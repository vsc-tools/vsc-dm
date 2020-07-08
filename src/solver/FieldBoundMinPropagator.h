/*
 * FieldBoundMinPropagator.h
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#pragma once
#include "solver/FieldBoundPropagator.h"
#include "expr/Expr.h"

namespace vsc {

class FieldBoundMinPropagator : public FieldBoundPropagator {
public:
	FieldBoundMinPropagator(
			FieldBoundInfo 		*info,
			ExprSP				min_e);

	virtual ~FieldBoundMinPropagator();

	virtual void propagate();

private:
	ExprSP						m_min_e;
};

} /* namespace vsc */

