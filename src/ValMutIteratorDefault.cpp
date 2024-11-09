/*
 * ValMutIteratorDefault.cpp
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
#include "vsc/dm/impl/ValRefStruct.h"
#include "ValMutIteratorDefault.h"
#include "TaskAssignValRef.h"


namespace vsc {
namespace dm {


ValMutIteratorDefault::ValMutIteratorDefault(const ValRef &src) :
    ValIteratorDefault(src) {

}

ValMutIteratorDefault::~ValMutIteratorDefault() {

}

void ValMutIteratorDefault::setVal(const ValRef &v) {
    m_path.back() = v;
}

void ValMutIteratorDefault::setFieldVal(int32_t idx, const ValRef &v) {
    if (m_numFields == -1) {
        updateNumFields();
    }
    if (idx < m_numFields) {
        ValRefStruct vs(m_path.back());
        vs.getFieldRef(idx) = v;        
    }
}

}
}
