/**
 * ValRefPtr.h
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


class ValRefPtr : public ValRef {
public:
    ValRefPtr() { }

    ValRefPtr(const ValRef &rhs) : ValRef(rhs) { }

    virtual ~ValRefPtr() { }

    uintptr_t get_val() const {
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            return *reinterpret_cast<uintptr_t *>(m_vp);
        } else {
            return m_vp;
        }
    }

    template <class T> T *get_valT() const {
        return reinterpret_cast<T *>(get_val());
    }

    static uint32_t size() {
        return sizeof(void *);
    }

    ValRef val() const {
        uintptr_t vp = m_vp;
        Flags flags = m_flags;
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            vp = *reinterpret_cast<uintptr_t *>(m_vp);
            flags = (flags & ~Flags::IsPtr);
        }

        return ValRef(
            vp,
            type(),
            flags);
    }

    void set_val(uintptr_t v) {
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            *reinterpret_cast<uintptr_t *>(m_vp) = v;
        } else {
            m_vp = v;
        }
    }

};

}
}


