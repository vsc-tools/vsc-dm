/*
 * DataTypeWidthVisitor.cpp
 *
 *  Created on: Nov 1, 2021
 *      Author: mballance
 */

#include "DataTypeWidthVisitor.h"

namespace vsc {
namespace dm {

DataTypeWidthVisitor::DataTypeWidthVisitor() :
		m_is_signed(false), m_width(-1) {
	// TODO Auto-generated constructor stub

}

DataTypeWidthVisitor::~DataTypeWidthVisitor() {
	// TODO Auto-generated destructor stub
}

std::pair<bool,int32_t> DataTypeWidthVisitor::width(IDataType *t) {
	m_is_signed = false;
	m_width = -1;
	t->accept(this);
	return {m_is_signed, m_width};
}

void DataTypeWidthVisitor::visitDataTypeInt(IDataTypeInt *t) {
	m_is_signed = t->is_signed();
	m_width = t->width();
}

}
} /* namespace vsc */
