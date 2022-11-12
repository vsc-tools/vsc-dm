/*
 * CompoundSolverDefault.cpp
 *
 *  Created on: Mar 23, 2022
 *      Author: mballance
 */

#include "vsc/impl/PrettyPrinter.h"
#include "vsc/impl/TaskUnrollModelIterativeConstraints.h"
#include "vsc/impl/TaskRollbackConstraintSubst.h"
#include "CommitFieldValueVisitor.h"
#include "CompoundSolverDefault.h"
#include "Debug.h"
#include "SolverFactoryDefault.h"
#include "SolveSetSolveModelBuilder.h"
#include "SolveSetSwizzlerPartsel.h"
#include "SolveSpecBuilder.h"
#include "vsc/impl/TaskSetUsedRand.h"
#include "TaskResizeConstrainedModelVec.h"
#include "vsc/impl/TaskUnrollModelIterativeConstraints.h"

#define EN_DEBUG_COMPOUND_SOLVER_DEFAULT

#ifdef EN_DEBUG_COMPOUND_SOLVER_DEFAULT
DEBUG_SCOPE(CompoundSolverDefault);
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(CompoundSolverDefault, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(CompoundSolverDefault, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(CompoundSolverDefault, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {

CompoundSolverDefault::CompoundSolverDefault(IContext *ctxt) : m_ctxt(ctxt) {
	// TODO Auto-generated constructor stub

}

CompoundSolverDefault::~CompoundSolverDefault() {
	// TODO Auto-generated destructor stub
}

bool CompoundSolverDefault::solve(
			IRandState								*randstate,
			const std::vector<IModelField *>		&fields,
			const std::vector<IModelConstraint *>	&constraints,
			SolveFlags								flags) {
	ISolverFactory *solver_f = SolverFactoryDefault::inst();

	bool ret = true;
	DEBUG_ENTER("randomize n_fields=%d n_constraints=%d",
			fields.size(),
			constraints.size());

	if ((flags & SolveFlags::RandomizeDeclRand) || (flags & SolveFlags::RandomizeTopFields)) {
		TaskSetUsedRand task;
		for (auto f=fields.begin(); f!=fields.end(); f++) {
			task.apply(*f,
					(flags & SolveFlags::RandomizeTopFields) != SolveFlags::NoFlags,
					((flags & SolveFlags::RandomizeDeclRand) != SolveFlags::NoFlags)?-1:1);
			DEBUG("Flags: %s 0x%08llx", (*f)->name().c_str(), (*f)->flags());
		}
	}

	SolveSpecUP spec(SolveSpecBuilder(m_ctxt).build(
			fields,
			constraints
			));

	DEBUG("%d solve-sets ; %d unconstrained ; %d unconstrained_sz_vec",
			spec->solvesets().size(),
			spec->unconstrained().size(),
			spec->unconstrained_sz_vec().size());

	// Start by fixing the size of the unconstrained-size vectors
	// to the current size
	for (std::vector<IModelFieldVec *>::const_iterator
		it=spec->unconstrained_sz_vec().begin();
		it!=spec->unconstrained_sz_vec().end(); it++) {
		(*it)->getSizeRef()->val()->set_val_u((*it)->getSize(), 32);
		(*it)->getSizeRef()->setFlag(ModelFieldFlag::Resolved);
	}

	for (auto uc_it=spec->unconstrained().begin();
			uc_it!=spec->unconstrained().end(); uc_it++) {
		DEBUG("Randomize unconstrained field %s", (*uc_it)->name().c_str());
		randstate->randbits((*uc_it)->val());
	}

	for (auto sset=spec->solvesets().begin();
			sset!=spec->solvesets().end(); sset++) {
		DEBUG("Solve Set: %d fields ; %d constraints",
				(*sset)->all_fields().size(),
				(*sset)->constraints().size());

		// See if we need to re-evaluate due to vector constraints
		// TODO: Apply vector-sizing task
		if ((*sset)->constrained_sz_vec().size() > 0) {
			fprintf(stdout, "TODO: apply sizing to vectors\n");

			TaskResizeConstrainedModelVec(m_ctxt, solver_f).resize(sset->get());
		} 

		if ((*sset)->hasFlags(SolveSetFlag::HaveForeach)) {
			// This solve-set has foreach constraints. Need to expand
			// the constraints, etc
			fprintf(stdout, "TODO: expand foreach constraints\n");
			TaskUnrollModelIterativeConstraints unroller(m_ctxt);
			IModelConstraintScopeUP unroll_s(m_ctxt->mkModelConstraintScope());
			for (std::vector<IModelConstraint *>::const_iterator
				it=(*sset)->constraints().begin();
				it!=(*sset)->constraints().end(); it++) {
				if (dynamic_cast<IModelConstraintScope *>(*it)) {
					unroller.unroll(unroll_s.get(), *it);
				}
			}

			DEBUG("unroll_s: %d constraints", unroll_s->constraints().size());

			// Now, partition up the new expanded set
			SolveSpecUP spec_it(SolveSpecBuilder(m_ctxt).build(
				{}, {unroll_s.get()}));

			DEBUG("spec_it: %d solve-sets ; %d unconstrained ; %d unconstrained_sz_vec",
					spec_it->solvesets().size(),
					spec_it->unconstrained().size(),
					spec_it->unconstrained_sz_vec().size());

			for (std::vector<SolveSetUP>::const_iterator 
					sset_it=spec_it->solvesets().begin();
					sset_it!=spec_it->solvesets().end(); sset_it++) {
				DEBUG("Solve Set It: %d fields ; %d constraints",
						(*sset_it)->all_fields().size(),
						(*sset_it)->constraints().size());
				solve_sset(sset_it->get(), solver_f, randstate, flags);
			}

			// TODO: roll-back the variables in the solve-set to 
			// reverse the  result of unrolling
			for (std::vector<IModelConstraint *>::const_iterator
				it=(*sset)->constraints().begin();
				it!=(*sset)->constraints().end(); it++) {
				TaskRollbackConstraintSubst().rollback(*it);
			}

		} else {
			// If vector-sizing has no effect on this solve set, then proceed
			// to solve and randomize the existing solveset
			if (!(ret=solve_sset(sset->get(), solver_f, randstate, flags))) {
				break;
			}
		}
	}


	DEBUG_LEAVE("randomize n_fields=%d n_constraints=%d ret=%d",
			fields.size(),
			constraints.size(),
			ret);
	return ret;
}

bool CompoundSolverDefault::solve_sset(
	SolveSet			*sset,
	ISolverFactory		*solver_f,
	IRandState			*randstate,
	SolveFlags			flags) {
	DEBUG_ENTER("solve_sset");
	bool ret = true;

	ISolverUP solver(solver_f->createSolverInst(sset));
	// Build solve data for this solve set
	SolveSetSolveModelBuilder(solver.get()).build(sset);

/*
	for (std::vector<IModelConstraint *>::const_iterator
		it=sset->constraints().begin();
		it!=sset->constraints().end(); it++) {
		DEBUG("Constraint: %s", PrettyPrinter().print(*it));
	}
 */

	// First, ensure all constraints solve
	for (auto c_it=sset->constraints().begin();
			c_it!=sset->constraints().end(); c_it++) {
		solver->addAssume(*c_it);
	}
	for (auto c_it=sset->soft_constraints().begin();
			c_it!=sset->soft_constraints().end(); c_it++) {
		solver->addAssume(*c_it);
	}

	if (solver->isSAT()) {
		DEBUG("PASS: Initial try-solve for solveset");
		for (auto c_it=sset->constraints().begin();
			c_it!=sset->constraints().end(); c_it++) {
			solver->addAssert(*c_it);
		}
	} else {
		DEBUG("FAIL: Initial try-solve for solveset");

		ret = false;

		// TODO: Try backing off soft constraints
	}

	if (ret) {
		if ((flags & SolveFlags::Randomize) != SolveFlags::NoFlags) {
			// Swizzle fields
			SolveSetSwizzlerPartsel(randstate).swizzle(
					solver.get(),
					sset);
		}

		// Ensure we're SAT
		if (!solver->isSAT()) {
			fprintf(stdout, "unsat post-swizzle\n");
		}

		for (auto f_it=sset->rand_fields().begin();
				f_it!=sset->rand_fields().end(); f_it++) {
			DEBUG("Commit %s", (*f_it)->name().c_str());
			CommitFieldValueVisitor(solver.get()).commit(*f_it);
		}
	}

	DEBUG_LEAVE("solve_sset");
	return ret;
}


} /* namespace vsc */
