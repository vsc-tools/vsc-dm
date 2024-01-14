/**
 * TaskIsFieldValPtr.h
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
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {



class TaskIsFieldValPtr : public virtual VisitorBase {
public:

    virtual ~TaskIsFieldValPtr() { }

    bool check(vsc::dm::ITypeField *t) {
        m_ret = false;
        t->accept(m_this);
        return m_ret;
    }

    bool check(vsc::dm::IDataType *t) {
        m_ret = true;
        t->accept(m_this);
        return m_ret;
    }

	virtual void visitDataTypeBool(IDataTypeBool *t) override { 
        m_ret = true;
    }

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override { 
        m_ret = true;
    }

	virtual void visitDataTypeInt(IDataTypeInt *t) override { 
        m_ret = true;
    }

	virtual void visitDataTypePtr(IDataTypePtr *t) override { 
        m_ret = true;
    }

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {
        m_ret = false;
    }

	virtual void visitDataTypeWrapper(IDataTypeWrapper *t) override {
        t->getDataTypePhy()->accept(m_this);
    }

	virtual void visitTypeFieldRef(ITypeFieldRef *f) override {
        m_ret = true;
    }

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override {
        f->getDataType()->accept(m_this);
    }

private:
    bool            m_ret;

};

} /* namespace dm */
} /* namespace vsc */


