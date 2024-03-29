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
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

/**
 * Constructs a list of value ranges that describe
 * the domain of a data type
 */
class DataTypeDomainRangeBuilder : public VisitorBase {
public:
	DataTypeDomainRangeBuilder();

	virtual ~DataTypeDomainRangeBuilder();

	ModelValRangelist build(IDataType *t);

	virtual void visitDataTypeInt(IDataTypeInt *t) override;

private:
	ModelValRangelist						m_domain;

};

}
} /* namespace vsc */

