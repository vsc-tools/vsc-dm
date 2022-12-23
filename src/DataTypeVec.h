/*
 * DataTypeVec.h
 *
 *  Created on: Jul 2, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IDataTypeVec.h"

namespace vsc {
namespace dm {

class DataTypeVec : public virtual IDataTypeVec {
public:
	DataTypeVec(IDataType *elem_t);

	virtual ~DataTypeVec();

	virtual IDataType *getElemType() const override {
		return m_elem_t;
	}

private:
	IDataType			*m_elem_t;
};

}
} /* namespace vsc */

