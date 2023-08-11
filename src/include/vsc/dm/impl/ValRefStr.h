/**
 * ValRefStr.h
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
#include <string.h>
#include <string>
#include "vsc/dm/IContext.h"
#include "vsc/dm/impl/ValRef.h"

namespace vsc {
namespace dm {



class ValRefStr : public ValRef {
public:

    ValRefStr(ValRef &rhs) : ValRef(rhs) { }

    ValRefStr(
        IContext            *ctxt,
        const std::string   &init) : ValRef(
            Val::Val2ValPtr(ctxt->mkVal(sizeof(ValDataStr)+init.size())),
            Flags::Owned) { 
        ValDataStr *data = reinterpret_cast<ValDataStr *>(m_vp);
        strcpy(data->str, init.c_str());
        data->sz = init.size();
    }

    virtual ~ValRefStr() { 
    }

    int32_t size() const {
        Val *vp = Val::ValPtr2Val(m_vp);
        ValDataStr *data = reinterpret_cast<ValDataStr *>(m_vp);
        return data->sz;
    }

    const char *val() const {
        ValDataStr *data = reinterpret_cast<ValDataStr *>(m_vp);
        return data->str;
    }

    std::string val_s() const {
        ValDataStr *data = reinterpret_cast<ValDataStr *>(m_vp);
        return std::string(data->str);
    }

    void append(const std::string &rhs) {
        // TODO: bail if we're working with a non-owned string
        Val *vp = Val::ValPtr2Val(m_vp);
        ValDataStr *data = reinterpret_cast<ValDataStr *>(m_vp);

        if ((sizeof(ValDataStr)+rhs.size()+data->sz+1) <= vp->sz) {
            // Can just add on
            strcpy(&data->str[data->sz], rhs.c_str());
            data->sz += rhs.size();
        } else {
            // Need to increased the string size
            uint32_t new_sz = (2*data->sz)+rhs.size()+1;
            Val *vp_p = vp->p.cp->mkVal(new_sz);
            ValDataStr *data_p = reinterpret_cast<ValDataStr *>(Val::Val2ValPtr(vp_p));
            strcpy(&data_p->str[0], &data->str[0]);
            strcpy(&data_p->str[data->sz], rhs.c_str());
            m_vp = Val::Val2ValPtr(vp_p);
            vp->p.cp->freeVal(vp);
        }
    }

    void clear() {
        Val *vp = Val::ValPtr2Val(m_vp);
        ValDataStr *data = reinterpret_cast<ValDataStr *>(m_vp);
        data->str[0] = 0;
        data->sz = 0;
    }

};

} /* namespace dm */
} /* namespace vsc */


