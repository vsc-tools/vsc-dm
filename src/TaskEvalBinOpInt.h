/**
 * TaskEvalBinOpInt.h
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
#include "vsc/dm/ITypeExprBin.h"
#include "vsc/dm/impl/ValRefInt.h"

namespace vsc {
namespace dm {



class TaskEvalBinOpInt {
public:
    TaskEvalBinOpInt(IContext *ctxt);

    virtual ~TaskEvalBinOpInt();

    ValRefInt eval(
        const ValRefInt         &lhs,
        BinOp                   op,
        const ValRefInt         &rhs,
        int32_t                 width=-1);

    ValRefInt Add(const ValRefInt &lhs, const ValRefInt &rhs);

private:
    IContext                    *m_ctxt;

};

}
}


