/*
 * ModelValRange.cpp
 *
 *  Created on: Feb 4, 2022
 *      Author: mballance
 */

#include "ModelValRange.h"

namespace vsc {

ModelValRange::ModelValRange(const IModelVal *lower) {
	m_lower.set(lower);
	m_upper.set(lower);
}

ModelValRange::ModelValRange(
		const IModelVal *lower,
		const IModelVal *upper) {
	m_lower.set(lower);
	m_upper.set(upper);
}

ModelValRange::ModelValRange(const IModelVal &lower) {
	m_lower.set(&lower);
	m_upper.set(&lower);
}

ModelValRange::ModelValRange(
		const IModelVal &lower,
		const IModelVal &upper) {
	m_lower.set(&lower);
	m_upper.set(&upper);
}

ModelValRange::ModelValRange(const IModelValRange *rhs) {
	m_lower.set(rhs->lower());
	m_upper.set(rhs->upper());
}

}

