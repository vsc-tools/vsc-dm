/**
 * TypeExprEnumRef.h
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
#include "vsc/dm/ITypeExprEnumRef.h"
#include "TypeExpr.h"

namespace vsc {
namespace dm {



class TypeExprEnumRef :
    public virtual ITypeExprEnumRef,
    public virtual TypeExpr {
public:
    TypeExprEnumRef(
        IDataTypeEnum       *enum_t,
        int32_t             enum_id);

    virtual ~TypeExprEnumRef();

    virtual IDataTypeEnum *getEnumType() override {
        return m_enum_t;
    }

    virtual int32_t getEnumeratorId() override {
        return m_enum_id;
    }

    virtual void accept(IVisitor *v) override {
        v->visitTypeExprEnumRef(this);
    }

private:
    IDataTypeEnum           *m_enum_t;
    int32_t                 m_enum_id;


};

}
}


