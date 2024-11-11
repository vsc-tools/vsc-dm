/**
 * ValRefInt.h
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
#include <string.h>
#include "vsc/dm/IDataTypeInt.h"
#include "vsc/dm/impl/ValRef.h"

namespace vsc {
namespace dm {



class ValRefInt : public ValRef {
public:

    ValRefInt() : ValRef() { }

    ValRefInt(const ValRef &rhs) : ValRef(rhs) { }

    ValRefInt(
        uintptr_t            value,
        IDataTypeInt         *type,
        Flags                flags) : ValRef(value, type, flags) { }

    ValRefInt(
        intptr_t    v,
        bool        is_signed=true,
        int32_t     bits=sizeof(void *)*8) : 
            ValRef(v, static_cast<IDataType *>(0), Flags::None),
            m_isSigned(is_signed), m_bits(bits) { }

    virtual ~ValRefInt() { }

    void operator = (const ValRefInt &rhs) {
        ValRef::operator=(rhs);
    }

    // Storage layout changes once we exceed the bit-size
    // of a pointer.
    static int32_t native_sz() { return sizeof(void *)*8; }

    void clear() {
        if (bits() <= native_sz()) {
            set_val(0);
        } else {
            memset(reinterpret_cast<char *>(vp()), 0, bits()/8);
        }
    }

#ifdef UNDEFINED
    ValRefInt signExt(int32_t bits) {
        // Sign-extension creates a mutable copy of the data.
        if (bits <= native_sz()) {
            // Value fits
            if (is_signed()) {

            } else {

            }
        } else {
            // Need to allocate space for the value
            if (is_signed()) {
            } else {

            }
        }
    }
#endif

    int32_t bits() const {
        if (type()) {
            return dynamic_cast<IDataTypeInt *>(type())->getWidth();
        } else {
            return m_bits;
        }
    }

    bool is_signed() const {
        if (type()) {
            return dynamic_cast<IDataTypeInt *>(type())->isSigned();
        } else {
            return m_isSigned;
        }
    }

    intptr_t get_val_s() const {
        intptr_t ret = -1;
        int32_t nb = bits();
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            if (nb <= 8) {
                ret = *reinterpret_cast<int8_t *>(m_vp);
            } else if (nb <= 16) {
                ret = *reinterpret_cast<int16_t *>(m_vp);
            } else if (nb <= 32) {
                ret = *reinterpret_cast<int32_t *>(m_vp);
            } else if (nb <= 64) {
                ret = *reinterpret_cast<int64_t *>(m_vp);
            }
        } else {
            if (nb <= 8) {
                ret = static_cast<int8_t>(m_vp);
            } else if (nb <= 16) {
                ret = static_cast<int16_t>(m_vp);
            } else if (nb <= 32) {
                ret = static_cast<int32_t>(m_vp);
            } else if (nb <= 64) {
                ret = static_cast<int64_t>(m_vp);
            }
        }
        return ret;
    }

    uintptr_t get_val_u() const {
        uintptr_t ret = 0;
        int32_t nb = bits();
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            if (nb <= 8) {
                ret = *reinterpret_cast<uint8_t *>(m_vp);
            } else if (nb <= 16) {
                ret = *reinterpret_cast<uint16_t *>(m_vp);
            } else if (nb <= 32) {
                ret = *reinterpret_cast<uint32_t *>(m_vp);
            } else if (nb <= 64) {
                ret = *reinterpret_cast<uint64_t *>(m_vp);
            }
        } else {
            if (nb <= 8) {
                ret = static_cast<uint8_t>(m_vp);
            } else if (nb <= 16) {
                ret = static_cast<uint16_t>(m_vp);
            } else if (nb <= 32) {
                ret = static_cast<uint32_t>(m_vp);
            } else if (nb <= 64) {
                ret = static_cast<uint64_t>(m_vp);
            }
        }
        return ret;
    }

    void set_val(uintptr_t v) {
        int32_t nb = bits();
        if (nb < native_sz()) {
            v &= ((static_cast<uintptr_t>(1) << nb)-1);
        }
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            if (nb <= 8) {
                *reinterpret_cast<uint8_t *>(m_vp) = v;
            } else if (nb <= 16) {
                *reinterpret_cast<uint16_t *>(m_vp) = v;
            } else if (nb <= 32) {
                *reinterpret_cast<uint32_t *>(m_vp) = v;
            } else if (nb <= 64) {
                *reinterpret_cast<uint64_t *>(m_vp) = v;
            }
        } else {
            m_vp = v;
        }
    }

    static void add(
        ValRefInt          &dst,
        const ValRefInt    &lhs,
        const ValRefInt    &rhs) {
        dst.set_val(lhs.get_val_u() + rhs.get_val_u());
    }


protected:
    bool                m_isSigned;
    int32_t             m_bits;

};

class ValRefUInt : public ValRefInt {
public:
    ValRefUInt() : ValRefInt(0, true, native_sz()) { }

    ValRefUInt(const ValRefUInt &rhs) : 
        ValRefInt(rhs.m_vp, rhs.m_isSigned, rhs.m_bits) { }

    ValRefUInt(
        uintptr_t   v,
        int32_t     bits=sizeof(void *)*8) : ValRefInt(v, false, bits) { }

    // Math functions assume that all inputs are of the
    // same size / bitwidth
    static void add(
        ValRefUInt          &dst,
        const ValRefUInt    &lhs,
        const ValRefUInt    &rhs) {
        dst.set_val(lhs.get_val_u() + rhs.get_val_u());
    }

};

} /* namespace dm */
} /* namespace vsc */


