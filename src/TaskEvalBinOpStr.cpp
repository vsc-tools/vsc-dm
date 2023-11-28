/*
 * TaskEvalBinOpStr.cpp
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
#include "vsc/dm/impl/ValRefBool.h"
#include "TaskEvalBinOpStr.h"


namespace vsc {
namespace dm {


TaskEvalBinOpStr::TaskEvalBinOpStr(IContext *ctxt) : m_ctxt(ctxt) {

}

TaskEvalBinOpStr::~TaskEvalBinOpStr() {

}

ValRef TaskEvalBinOpStr::eval(
        const ValRefStr         &lhs,
        BinOp                   op,
        const ValRefStr         &rhs) {
    ValRef ret;

    switch (op) {
        case BinOp::Eq:
            ret = m_ctxt->mkValRefBool(!strcmp(lhs.val(), rhs.val()));
            break;
        case BinOp::Ne:
            ret = m_ctxt->mkValRefBool(strcmp(lhs.val(), rhs.val()));
            break;
        /*
        case BinOp::Gt,
        case BinOp::Ge,
        case BinOp::Lt,
        case BinOp::Le,
        case BinOp::Add,
        case BinOp::Sub,
        case BinOp::Div,
        case BinOp::Mul,
        case BinOp::Mod,
        case BinOp::BinAnd,
        case BinOp::BinOr,
        case BinOp::BinXor,
        case BinOp::LogAnd,
        case BinOp::LogOr,
        case BinOp::LogXor,
        case BinOp::Sll,
        case BinOp::Srl,
         */
    }

    return ret;
}

}
}
