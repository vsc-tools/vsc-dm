/*
 * SolveSpecBuilder.h
 *
 *  Created on: Oct 7, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include "VisitorBase.h"
#include "SolveSet.h"
#include "SolveSpec.h"

namespace vsc {

class SolveSpecBuilder : public VisitorBase {
public:
	SolveSpecBuilder();

	virtual ~SolveSpecBuilder();

	SolveSpec *build(
			const std::vector<ModelField *>			&fields,
			const std::vector<ModelConstraint *>	&constraints
			);

	virtual void visitDataTypeInt(DataTypeInt *t) override;

	virtual void visitModelConstraintExpr(ModelConstraintExpr *c) override;

	virtual void visitModelExprFieldRef(ModelExprFieldRef *e) override;

	virtual void visitModelField(ModelField *f) override;

private:

	void constraint_enter(ModelConstraint *c);

	void constraint_leave(ModelConstraint *c);

	void process_fieldref(ModelField *f);

private:
	uint32_t									m_pass;
	std::vector<SolveSetUP>						m_solveset_l;
	std::unordered_map<SolveSet *, int32_t>		m_solveset_m;
	SolveSet									*m_active_solveset;
	std::unordered_map<ModelField *,int32_t>	m_unconstrained_m;
	std::vector<ModelField *>					m_unconstrained_l;

	std::unordered_map<ModelField*,SolveSet*>	m_solveset_field_m;
	std::vector<ModelConstraint *>				m_constraint_s;

	std::vector<ModelField *>					m_field_s;


};

} /* namespace vsc */

