/*
 * IDataType.h
 *
 *  Created on: Feb 8, 2022
 *      Author: mballance
 */

#pragma once
#include <string>
#include "vsc/dm/IAccept.h"
#include "vsc/dm/IAssociatedData.h"
#include "vsc/dm/IValOps.h"

namespace vsc {
namespace dm {

class IModelBuildContext;
class IContext;

class IDataType;
using IDataTypeUP=UP<IDataType>;
using IDataTypeSP=std::shared_ptr<IDataType>;
class IDataType : 
    public virtual IAccept,
    public virtual IValOps {
public:

	virtual ~IDataType() { }

	// Notify datatype that no more information
	// will be added.
	virtual void finalize(IContext *ctxt) = 0;

    virtual int32_t getByteSize() const = 0;

	virtual IModelField *mkRootField(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) = 0;

	virtual IModelField *mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type,
        const ValRef        &val) = 0;

	template <class T> T *mkRootFieldT(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) {
		return dynamic_cast<T *>(mkRootField(ctxt, name, is_ref));
	}

	template <class T> T *mkTypeFieldT(
		IModelBuildContext	*ctxt,
		ITypeField			*type,
        const ValRef        &val) {
		return dynamic_cast<T *>(mkTypeField(ctxt, type, val));
	}

    virtual void setAssociatedData(IAssociatedData *data) = 0;

    virtual IAssociatedData *getAssociatedData() const = 0;

};

}
}

