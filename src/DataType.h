/*
 * DataType.h
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IDataType.h"
#include "vsc/IModelFieldFactory.h"
#include "ModelVal.h"

namespace vsc {

class DataType;
typedef std::unique_ptr<DataType> DataTypeUP;
class DataType : public virtual IDataType {
public:
	DataType(IModelFieldFactory *f=0);

	virtual ~DataType();

	virtual void setFactory(IModelFieldFactory *f) {
		m_factory = IModelFieldFactoryUP(f);
	}

	virtual IModelFieldFactory *getFactory() {
		return m_factory.get();
	}

protected:
	IModelFieldFactoryUP				m_factory;

};

} /* namespace vsc */

