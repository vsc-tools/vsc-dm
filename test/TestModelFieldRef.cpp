/*
 * TestModelFieldRef.cpp
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#include "TestModelFieldRef.h"
#include "Context.h"
#include "VscImpl.h"
#include "vsc/IDataTypeInt.h"
#include "vsc/IModelField.h"
#include "vsc/IModelFieldRef.h"
#include "vsc/impl/ModelBuildContext.h"
#include "vsc/impl/TaskUnrollModelFieldRefConstraints.h"
#include "vsc/impl/PrettyPrinter.h"
#include "vsc/impl/TaskSetUsedRand.h"

namespace vsc {

TestModelFieldRef::TestModelFieldRef() {
	// TODO Auto-generated constructor stub

}

TestModelFieldRef::~TestModelFieldRef() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestModelFieldRef, smoke) {
	Context ctx;

	IDataTypeInt *vsc_uint32_t = ctx.findDataTypeInt(false, 32);
	if (!vsc_uint32_t) {
		vsc_uint32_t = ctx.mkDataTypeInt(false, 32);
		ctx.addDataTypeInt(vsc_uint32_t);
	}
	IModelField *top = ctx.mkModelFieldRoot(vsc_uint32_t, "top");
	IModelField *a = ctx.mkModelFieldRoot(vsc_uint32_t, "a");
	a->setFlag(ModelFieldFlag::DeclRand);
	top->addField(a);
	IModelFieldRef *ref = ctx.mkModelFieldRefRoot(vsc_uint32_t, "ref");
	top->addField(ref);

	IModelField *f1 = ctx.mkModelFieldRoot(vsc_uint32_t, "f1");
	f1->val()->set_val_u(1);

	IModelField *f2 = ctx.mkModelFieldRoot(vsc_uint32_t, "f2");
	f2->val()->set_val_u(2);

	top->addConstraint(ctx.mkModelConstraintExpr(
			ctx.mkModelExprBin(
					ctx.mkModelExprFieldRef(a),
					BinOp::Eq,
					ctx.mkModelExprFieldRef(ref))));

	ICompoundSolverUP solver(ctx.mkCompoundSolver());
	IRandStateUP randstate(ctx.mkRandState("0"));

	ref->setRef(f1);

	solver->solve(
			randstate.get(),
			{top},
			{},
			SolveFlags::Randomize|SolveFlags::RandomizeDeclRand|SolveFlags::RandomizeTopFields);

	fprintf(stdout, "a: %lld\n", a->val()->val_u());

}

TEST_F(TestModelFieldRef, ref_subfield_ref) {
	Context ctx;
	ModelBuildContext build_ctx(&ctx);

	VscImpl::inst()->getDebugMgr()->enable(true);

	IDataTypeInt *vsc_uint32_t = ctx.findDataTypeInt(false, 32);
	if (!vsc_uint32_t) {
		vsc_uint32_t = ctx.mkDataTypeInt(false, 32);
		ctx.addDataTypeInt(vsc_uint32_t);
	}

	IModelValUP val(ctx.mkModelVal());
	val->setBits(32);

	IDataTypeStruct *obj_t = ctx.mkDataTypeStruct("obj_t");
	obj_t->addField(ctx.mkTypeFieldPhy(
		"a",
		vsc_uint32_t,
		false,
		TypeFieldAttr::Rand,
		0));
	obj_t->addField(ctx.mkTypeFieldPhy(
		"b",
		vsc_uint32_t,
		false,
		TypeFieldAttr::Rand,
		0));

	IModelFieldRef *root_ref = ctx.mkModelFieldRefRoot(obj_t, "ref");

	std::vector<IModelField *> candidates;
	std::vector<IModelConstraint *> constraints;
	std::vector<IModelConstraintUP> constraints_u;
	for (uint32_t i=0; i<4; i++) {
		char tmp[16];
		sprintf(tmp, "c%d", i);
		candidates.push_back(obj_t->mkRootField(&build_ctx, tmp, false));
		val->set_val_i(i);

		// Ensure that each candidate's 'a' field tracks its index
		IModelExprIndexedFieldRef *ref_a = ctx.mkModelExprIndexedFieldRef();
		ref_a->addField(candidates.back());
		ref_a->addFieldOffsetRef(0);
		IModelConstraint *c = ctx.mkModelConstraintExpr(
			ctx.mkModelExprBin(
				ref_a,
				BinOp::Eq,
				ctx.mkModelExprVal(val.get())
			));
		constraints.push_back(c);
		constraints_u.push_back(IModelConstraintUP(c));
	}	

	// These constraints (directly on the object) must come through
	std::vector<IModelConstraint *> target_constraints;
	for (std::vector<IModelConstraint *>::const_iterator
		it=constraints.begin();
		it!=constraints.end(); it++) {
		target_constraints.push_back(*it);
	}	

	// Now, place a constraint relative to the ref field
	// This constraint will get expanded
	IModelExprIndexedFieldRef *ref = ctx.mkModelExprIndexedFieldRef();
	ref->addField(root_ref);
	ref->addFieldOffsetRef(0); 
	val->set_val_i(2);
	IModelConstraint *c = ctx.mkModelConstraintExpr(
		ctx.mkModelExprBin(
			ref,
			BinOp::Eq,
			ctx.mkModelExprVal(val.get())));
	constraints.push_back(c);
	constraints_u.push_back(IModelConstraintUP(c));

	// Now, let's build out the reference constraints
	ModelFieldRefConstraintDataUP data(
		TaskUnrollModelFieldRefConstraints(&ctx).build(
			root_ref,
			candidates,
			{},
			constraints));

	fprintf(stdout, "Select Constraints: %d\n", data->getSelectConstraints().size());

	ICompoundSolverUP solver(ctx.mkCompoundSolver());
	IRandStateUP randstate(ctx.mkRandState("0"));

	for (std::vector<IModelConstraintUP>::const_iterator
		it=data->getSelectConstraints().begin();
		it!=data->getSelectConstraints().end(); it++) {
		target_constraints.push_back(it->get());
	}
	target_constraints.push_back(data->getValidC());

	// Add in constraints from the candidate objects
	for (std::vector<IModelField *>::const_iterator
		it=candidates.begin();
		it!=candidates.end(); it++) {
		for (std::vector<IModelConstraintUP>::const_iterator
			c_it=(*it)->constraints().begin();
			c_it!=(*it)->constraints().end(); c_it++) {
			target_constraints.push_back(c_it->get());
			}
	}

	for (std::vector<IModelConstraint *>::const_iterator
		it=target_constraints.begin();
		it!=target_constraints.end(); it++) {
		fprintf(stdout, "Constraint:\n%s\n", PrettyPrinter().print(*it));
	}

	// Reset the rand state of all candidates...
	for (std::vector<IModelField *>::const_iterator
		it=candidates.begin();
		it!=candidates.end(); it++) {
		TaskSetUsedRand().apply(*it, true);
	}

	bool result = solver->solve(
			randstate.get(),
			{data->getSelector()},
			target_constraints,
			SolveFlags::Randomize|SolveFlags::RandomizeDeclRand|SolveFlags::RandomizeTopFields);
	ASSERT_TRUE(result);

	fprintf(stdout, "selector=%lld\n", data->getSelector()->val()->val_i());
	ASSERT_EQ(data->getSelector()->val()->val_i(), 2);
}

TEST_F(TestModelFieldRef, ref_subfield_bidir_ref) {
	Context ctx;
	ModelBuildContext build_ctx(&ctx);

	VscImpl::inst()->getDebugMgr()->enable(true);

	IDataTypeInt *vsc_uint32_t = ctx.findDataTypeInt(false, 32);
	if (!vsc_uint32_t) {
		vsc_uint32_t = ctx.mkDataTypeInt(false, 32);
		ctx.addDataTypeInt(vsc_uint32_t);
	}

	IModelValUP val(ctx.mkModelVal());
	val->setBits(32);

	IDataTypeStruct *obj_t = ctx.mkDataTypeStruct("obj_t");
	obj_t->addField(ctx.mkTypeFieldPhy(
		"a",
		vsc_uint32_t,
		false,
		TypeFieldAttr::Rand,
		0));
	obj_t->addField(ctx.mkTypeFieldPhy(
		"b",
		vsc_uint32_t,
		false,
		TypeFieldAttr::Rand,
		0));

	IModelFieldRef *root_ref = ctx.mkModelFieldRefRoot(obj_t, "ref");

	std::vector<IModelField *> candidates;
	std::vector<IModelConstraint *> constraints;
	std::vector<IModelConstraintUP> constraints_u;
	for (uint32_t i=0; i<4; i++) {
		char tmp[16];
		sprintf(tmp, "c%d", i);
		candidates.push_back(obj_t->mkRootField(&build_ctx, tmp, false));
	}

	// Candidate refs are the producer-refs for a given candidate
	std::vector<IModelFieldRef *> candidate_refs;
	std::vector<IModelFieldRefUP> candidate_refs_u;
	for (uint32_t i=0; i<4; i++) {
		char tmp[16];
		sprintf(tmp, "cr%d", i);
		IModelFieldRef *ref_c = obj_t->mkRootFieldT<IModelFieldRef>(&build_ctx, tmp, true);
		ref_c->setRef(candidates.at(i));
		candidate_refs.push_back(ref_c);
		candidate_refs_u.push_back(IModelFieldRefUP(ref_c));

		val->set_val_i(i);

		// Ensure that each candidate ref's 'a' field tracks its index
		IModelExprIndexedFieldRef *ref_a = ctx.mkModelExprIndexedFieldRef();
		ref_a->addField(candidate_refs.back());
		ref_a->addFieldOffsetRef(0);
		IModelConstraint *c = ctx.mkModelConstraintExpr(
			ctx.mkModelExprBin(
				ref_a,
				BinOp::Eq,
				ctx.mkModelExprVal(val.get())
			));
		constraints.push_back(c);
		constraints_u.push_back(IModelConstraintUP(c));
	}

	// These constraints (directly on the object) must come through
	std::vector<IModelConstraint *> target_constraints;
	for (std::vector<IModelConstraint *>::const_iterator
		it=constraints.begin();
		it!=constraints.end(); it++) {
		target_constraints.push_back(*it);
	}	

	// Now, place a constraint relative to the ref field
	// This constraint will get expanded
	IModelExprIndexedFieldRef *ref = ctx.mkModelExprIndexedFieldRef();
	ref->addField(root_ref);
	ref->addFieldOffsetRef(0); 
	val->set_val_i(2);
	IModelConstraint *c = ctx.mkModelConstraintExpr(
		ctx.mkModelExprBin(
			ref,
			BinOp::Eq,
			ctx.mkModelExprVal(val.get())));
	constraints.push_back(c);
	constraints_u.push_back(IModelConstraintUP(c));

	// Now, let's build out the reference constraints
	ModelFieldRefConstraintDataUP data(
		TaskUnrollModelFieldRefConstraints(&ctx).build(
			root_ref,
			candidates,
			{}, //			candidate_refs,
			constraints));

	fprintf(stdout, "Select Constraints: %d\n", data->getSelectConstraints().size());

	ICompoundSolverUP solver(ctx.mkCompoundSolver());
	IRandStateUP randstate(ctx.mkRandState("0"));

	for (std::vector<IModelConstraintUP>::const_iterator
		it=data->getSelectConstraints().begin();
		it!=data->getSelectConstraints().end(); it++) {
		target_constraints.push_back(it->get());
	}
	target_constraints.push_back(data->getValidC());

	// Add in constraints from the candidate objects
	for (std::vector<IModelField *>::const_iterator
		it=candidates.begin();
		it!=candidates.end(); it++) {
		for (std::vector<IModelConstraintUP>::const_iterator
			c_it=(*it)->constraints().begin();
			c_it!=(*it)->constraints().end(); c_it++) {
			target_constraints.push_back(c_it->get());
			}
	}

	for (std::vector<IModelConstraint *>::const_iterator
		it=target_constraints.begin();
		it!=target_constraints.end(); it++) {
		fprintf(stdout, "Constraint:\n%s\n", PrettyPrinter().print(*it));
	}

	// Reset the rand state of all candidates...
	for (std::vector<IModelField *>::const_iterator
		it=candidates.begin();
		it!=candidates.end(); it++) {
		TaskSetUsedRand().apply(*it, true);
	}

	bool result = solver->solve(
			randstate.get(),
			{data->getSelector()},
			target_constraints,
			SolveFlags::Randomize|SolveFlags::RandomizeDeclRand|SolveFlags::RandomizeTopFields);
	ASSERT_TRUE(result);

	fprintf(stdout, "selector=%lld\n", data->getSelector()->val()->val_i());
	ASSERT_EQ(data->getSelector()->val()->val_i(), 2);
}

} /* namespace vsc */
