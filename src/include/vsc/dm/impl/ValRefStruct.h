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
#include "vsc/dm/IDataTypeStruct.h"
#include "vsc/dm/impl/TaskIsFieldValPtr.h"
#include "vsc/dm/impl/ValRef.h"

namespace vsc {
namespace dm {



class ValRefStruct : public ValRef {
public:
    friend class Context;

    ValRefStruct() {}

    ValRefStruct(const ValRef &rhs) : ValRef(rhs) { }

    virtual ~ValRefStruct() { }

    int32_t getNumFields() const {
        return dynamic_cast<IDataTypeStruct *>(type())->getFields().size();
    }

    ValRef getFieldRef(int32_t i) const {
        char *ptr;
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            ptr = reinterpret_cast<char *>(
                *reinterpret_cast<uintptr_t *>(m_vp));
        } else {
            ptr = reinterpret_cast<char *>(m_vp);
        }
        IDataTypeStruct *dt_s = typeT<IDataTypeStruct>();
        ITypeField *field = dt_s->getField(i);
        ValRef::Flags flags = static_cast<ValRef::Flags>(
            static_cast<uint32_t>(m_flags) & ~static_cast<uint32_t>(ValRef::Flags::Owned));

        if (TaskIsFieldValPtr().check(field)) {
            flags = flags | ValRef::Flags::IsPtr;
        } else {
            flags = static_cast<ValRef::Flags>(
                static_cast<uint32_t>(flags) & ~static_cast<uint32_t>(ValRef::Flags::IsPtr));
        }
        return ValRef(
            reinterpret_cast<uintptr_t>(&ptr[field->getOffset()]),
            field,
            flags
        );
    }

protected:

    ValRefStruct(
        ValData             vp,
        IDataTypeStruct     *type,
        ValRef::Flags        flags) : ValRef(vp, type, flags) { }

};

} /* namespace dm */
} /* namespace vsc */


