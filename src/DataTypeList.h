/**
 * DataTypeList.h
 *
 * Copyright 2023 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author: 
 */
#pragma once
#include "vsc/dm/IDataTypeList.h"
#include "DataType.h"

namespace vsc {
namespace dm {



class DataTypeList :
    public virtual IDataTypeList,
    public virtual DataType {
public:
    DataTypeList(
        IDataType       *elem_t
    );

    virtual ~DataTypeList();

    virtual IDataType *getElemType() const override {
        return m_elem_t.get();
    }

    virtual void initVal(ValRef &v) override;

    virtual void finiVal(ValRef &v) override;

    virtual ValRef copyVal(const ValRef &src) override;

	virtual IModelField *mkRootField(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) override;

	virtual IModelField *mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type,
        const ValRef        &val) override;

    virtual void accept(IVisitor *v) override;

private:
    IDataTypeUP         m_elem_t;
};

}
}


