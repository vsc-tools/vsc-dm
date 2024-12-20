/**
 * ValOpsDelegatorBase.h
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
#include "vsc/dm/IValOpsDelegator.h"
#include "vsc/dm/impl/ValRef.h"

namespace vsc {
namespace dm {



class ValOpsDelegatorBase :
    public virtual IValOps,
    public virtual IValOpsDelegator {
public:

    virtual ~ValOpsDelegatorBase() { }

    virtual void setValOps(IValOps *ops) override {
        m_ops = ops;
    }

    virtual IValOps *getValOps() const override {
        return m_ops;
    }

    virtual void initVal(ValRef &v) override {
        m_ops->initVal(v);
    }

    virtual void finiVal(ValRef &v) override {
        m_ops->finiVal(v);
    }

    virtual ValRef copyVal(const ValRef &src) override {
        return m_ops->copyVal(src);
    }

    virtual vsc::dm::IValIterator *mkValIterator(const vsc::dm::ValRef &src) override {
        return m_ops->mkValIterator(src);
    }

    virtual vsc::dm::IValMutIterator *mkValMutIterator(const vsc::dm::ValRef &src) override {
        return m_ops->mkValMutIterator(src);
    }

protected:
    IValOps                 *m_ops;
};

} /* namespace dm */
} /* namespace vsc */


