/*
 * SolverBoolectorModelBuilder.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include <vector>
#include "SolverBitwuzla.h"
#include "VisitorBase.h"

namespace vsc {

class SolverBitwuzlaSolveModelBuilder : public VisitorBase {
public:
	SolverBitwuzlaSolveModelBuilder(SolverBitwuzla *solver);

	virtual ~SolverBitwuzlaSolveModelBuilder();

	BitwuzlaTerm *build(ModelField *f);

	BitwuzlaTerm *build(ModelConstraint *c);

	virtual void visitDataTypeInt(DataTypeInt *t) override;

	virtual void visitDataTypeStruct(DataTypeStruct *t) override;

	virtual void visitModelConstraint(ModelConstraint *c) override;

	virtual void visitModelConstraintExpr(ModelConstraintExpr *c) override;

	virtual void visitModelConstraintScope(ModelConstraintScope *c) override;

	virtual void visitModelConstraintSoft(ModelConstraintSoft *c) override;

	virtual void visitModelExprBin(ModelExprBin *e) override;

	virtual void visitModelExprFieldRef(ModelExprFieldRef *e) override;

	virtual void visitModelExprIn(ModelExprIn *e) override;

	virtual void visitModelExprPartSelect(ModelExprPartSelect *e) override;

	virtual void visitModelExprVal(ModelExprVal *e) override;

	virtual void visitModelField(ModelField *f) override;

	virtual void visitModelFieldRoot(ModelFieldRoot *f) override;

	virtual void visitModelFieldType(ModelFieldType *f) override;

private:

	using node_info_t=std::pair<bool, BitwuzlaTerm *>;

private:

	BitwuzlaTerm *toBoolNode(BitwuzlaTerm *n);

	node_info_t expr(ModelExpr *e, int32_t ctx_width);

	BitwuzlaTerm *extend(
			BitwuzlaTerm		*n,
			int32_t				ctx_width,
			bool				is_signed);


private:
	SolverBitwuzla						*m_solver;
	std::vector<ModelField *>			m_field_s;
	std::pair<bool,BitwuzlaTerm *>		m_node_i;
	std::vector<int32_t>				m_width_s;
};

} /* namespace vsc */

