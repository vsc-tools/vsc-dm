/*
 * ModelVal.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <stdint.h>
#include <vector>

namespace vsc {

class DataType;

class ModelVal;
using ModelValUP=std::unique_ptr<ModelVal>;
class ModelVal {
public:
	ModelVal();

	virtual ~ModelVal();

private:
	DataType						*m_type;
	std::vector<uint32_t>			m_val;
};

} /* namespace vsc */

