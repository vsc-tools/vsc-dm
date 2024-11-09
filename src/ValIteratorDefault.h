/**
 * ValIteratorDefault.h
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
#include <vector>
#include "vsc/dm/impl/ValRef.h"
#include "vsc/dm/impl/VisitorBase.h"
#include "vsc/dm/IValIterator.h"

namespace vsc {
namespace dm {



class ValIteratorDefault :
    public virtual IValIterator,
    public virtual VisitorBase {
public:
    ValIteratorDefault(const ValRef &src);

    virtual ~ValIteratorDefault();

    // Resets the iterator to its initial point
    virtual void reset() override;

    // Gets the data type of the current value
    virtual IDataType *getDataType() override;

    // Gets the value of the current field
    virtual const ValRef &getVal() override;

    // Returns the number of fields in the current scope
    virtual int32_t numFields() override;

    virtual IDataType *getFieldType(int32_t f) override;

    virtual const ValRef &getFieldVal(int32_t f) override;

    virtual std::string getFieldName(int32_t f) override;

    // Pushes into a specific field scope
    virtual bool push(int32_t idx) override;

    // Pops out of the current scope
    virtual bool pop() override;

    virtual void visitDataTypeStruct(IDataTypeStruct *t) override;

protected:
    void updateNumFields();

protected:
    static std::string      m_empty;
    static ValRef           m_empty_val;
    ValRef                  m_root;
    std::vector<ValRef>     m_path;
    int32_t                 m_numFields;

};


}
}


