/*
 * DataType.h
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IContext.h"
#include "vsc/IDataType.h"
#include "vsc/IModelBuildContext.h"
#include "ModelVal.h"

namespace vsc {

class DataType;
typedef std::unique_ptr<DataType> DataTypeUP;
class DataType : public virtual IDataType {
public:
	DataType();

	virtual ~DataType();

protected:

};

} /* namespace vsc */

