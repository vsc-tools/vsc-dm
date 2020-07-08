/*
 * FieldBoundMaxPropagator.cpp
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#include "FieldBoundMaxPropagator.h"

#include "../expr/ExprNumericEvaluator.h"

namespace vsc {

FieldBoundMaxPropagator::FieldBoundMaxPropagator(
		FieldBoundInfo 		*info,
		ExprSP				max_e) : FieldBoundPropagator(info), m_max_e(max_e) {

}

FieldBoundMaxPropagator::~FieldBoundMaxPropagator() {
	// TODO Auto-generated destructor stub
}

void FieldBoundMaxPropagator::propagate() {
	ExprNumericEvaluator eval;
	ExprValNumericSP max_v = eval.eval_num(m_max_e.get());


	domain_t &domain = m_info->domain();
	int32_t i=domain.size()-1;

	// Find the first interval where the minimum is less than the max value
	while (i>0) {
		if (domain.at(i).first->le(max_v.get())) {
			break;
		} else {
			i--;
		}
	}

	bool do_propagate = false;

	if (domain.at(i).second->gt(max_v.get())) {
		domain.at(i).second = max_v;
		do_propagate = true;
	}

	if (i < domain.size()-1) {
		// Trim off range elements, since these are greater
		// than the new max
		do_propagate = true;
		domain.resize(i+1);
	}

	if (do_propagate) {
		m_info->propagate();
	}
}

} /* namespace vsc */
