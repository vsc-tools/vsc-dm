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
#include "vsc/dm/IValAlloc.h"
#include "vsc/dm/IValOps.h"
#include "vsc/dm/IDataType.h"
#include "vsc/dm/ITypeField.h"
#include "vsc/dm/Val.h"

#define VALREF_FLAGSET(e, flag) ((static_cast<uint32_t>(e) & static_cast<uint32_t>(flag)) != 0)
#define VALREF_SETFLAG(e, flag) (static_cast<ValRef::Flags>((static_cast<uint32_t>(e) | static_cast<uint32_t>(flag))))
#define VALREF_CLRFLAG(e, flag) (static_cast<ValRef::Flags>((static_cast<uint32_t>(e) & ~static_cast<uint32_t>(flag))))

namespace vsc {
namespace dm {

class IDataType;
class ITypeField;
class IValOps;


class ValRef {
public:
    enum class Flags {
        None     = 0,
        Void     = (1 << 0), // Does not hold a valid value
        Root     = (1 << 1), // 
        Owned    = (1 << 2), // Storage is owned by this handle
        IsPtr    = (1 << 3),
        HasField = (1 << 4),
        Mutable  = (1 << 5)
    };


public:
    ValRef() : m_vp(0), m_type_field(static_cast<IDataType *>(0)), m_flags(Flags::Void) { }
    
    ValRef(const ValRef &rhs) : 
        m_vp(rhs.m_vp), 
        m_type_field(rhs.m_type_field), 
        m_flags(rhs.m_flags) {

        if (VALREF_FLAGSET(m_flags, Flags::Owned)) {
            // The producer is passing ownership. Accept
            Val *v = Val::ValPtr2Val(m_vp);
            v->owner = this;
        }
    }

    void operator = (const ValRef &rhs) {
        m_vp = rhs.m_vp;
        m_type_field = rhs.m_type_field;
        m_flags = rhs.m_flags;

        if (VALREF_FLAGSET(m_flags, Flags::Owned)) {
            // The producer is passing ownership. Accept
            Val *v = Val::ValPtr2Val(m_vp);
            v->owner = this;
        }
    }

    ValRef(
        uintptr_t       vp,
        IDataType       *type,
        Flags           flags) : m_vp(vp), m_type_field(type), 
        m_flags(VALREF_CLRFLAG(flags, Flags::HasField)) { }

    ValRef(
        uintptr_t       vp,
        ITypeField      *field,
        Flags           flags) : m_vp(vp), m_type_field(field), 
            m_flags(VALREF_SETFLAG(flags, Flags::HasField)) { }

    virtual ~ValRef() {
        if (m_vp) {
            if (VALREF_FLAGSET(m_flags, Flags::Owned)) {
            Val *vp = Val::ValPtr2Val(m_vp);
            if (vp->owner == this) {
                if (type()) {
                    type()->finiVal(*this);
                }
                vp->p.ap->freeVal(vp);
            }
            }
        }
    }

    bool valid() const { return m_type_field.m_type; }

    Flags flags() const { return m_flags; }

    void set(const ValRef &rhs) {
        m_vp = rhs.m_vp;
        m_flags = rhs.m_flags;
        m_type_field = rhs.m_type_field;
    }

    void move(ValRef &rhs) {
        m_vp = rhs.m_vp;
        m_flags = rhs.m_flags;
        m_type_field = rhs.m_type_field;
        if (VALREF_FLAGSET(m_flags, Flags::Owned)) {
            rhs.m_vp = 0;
        }
    }

    bool isVoid() const { return VALREF_FLAGSET(m_flags, Flags::Void); }

    bool isMutable() const { return VALREF_FLAGSET(m_flags, Flags::Mutable); }

    void setWeakRef(const ValRef &rhs) {
        reset(); // Clear out prior value first
        m_vp = rhs.m_vp;
        m_flags = rhs.m_flags; // TODO: don't want this to pull along ownership
        m_type_field = rhs.m_type_field;
    }

    ValRef copyVal() const {
//        return ValRef(type()->copyVal(*this));
        return ValRef(type()->copyVal(*this));
//        return cp;
//        return type()->copyVal(*this);
    }

    ValRef toMutable() const {
        // We want 
        if (VALREF_FLAGSET(m_flags, Flags::Mutable)) {
            // This value is already mutable
            Flags flags = VALREF_CLRFLAG(m_flags, Flags::Owned);
            if (VALREF_FLAGSET(m_flags, Flags::HasField)) {
                return ValRef(m_vp, m_type_field.m_field, 
                    VALREF_CLRFLAG(m_flags, Flags::Owned));
            } else {
                return ValRef(m_vp, m_type_field.m_type, 
                    VALREF_CLRFLAG(m_flags, Flags::Owned));
            }
        } else {
            // TODO: maybe this is just a failure?
            fprintf(stdout, "Error: cannot make an immutable field mutable\n");

            // Create a copy and make it mutable
            ValRef cp(copyVal());
            cp.m_flags = VALREF_SETFLAG(cp.m_flags, Flags::Mutable);
            return cp;
        }
    }

    ValRef toImmutable() const {
        if (VALREF_FLAGSET(m_flags, Flags::HasField)) {
            return ValRef(m_vp, m_type_field.m_field, 
                VALREF_CLRFLAG(m_flags, Flags::Mutable));
        } else {
            return ValRef(m_vp, m_type_field.m_type, 
                VALREF_CLRFLAG(m_flags, Flags::Mutable));
        }
    }

    ValRef toUnowned() const {
        Flags flags = VALREF_CLRFLAG(m_flags, Flags::Owned);
        return ValRef(m_vp, m_type_field.m_type, flags);
    }

    void reset() {
        if (m_vp && (static_cast<uint32_t>(m_flags) & static_cast<uint32_t>(Flags::Owned))) {
            if (type()) {
                type()->finiVal(*this);
            }
            Val *vp = Val::ValPtr2Val(m_vp);
            vp->p.ap->freeVal(vp);
        }
        m_flags = VALREF_SETFLAG(m_flags, Flags::Void);
        m_type_field.m_type = 0;
    }

    std::string name() const {
        if (VALREF_FLAGSET(m_flags, Flags::HasField)) {
            return m_type_field.m_field->name();
        } else {
            return "";
        }
    }

    ITypeField *field() const { 
        if (VALREF_FLAGSET(m_flags, Flags::HasField)) {
            return m_type_field.m_field; 
        } else {
            return 0;
        }
    }

    IDataType *type() const {
        if (VALREF_FLAGSET(m_flags, Flags::HasField)) {
            return m_type_field.m_field->getDataType();
        } else {
            return m_type_field.m_type; 
        }
    }

    template <class T> T *typeT() const {
        return dynamic_cast<T *>(type());
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

}
}


namespace vsc {
namespace dm {

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

#undef VALREF_FLAGSET
#undef VALREF_SETFLAG
#undef VALREF_CLRFLAG

