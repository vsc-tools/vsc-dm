/*
 * IDataType.h
 *
 *  Created on: Feb 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IAccept.h"

namespace vsc {
namespace dm {

class IModelBuildContext;

class IDataType;
using IDataTypeUP=std::unique_ptr<IDataType>;
using IDataTypeSP=std::shared_ptr<IDataType>;
class IDataType : public IAccept {
public:

	virtual ~IDataType() { }

	// Notify datatype that no more information
	// will be added.
//	virtual void finalize() = 0;

	virtual IModelField *mkRootField(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) = 0;

	virtual IModelField *mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type) = 0;

	template <class T> T *mkRootFieldT(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) {
		return dynamic_cast<T *>(mkRootField(ctxt, name, is_ref));
	}

	template <class T> T *mkTypeFieldT(
		IModelBuildContext	*ctxt,
		ITypeField			*type) {
		return dynamic_cast<T *>(mkTypeField(ctxt, type));
	}

};

}
}

