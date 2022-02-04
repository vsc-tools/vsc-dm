/*
 * DataTypeDomainRangeBuilder.h
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "ModelVal.h"
#include "ModelValRangelist.h"
#include "VisitorBase.h"

namespace vsc {

/**
 * Constructs a list of value ranges that describe
 * the domain of a data type
 */
class DataTypeDomainRangeBuilder : public VisitorBase {
public:
	DataTypeDomainRangeBuilder();

	virtual ~DataTypeDomainRangeBuilder();

	ModelValRangelist build(DataType *t);

	virtual void visitDataTypeInt(DataTypeInt *t) override;

private:
	ModelValRangelist						m_domain;

};

} /* namespace vsc */

