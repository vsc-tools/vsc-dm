/*
 * ValIteratorDefault.cpp
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
#include "vsc/dm/impl/ValRefArr.h"
#include "vsc/dm/impl/ValRefStruct.h"
#include "ValIteratorDefault.h"


namespace vsc {
namespace dm {


ValIteratorDefault::ValIteratorDefault(const ValRef &root) : 
    m_root(root), m_numFields(-1) {
    reset();
}

ValIteratorDefault::~ValIteratorDefault() {

}

    // Resets the iterator to its initial point
void ValIteratorDefault::reset() {
    m_numFields = -1;
    m_path.clear();
    m_path.push_back(m_root);
}

    // Gets the data type of the current value
IDataType *ValIteratorDefault::getDataType() {

}

    // Gets the value of the current field
const ValRef &ValIteratorDefault::getVal() {
    return m_path.back();
}

    // Returns the number of fields in the current scope
int32_t ValIteratorDefault::numFields() {
    if (m_numFields == -1) {
        updateNumFields();
    }
    return m_numFields;
}

IDataType *ValIteratorDefault::getFieldType(int32_t idx) {
    if (m_numFields == -1) {
        updateNumFields();
    }
    if (idx < m_numFields) {
        ValRefStruct sv(m_path.back());
        return sv.getFieldRef(idx).type();
    } else {
        return 0;
    }
}

std::string ValIteratorDefault::getFieldName(int32_t idx) {
    if (m_numFields == -1) {
        updateNumFields();
    }
    if (idx < m_numFields) {
        ValRefStruct sv(m_path.back());
        return sv.getFieldRef(idx).name();
    } else {
        return m_empty;
    }
}

const ValRef &ValIteratorDefault::getFieldVal(int32_t idx) {
    if (m_numFields == -1) {
        updateNumFields();
    }
    if (idx < m_numFields) {
        ValRefStruct sv(m_path.back());
        return sv.getFieldRef(idx);
    } else {
        return m_empty_val;
    }
}

    // Pushes into a specific field scope
bool ValIteratorDefault::push(int32_t idx) {
    if (m_numFields == -1) {
        updateNumFields();
    }
    if (idx < m_numFields) {
        ValRefStruct sv(m_path.back());
        ValRef sf = sv.getFieldRef(idx);
        m_path.push_back(sf);
        return true;
    } else {
        return false;
    }
}

    // Pops out of the current scope
bool ValIteratorDefault::pop() {
    if (m_path.size() > 1) {
        m_path.pop_back();
        return true;
    } else {
        return false;
    }
}

void ValIteratorDefault::visitDataTypeStruct(IDataTypeStruct *t) {
    ValRefStruct vs(m_path.back());
    m_numFields = vs.getNumFields();
}

void ValIteratorDefault::updateNumFields() {
    m_numFields = 0;
    m_path.back().type()->accept(m_this);
}

std::string ValIteratorDefault::m_empty;
ValRef ValIteratorDefault::m_empty_val;

}
}
