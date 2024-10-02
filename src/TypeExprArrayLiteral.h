/**
 * TypeExprArrayLiteral.h
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
#include "vsc/dm/ITypeExprArrayLiteral.h"

namespace vsc {
namespace dm {



class TypeExprArrayLiteral :
    public virtual ITypeExprArrayLiteral {
public:
    TypeExprArrayLiteral(
        IDataTypeArray                     *arr_t,
        bool                                arr_t_owned,
        const std::vector<ITypeExpr *>      &vals);

    virtual ~TypeExprArrayLiteral();

    virtual IDataTypeArray *getDataType() const override {
        return m_arr_t.get();
    }

    virtual const std::vector<ITypeExprUP> &getValue() const override {
        return m_vals;
    }

    virtual void accept(IVisitor *v) override;

private:
    IDataTypeArrayUP                m_arr_t;
    std::vector<ITypeExprUP>        m_vals;

};

}
}


