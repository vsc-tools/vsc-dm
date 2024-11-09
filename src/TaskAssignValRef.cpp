/*
 * TaskAssignValRef.cpp
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
#include "vsc/dm/impl/TaskIsDataTypeInt.h"
#include "vsc/dm/impl/TaskIsDataTypeStr.h"
#include "TaskAssignValRef.h"


namespace vsc {
namespace dm {


TaskAssignValRef::TaskAssignValRef(
        const ValRef    &lhs,
        const ValRef    &rhs) : m_ret(false), m_lhs(lhs), m_rhs(rhs) {

}

TaskAssignValRef::~TaskAssignValRef() {

}

bool TaskAssignValRef::assign() {
    m_ret = false;
    m_lhs.type()->accept(m_this);
    return m_ret;
}

void TaskAssignValRef::visitDataTypeInt(IDataTypeInt *t) {
    if (t == m_rhs.type()) {
        // Easy
    } else {
        IDataTypeInt *rhs_t = TaskIsDataTypeInt().check(m_rhs.type());
        if (rhs_t) {

        }
    }
}

void TaskAssignValRef::visitDataTypeString(IDataTypeString *t) {
    if (m_rhs.type() == t) {

    }
}

}
}
