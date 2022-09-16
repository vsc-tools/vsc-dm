/*
 * SolverBoolectorModelBuilder.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include <vector>
#include "SolverBoolector.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class SolverBoolectorSolveModelBuilder : public VisitorBase {
public:
	SolverBoolectorSolveModelBuilder(SolverBoolector *solver);

	virtual ~SolverBoolectorSolveModelBuilder();

	BoolectorNode *build(IModelField *f);

	BoolectorNode *build(IModelConstraint *c);

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override;

	virtual void visitDataTypeInt(IDataTypeInt *t) override;

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override;

	virtual void visitModelConstraint(IModelConstraint *c) override;

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override;

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) override;

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override;

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override;

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override;

	virtual void visitModelExprBin(IModelExprBin *e) override;

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override;

	virtual void visitModelExprIn(IModelExprIn *e) override;

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override;

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override;

	virtual void visitModelExprVal(IModelExprVal *e) override;

	virtual void visitModelField(IModelField *f) override;

	virtual void visitModelFieldRoot(IModelFieldRoot *f) override;

	virtual void visitModelFieldType(IModelFieldType *f) override;

private:

	using node_info_t=std::pair<bool, BoolectorNode *>;

private:

	BoolectorNode *toBoolNode(BoolectorNode *n);

	node_info_t expr(IModelExpr *e, int32_t ctx_width);

	BoolectorNode *extend(
			BoolectorNode		*n,
			int32_t				ctx_width,
			bool				is_signed);


private:
	SolverBoolector						*m_solver;
	std::vector<IModelField *>			m_field_s;
	std::pair<bool,BoolectorNode *>		m_node_i;
	std::vector<int32_t>				m_width_s;
	bool								m_build_field;
};

} /* namespace vsc */

