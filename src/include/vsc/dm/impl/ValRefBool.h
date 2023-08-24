/**
 * ValRefBool.h
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
#include "ValRef.h"

namespace vsc {
namespace dm {



class ValRefBool : public ValRef {
public:

    ValRefBool() { }

    ValRefBool(const ValRef &v) : ValRef(v) { }

    ValRefBool(ValRef &v) : ValRef(v) { }

    virtual ~ValRefBool() { }

    static int32_t size() { return sizeof(bool)*8; }

    bool get_val() const {
        bool ret;
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            ret = *reinterpret_cast<bool *>(m_vp);
        } else {
            ret = static_cast<bool>(m_vp);
        }
        return ret;
    }

    void set_val(bool v) {
        if ((m_flags & Flags::IsPtr) != Flags::None) {
            *reinterpret_cast<bool *>(m_vp) = v;
        } else {
            m_vp = v;
        }
    }

};

} /* namespace dm */
} /* namespace vsc */


