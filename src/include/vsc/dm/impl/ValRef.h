/**
 * ValRef.h
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
#include <stdint.h>
#include "vsc/dm/IDataType.h"
#include "vsc/dm/ITypeField.h"
#include "vsc/dm/IValAlloc.h"
#include "vsc/dm/IValOps.h"
#include "vsc/dm/Val.h"

namespace vsc {
namespace dm {


class ValRef {
public:
    enum class Flags {
        None     = 0,
        Root     = (1 << 0),
        Owned    = (1 << 1),
        IsPtr    = (1 << 2),
        HasField = (1 << 3)
    };


public:
    ValRef() : m_vp(0), m_type_field(static_cast<IDataType *>(0)), m_flags(Flags::None) { }
    
    ValRef(const ValRef &rhs) : m_vp(rhs.m_vp), m_type_field(rhs.m_type_field), m_flags(rhs.m_flags) {
        // Implement move semantics
        /*
        if ((static_cast<uint32_t>(m_flags) & static_cast<uint32_t>(Flags::Owned))) {
            rhs.m_vp = 0;
        }
         */
    }

    ValRef(ValRef &rhs) : m_vp(rhs.m_vp), m_type_field(rhs.m_type_field), m_flags(rhs.m_flags) {
        // Implement move semantics
        if ((static_cast<uint32_t>(m_flags) & static_cast<uint32_t>(Flags::Owned))) {
            rhs.m_vp = 0;
        }
    }

    ValRef(ValRef &&rhs) : m_vp(rhs.m_vp), m_type_field(rhs.m_type_field), m_flags(rhs.m_flags) {
        // Implement move semantics
        if ((static_cast<uint32_t>(m_flags) & static_cast<uint32_t>(Flags::Owned))) {
            rhs.m_vp = 0;
        }
    }

    ValRef(
        uintptr_t       vp,
        Flags           flags) : m_vp(vp), m_flags(flags) { }

    ValRef(
        uintptr_t       vp,
        IDataType       *type,
        Flags           flags) : m_vp(vp), m_type_field(type), m_flags(flags) { }

    ValRef(
        uintptr_t       vp,
        ITypeField      *field,
        Flags           flags) : m_vp(vp), m_type_field(field), 
            m_flags(static_cast<Flags>(static_cast<uint32_t>(flags) | static_cast<uint32_t>(Flags::HasField))) { }

    virtual ~ValRef() { 
        if (m_vp && (static_cast<uint32_t>(m_flags) & static_cast<uint32_t>(Flags::Owned))) {
            if (type()) {
                type()->finiVal(vp());
            }
            Val *vp = Val::ValPtr2Val(m_vp);
            vp->p.ap->freeVal(vp);
        }
    }

    bool valid() const { return m_type_field.m_type; }

    void set(ValRef &rhs) {
        m_vp = rhs.m_vp;
        m_flags = rhs.m_flags;
        m_type_field = rhs.m_type_field;
        if ((static_cast<uint32_t>(m_flags) & static_cast<uint32_t>(Flags::Owned))) {
            rhs.m_vp = 0;
        }
    }

    void setWeakRef(const ValRef &rhs) {
        reset(); // Clear out prior value first
        m_vp = rhs.m_vp;
        m_flags = rhs.m_flags; // TODO: don't want this to pull along ownership
        m_type_field = rhs.m_type_field;
    }

    void reset() {
        if (m_vp && (static_cast<uint32_t>(m_flags) & static_cast<uint32_t>(Flags::Owned))) {
            if (type()) {
                type()->finiVal(vp());
            }
            Val *vp = Val::ValPtr2Val(m_vp);
            vp->p.ap->freeVal(vp);
        }
        m_type_field.m_type = 0;
    }

    std::string name() const {
        if ((static_cast<uint32_t>(m_flags) & static_cast<uint32_t>(Flags::HasField))) {
            return m_type_field.m_field->name();
        } else {
            return "";
        }
    }

    ITypeField *field() const { return m_type_field.m_field; }

    IDataType *type() const { 
        if ((static_cast<uint32_t>(m_flags) & static_cast<uint32_t>(Flags::HasField))) {
            return m_type_field.m_field->getDataType();
        } else {
            return m_type_field.m_type; 
        }
    }

    uintptr_t vp() const { return m_vp; }

protected:
    uintptr_t           m_vp;
    union TypeField {
        TypeField() : m_type(0) { }
        TypeField(IDataType *t) : m_type(t) { }
        TypeField(ITypeField *t) : m_field(t) { }
        IDataType       *m_type;
        ITypeField      *m_field;
    }                   m_type_field;
    Flags               m_flags;
};

static inline ValRef::Flags operator | (const ValRef::Flags lhs, const ValRef::Flags rhs) {
	return static_cast<ValRef::Flags>(
			static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

static inline ValRef::Flags operator & (const ValRef::Flags lhs, const ValRef::Flags rhs) {
	return static_cast<ValRef::Flags>(
			static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

} /* namespace dm */
} /* namespace vsc */


