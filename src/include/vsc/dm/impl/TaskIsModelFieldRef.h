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

class TaskIsModelFieldRef : public virtual VisitorBase {
public:

    TaskIsModelFieldRef() : m_ret(false) { }


    bool check(IModelField *f) {
        m_ret = false;
        f->accept(m_this);
        return m_ret;
    }

	virtual void visitModelField(IModelField *f) override { }

	virtual void visitModelFieldRef(IModelFieldRef *f) override {
        m_ret = true;
    }

	virtual void visitModelFieldRefRoot(IModelFieldRef *f) override {
        m_ret = true;
    }

	virtual void visitModelFieldRefType(IModelFieldTypeRef *f) override {
        m_ret = true;
    }

	virtual void visitModelFieldRoot(IModelFieldRoot *f) override {
        m_ret = true;
    }

protected:
    bool                    m_ret;

};

}
}
