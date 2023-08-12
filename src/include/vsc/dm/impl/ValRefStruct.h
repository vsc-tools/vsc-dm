/**
 * ValRefStruct.h
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
#include "vsc/dm/impl/ValRef.h"
#include "vsc/dm/IDataTypeStruct.h"

namespace vsc {
namespace dm {



class ValRefStruct : public ValRef {
public:

    ValRefStruct(ValRef &rhs) : ValRef(rhs) { }

    ValRefStruct(
        IContext            *ctxt,
        IDataTypeStruct     *type) : 
            ValRef(
                Val::Val2ValPtr(ctxt->mkVal(type->getByteSize())),
                type,
                Flags::Owned) {
        type->initVal(vp());
    }

    virtual ~ValRefStruct() { }

    int32_t getNumFields() const {
        return dynamic_cast<IDataTypeStruct *>(type())->getFields().size();
    }

    ValRef getField(int32_t i) {
        char *ptr = reinterpret_cast<char *>(m_vp);
        ITypeField *field = dynamic_cast<IDataTypeStruct *>(type())->getField(i);
        return ValRef(
            *reinterpret_cast<uintptr_t *>(&ptr[field->getOffset()]),
            field,
            Flags::None
        );
    }

    ValRef getFieldRef(int32_t i) {
        char *ptr = reinterpret_cast<char *>(m_vp);
        ITypeField *field = dynamic_cast<IDataTypeStruct *>(type())->getField(i);
        fprintf(stdout, "getFieldRef: %d %d\n", i, field->getOffset());
        return ValRef(
            reinterpret_cast<uintptr_t>(&ptr[field->getOffset()]),
            field,
            Flags::IsPtr
        );
    }


};

} /* namespace dm */
} /* namespace vsc */


