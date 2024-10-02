/**
 * TypeExprStructLiteral.h
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
#include "vsc/dm/ITypeExprStructLiteral.h"

namespace vsc {
namespace dm {



class TypeExprStructLiteral :
    public virtual ITypeExprStructLiteral {
public:
    TypeExprStructLiteral(
        IDataTypeStruct                 *type,
        bool                            owned,
        const std::vector<ITypeExpr *>  &vals);

    virtual ~TypeExprStructLiteral();

    virtual IDataTypeStruct *getDataType() const override {
        return m_type.get();
    }

    virtual const std::vector<ITypeExprUP> &getValue() const override {
        return m_vals;
    }

    virtual void accept(IVisitor *v) override;

private:
    IDataTypeStructUP           m_type;
    std::vector<ITypeExprUP>    m_vals;

};

}
}


