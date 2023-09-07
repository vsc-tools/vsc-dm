/*
 * TypeConstraintForeach.cpp
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
#include "TypeConstraintForeach.h"


namespace vsc {
namespace dm {


TypeConstraintForeach::TypeConstraintForeach(
    IContext                *ctxt,
    ITypeExpr               *target,
    bool                    target_owned,
    const std::string       &iter_name,
    ITypeConstraint         *body,
    bool                    body_owned) : 
        m_target(target, target_owned), m_body(body, body_owned) {
    IDataTypeInt *ui32 = ctxt->findDataTypeInt(true, 32);
    addVariable(ctxt->mkTypeFieldPhy(
        iter_name,
        ui32,
        false,
        TypeFieldAttr::NoAttr,
        ctxt->mkValRefInt(0, false, 32)));

}

TypeConstraintForeach::~TypeConstraintForeach() {

}

}
}
