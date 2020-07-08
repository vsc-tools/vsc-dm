/*
 * FieldBoundInfo.cpp
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#include "FieldBoundInfo.h"

namespace vsc {

FieldBoundInfo::FieldBoundInfo(bool is_signed) : m_is_signed(is_signed),
		m_is_constrained(false) {

}

FieldBoundInfo::~FieldBoundInfo() {
	// TODO Auto-generated destructor stub
}

void FieldBoundInfo::propagate() {
	for (std::vector<FieldBoundPropagatorUP>::const_iterator it=m_propagators.begin();
			it!=m_propagators.end(); it++) {
		(*it)->propagate();
	}
}

void FieldBoundInfo::update() {

}

} /* namespace vsc */
