/**
 * TaskMkValRef.h
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
#include "vsc/dm/IContext.h"
#include "vsc/dm/impl/ValRef.h"
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {



class TaskMkValRef :
    public virtual VisitorBase {
public:
    TaskMkValRef(IContext *ctxt);

    virtual ~TaskMkValRef();

    ValRef mk(IDataType *t);

	virtual void visitDataTypeArray(IDataTypeArray *t) override;

	virtual void visitDataTypeBool(IDataTypeBool *t) override;

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override;

	virtual void visitDataTypeInt(IDataTypeInt *t) override;

	virtual void visitDataTypeList(IDataTypeList *t) override;

	virtual void visitDataTypePtr(IDataTypePtr *t) override;

	virtual void visitDataTypeString(IDataTypeString *t) override;

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override;

private:
    IContext                *m_ctxt;
    ValRef                  m_val;

};

}
}


