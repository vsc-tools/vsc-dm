/*
 * SolveGroupSetBuilder.h
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_SOLVEGROUPSETBUILDER_H_
#define SRC_SOLVER_SOLVEGROUPSETBUILDER_H_
#include <vector>
#include <set>
#include <map>
#include "VisitorBase.h"
#include "SolveGroupSet.h"
#include "Field.h"
#include "ConstraintBlock.h"

namespace vsc {

class SolveGroupSetBuilder : public VisitorBase {
public:
	SolveGroupSetBuilder();

	virtual ~SolveGroupSetBuilder();

	SolveGroupSet *build(
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintBlockSP>	&constraints
			);

	virtual void visitConstraintBlock(ConstraintBlock *c) override;

	virtual void visitConstraintStmtEnter(ConstraintStmt *c) override;

	virtual void visitConstraintStmtLeave(ConstraintStmt *c) override;

	virtual void visitExprFieldRef(ExprFieldRef *e) override;

	virtual void visitFieldComposite(FieldComposite *f) override;

	virtual void visitFieldScalar(FieldScalar *f) override;

protected:

	void process_fieldref(Field *f);

private:
	uint32_t							m_pass;
	bool								m_used_rand;
	std::set<Field *>					m_field_s;
	ConstraintStmt						*m_active_constraint;
	SolveGroup							*m_active_solvegroup;
	std::set<SolveGroup *>				m_solvegroup_s;
	std::map<Field *, SolveGroup *>		m_field_solvegroup_m;
	std::vector<ConstraintStmt *>		m_constraint_l;
};

} /* namespace vsc */

#endif /* SRC_SOLVER_SOLVEGROUPSETBUILDER_H_ */
