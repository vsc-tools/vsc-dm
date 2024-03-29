/*
 * DataTypeWidthVisitor.h
 *
 *  Created on: Nov 1, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

class DataTypeWidthVisitor : public VisitorBase {
public:
	DataTypeWidthVisitor();

	virtual ~DataTypeWidthVisitor();

	std::pair<bool,int32_t> width(IDataType *t);

	virtual void visitDataTypeInt(IDataTypeInt *t) override;

private:
	bool					m_is_signed;
	int32_t					m_width;

};

}
} /* namespace vsc */

