/*
 * TestModelFieldRef.cpp
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#include "TestModelFieldRef.h"
#include "Context.h"
#include "vsc/IDataTypeInt.h"
#include "vsc/IModelField.h"
#include "vsc/IModelFieldRef.h"

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

} /* namespace vsc */
