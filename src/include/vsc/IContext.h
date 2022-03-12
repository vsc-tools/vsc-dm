/*
 * IContext.h
 *
 *  Created on: Jan 27, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IDataTypeInt.h"

namespace vsc {

class IContext {
public:

	virtual ~IContext() { }

	/**
	 * Returns a new datatype. The returned handle
	 * is owned by the context, and must not be deleted
	 */
	virtual IDataTypeInt *mkDataTypeInt(
			bool			is_signed,
			int32_t			width) = 0;

	virtual IModelField *mkModelFieldRoot(
			IDataType 			*type,
			const std::string	&name) = 0;

};

}
