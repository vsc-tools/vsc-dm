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
#include "vsc/dm/impl/ValRef.h"

namespace vsc {
namespace dm {



class ValRefInt : public ValRef {
public:

    ValRefInt(ValRef &&rhs) : ValRef(rhs) { }

    ValRefInt(
        intptr_t    v,
        bool        is_signed=true,
        int32_t     bits=INTPTR_WIDTH) : 
            ValRef(v, Flags::None),
            m_isSigned(is_signed), m_bits(bits) { }

    virtual ~ValRefInt() { }

    intptr_t get_val_s() const {
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            return *reinterpret_cast<intptr_t *>(m_vp);
        } else {
            return static_cast<intptr_t>(m_vp);
        }
    }

    uintptr_t get_val_u() const {
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            return *reinterpret_cast<uintptr_t *>(m_vp);
        } else {
            return m_vp;
        }
    }

    uintptr_t val() const {
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            return *reinterpret_cast<uintptr_t *>(m_vp);
        } else {
            return m_vp;
        }
    }

    void set_val(uintptr_t v) {
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            *reinterpret_cast<uintptr_t *>(m_vp) = v;
        } else {
            m_vp = v;
        }
    }

    static void add(
        ValRefInt          &dst,
        const ValRefInt    &lhs,
        const ValRefInt    &rhs) {
        dst.set_val(lhs.val() + rhs.val());
    }


protected:
    bool                m_isSigned;
    int32_t             m_bits;

};

class ValRefUInt : public ValRefInt {
public:
    ValRefUInt() : ValRefInt(0, INTPTR_WIDTH) { }

    ValRefUInt(const ValRefUInt &rhs) : 
        ValRefInt(rhs.m_vp, rhs.m_isSigned, rhs.m_bits) { }

    ValRefUInt(
        uintptr_t   v,
        int32_t     bits=INTPTR_WIDTH) : ValRefInt(v, false, bits) { }

    static void add(
        ValRefUInt          &dst,
        const ValRefUInt    &lhs,
        const ValRefUInt    &rhs) {
        dst.set_val(lhs.val() + rhs.val());
    }

};

} /* namespace dm */
} /* namespace vsc */


