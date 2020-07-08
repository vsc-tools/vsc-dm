/*
 * VariableBoundVisitor.h
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#pragma once
#include <map>
#include <vector>
#include "VisitorBase.h"
#include "solver/FieldBoundInfo.h"

namespace vsc {

typedef std::map<Field*, FieldBoundInfoUP> FieldBoundMap;
typedef std::unique_ptr<FieldBoundMap> FieldBoundMapUP;

class FieldBoundVisitor : public VisitorBase {
public:
	FieldBoundVisitor();

	virtual ~FieldBoundVisitor();

	FieldBoundMap *process(
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintBlockSP>	&constraints);


	// Visitor Methods

	virtual void visitConstraintIf(ConstraintIf *c) override;

	// TODO: Implies

	// TODO: Foreach

	// TODO: Unique

	virtual void visitExprBin(ExprBin *e) override;

	// TODO: ExprIn

	virtual void visitExprFieldRef(ExprFieldRef *e) override;

	virtual void visitExprListSubscript(ExprListSubscript *e) override;

	virtual void visitFieldScalar(FieldScalar *f) override;

	// TODO: FieldEnum

private:
	uint32_t								m_depth;
	uint32_t								m_phase;
	FieldBoundMapUP							m_bounds;

};

} /* namespace vsc */

