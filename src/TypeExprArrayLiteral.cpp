/*
 * TypeExprArrayLiteral.cpp
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
#include "TypeExprArrayLiteral.h"


namespace vsc {
namespace dm {


TypeExprArrayLiteral::TypeExprArrayLiteral(
        IDataTypeArray                     *arr_t,
        bool                                arr_t_owned,
        const std::vector<ITypeExpr *>      &vals) :
        m_arr_t(arr_t, arr_t_owned) {
    for (std::vector<ITypeExpr *>::const_iterator
        it=vals.begin();
        it!=vals.end(); it++) {
        m_vals.push_back(ITypeExprUP(*it));
    }
}

TypeExprArrayLiteral::~TypeExprArrayLiteral() {

}

void TypeExprArrayLiteral::accept(IVisitor *v) {
    v->visitTypeExprArrayLiteral(this);
}

}
}
