/*
 * SolverBoolectorModelBuilder.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include <vector>
#include "SolverBitwuzla.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class SolverBitwuzlaSolveModelBuilder : public VisitorBase {
public:
	SolverBitwuzlaSolveModelBuilder(SolverBitwuzla *solver);

	virtual ~SolverBitwuzlaSolveModelBuilder();

	const BitwuzlaTerm *build(IModelField *f);

	const BitwuzlaTerm *build(IModelConstraint *c);

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override;

	virtual void visitDataTypeInt(IDataTypeInt *t) override;

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override;

	virtual void visitModelConstraint(IModelConstraint *c) override;

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override;

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override;

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override;

	virtual void visitModelExprBin(IModelExprBin *e) override;

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override;

	virtual void visitModelExprIn(IModelExprIn *e) override;

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override;

	virtual void visitModelExprVal(IModelExprVal *e) override;

	virtual void visitModelField(IModelField *f) override;

	virtual void visitModelFieldRoot(IModelFieldRoot *f) override;

	virtual void visitModelFieldType(IModelFieldType *f) override;

private:

	using node_info_t=std::pair<bool, const BitwuzlaTerm *>;

private:

	const BitwuzlaTerm *toBoolNode(const BitwuzlaTerm *n);

	node_info_t expr(IModelExpr *e, int32_t ctx_width);

	const BitwuzlaTerm *extend(
			const BitwuzlaTerm		*n,
			int32_t					ctx_width,
			bool					is_signed);


private:
	SolverBitwuzla							*m_solver;
	std::vector<IModelField *>				m_field_s;
	std::pair<bool,const BitwuzlaTerm *>	m_node_i;
	std::vector<int32_t>					m_width_s;
};

} /* namespace vsc */

