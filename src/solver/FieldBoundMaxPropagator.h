/*
 * FieldBoundMaxPropagator.h
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#pragma once
#include "solver/FieldBoundPropagator.h"
#include "solver/FieldBoundInfo.h"
#include "expr/Expr.h"

namespace vsc {

class FieldBoundMaxPropagator : public FieldBoundPropagator {
public:
	FieldBoundMaxPropagator(
			FieldBoundInfo		*info,
			ExprSP				max_e);

	virtual ~FieldBoundMaxPropagator();

	virtual void propagate() override;

private:
	ExprSP						m_max_e;

};

} /* namespace vsc */

