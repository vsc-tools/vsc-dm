/*
 * SolverBoolectorModelBuilder.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include <vector>
#include "SolverBoolector.h"
#include "VisitorBase.h"

namespace vsc {

class SolverBoolectorSolveModelBuilder : public VisitorBase {
public:
	SolverBoolectorSolveModelBuilder(SolverBoolector *solver);

	virtual ~SolverBoolectorSolveModelBuilder();

	BoolectorNode *build(ModelField *f);

	BoolectorNode *build(ModelConstraint *c);

	virtual void visitDataTypeInt(DataTypeInt *t) override;

	virtual void visitDataTypeStruct(DataTypeStruct *t) override;

	virtual void visitModelConstraint(ModelConstraint *c) override;

	virtual void visitModelConstraintExpr(ModelConstraintExpr *c) override;

	virtual void visitModelConstraintIf(ModelConstraintIf *c) override;

	virtual void visitModelConstraintScope(ModelConstraintScope *c) override;

	virtual void visitModelConstraintSoft(ModelConstraintSoft *c) override;

	virtual void visitModelExprBin(ModelExprBin *e) override;

	virtual void visitModelExprFieldRef(ModelExprFieldRef *e) override;

	virtual void visitModelExprPartSelect(ModelExprPartSelect *e) override;

	virtual void visitModelExprVal(ModelExprVal *e) override;

	virtual void visitModelField(ModelField *f) override;

	virtual void visitModelFieldRoot(ModelFieldRoot *f) override;

	virtual void visitModelFieldType(ModelFieldType *f) override;

private:

	using node_info_t=std::pair<bool, BoolectorNode *>;

private:

	BoolectorNode *toBoolNode(BoolectorNode *n);

	node_info_t expr(ModelExpr *e, int32_t ctx_width);

	BoolectorNode *extend(
			BoolectorNode		*n,
			int32_t				ctx_width,
			bool				is_signed);


private:
	SolverBoolector						*m_solver;
	std::vector<ModelField *>			m_field_s;
	std::pair<bool,BoolectorNode *>		m_node_i;
	std::vector<int32_t>				m_width_s;
};

} /* namespace vsc */

