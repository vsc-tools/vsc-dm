/*
 * Copyright 2019-2023 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

class TaskIsTypeFieldRef : public virtual VisitorBase {
public:

    TaskIsTypeFieldRef() : m_ret(false) { }

    bool eval(ITypeField *f) {
        m_ret = false;
        f->accept(m_this);
        return m_ret;
    }

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override { }

	virtual void visitTypeFieldRef(ITypeFieldRef *f) override {
        m_ret = true;
    }

protected:
    bool                    m_ret;

};

}
}
