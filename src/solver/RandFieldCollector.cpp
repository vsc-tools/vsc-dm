/*
 * RandFieldCollector.cpp
 *
 *  Created on: Jul 10, 2020
 *      Author: ballance
 */

#include "RandFieldCollector.h"

namespace vsc {

RandFieldCollector::RandFieldCollector() : m_rand_fields(0) {
	// TODO Auto-generated constructor stub

}

RandFieldCollector::~RandFieldCollector() {
	// TODO Auto-generated destructor stub
}

void RandFieldCollector::collect(
		const std::vector<FieldSP>		&fields,
		std::vector<FieldScalar *>		&rand_fields) {
	m_rand_fields = &rand_fields;
	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}
}

void RandFieldCollector::visitFieldScalar(FieldScalar *f) {
	m_rand_fields->push_back(f);
}

} /* namespace vsc */
