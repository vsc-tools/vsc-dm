/*
 * TaskMkValRef.cpp
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
#include "TaskMkValRef.h"


namespace vsc {
namespace dm {


TaskMkValRef::TaskMkValRef(IContext *ctxt) : m_ctxt(ctxt) {

}

TaskMkValRef::~TaskMkValRef() {

}

ValRef TaskMkValRef::mk(IDataType *t) {
    m_val = ValRef();
    t->accept(m_this);
    return m_val;
};

void TaskMkValRef::visitDataTypeArray(IDataTypeArray *t) { 

}

void TaskMkValRef::visitDataTypeBool(IDataTypeBool *t) { 
    m_val = m_ctxt->mkValRefBool(false);
}

void TaskMkValRef::visitDataTypeEnum(IDataTypeEnum *t) { 

}

void TaskMkValRef::visitDataTypeInt(IDataTypeInt *t) { 
    m_val = m_ctxt->mkValRefInt(0, t->isSigned(), t->getWidth());

}

void TaskMkValRef::visitDataTypeList(IDataTypeList *t) { }

void TaskMkValRef::visitDataTypePtr(IDataTypePtr *t) { }

void TaskMkValRef::visitDataTypeString(IDataTypeString *t) { 
    m_val = m_ctxt->mkValRefStr("");
}

void TaskMkValRef::visitDataTypeStruct(IDataTypeStruct *t) { 
    m_val = m_ctxt->mkValRefStruct(t);
}

}
}
