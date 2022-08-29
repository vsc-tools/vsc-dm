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
#include "vsc/IContext.h"
#include "vsc/impl/VisitorBase.h"
#include "SolveSet.h"
#include "SolveSpec.h"

namespace vsc {

class SolveSpecBuilder : public VisitorBase {
public:
	SolveSpecBuilder(IContext *ctx);

	virtual ~SolveSpecBuilder();

	SolveSpec *build(
			const std::vector<IModelField *>		&fields,
			const std::vector<IModelConstraint *>	&constraints
			);

	SolveSpec *build(
			const std::vector<IModelField *>		&fields,
			const std::vector<IModelConstraintUP>	&constraints
			);

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override;

	virtual void visitDataTypeInt(IDataTypeInt *t) override;

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override;

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override;

	virtual void visitModelConstraintForeach(IModelConstraintForeach *c) override;

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) override;

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override;

//	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override;

//	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) override;

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override;

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override;

	virtual void visitModelField(IModelField *f) override;

private:

	void constraint_enter(IModelConstraint *c);

	void constraint_leave(IModelConstraint *c);

	void process_fieldref(IModelField *f);

private:
	IContext									*m_ctx;
	uint32_t									m_pass;
	SolveSetFlag								m_flags;
	std::vector<SolveSetUP>						m_solveset_l;
	std::unordered_map<SolveSet *, int32_t>		m_solveset_m;
	SolveSet									*m_active_solveset;
	std::unordered_map<IModelField *,int32_t>	m_unconstrained_m;
	std::vector<IModelField *>					m_unconstrained_l;

	std::unordered_map<IModelField*,SolveSet*>	m_solveset_field_m;
	std::vector<IModelConstraint *>				m_constraint_s;

	std::vector<IModelField *>					m_field_s;


};

} /* namespace vsc */

