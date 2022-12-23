/*
 * DataTypeDomainRangeBuilder.cpp
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#include "DataTypeDomainRangeBuilder.h"

namespace vsc {
namespace dm {

DataTypeDomainRangeBuilder::DataTypeDomainRangeBuilder() {
	// TODO Auto-generated constructor stub

}

DataTypeDomainRangeBuilder::~DataTypeDomainRangeBuilder() {
	// TODO Auto-generated destructor stub
}

ModelValRangelist DataTypeDomainRangeBuilder::build(IDataType *t) {
	m_domain.clear();
	t->accept(this);
	return m_domain;
}

void DataTypeDomainRangeBuilder::visitDataTypeInt(IDataTypeInt *t) {
	if (t->is_signed()) {
		m_domain.setIsSigned(true);
		if (t->width() > 64) {
			// TODO:
		} else if (t->width() == 64) {
			m_domain.push_back(ModelValRange(
					ModelVal(64, 0x8000000000000000),
					ModelVal(64, 0x7FFFFFFFFFFFFFFF)));
		} else {
			// Smaller than 64
			m_domain.push_back(ModelValRange(
					ModelVal(t->width(), (1ULL<<(t->width()-1))-1),
					ModelVal(t->width(), (1ULL<<(t->width()-1))-1)));
		}
	} else {
		m_domain.setIsSigned(false);
		if (t->width() > 64) {
			// TODO:
		} else if (t->width() == 64) {
			m_domain.push_back(ModelValRange(
					ModelVal(64, 0x0000000000000000),
					ModelVal(64, 0xFFFFFFFFFFFFFFFF)));
		} else {
			// Smaller than 64
			m_domain.push_back(ModelValRange(
					ModelVal(t->width(), 0),
					ModelVal(t->width(), (1ULL<<t->width())-1)));
		}

	}
}


}
} /* namespace vsc */
