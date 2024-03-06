/*
 * TaskEvalBinOpInt.cpp
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
#include "vsc/dm/IContext.h"
#include "TaskEvalBinOpInt.h"


namespace vsc {
namespace dm {


TaskEvalBinOpInt::TaskEvalBinOpInt(IContext *ctxt) : m_ctxt(ctxt) {

}

TaskEvalBinOpInt::~TaskEvalBinOpInt() {

}

ValRefInt TaskEvalBinOpInt::eval(
        const ValRefInt         &lhs,
        BinOp                   op,
        const ValRefInt         &rhs,
        int32_t                 width) {
    ValRefInt ret = ValRefInt(ValRef());

    if (lhs.bits() > width) {
        width = lhs.bits();
    }
    if (rhs.bits() > width) {
        width = rhs.bits();
    }

    bool is_signed = (lhs.is_signed() && rhs.is_signed());

    switch (op) {
	    case BinOp::Eq: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() == rhs.get_val_s()),
                        false,
                        1);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() == rhs.get_val_s()),
                        false,
                        1);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::Ne: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() != rhs.get_val_s()),
                        false,
                        1);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() != rhs.get_val_s()),
                        false,
                        1);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::Gt: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() > rhs.get_val_s()),
                        false,
                        1);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() > rhs.get_val_s()),
                        false,
                        1);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::Ge: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() >= rhs.get_val_s()),
                        false,
                        1);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() >= rhs.get_val_s()),
                        false,
                        1);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::Lt: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() < rhs.get_val_s()),
                        false,
                        1);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() < rhs.get_val_s()),
                        false,
                        1);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::Le: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() <= rhs.get_val_s()),
                        false,
                        1);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() <= rhs.get_val_s()),
                        false,
                        1);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::Add: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() + rhs.get_val_s()),
                        is_signed,
                        width);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        lhs.get_val_u() + rhs.get_val_u(),
                        is_signed,
                        width);
                }
            } else {
                ret = Add(lhs, rhs);
            }
        } break;
        case BinOp::Sub: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() - rhs.get_val_s()),
                        is_signed,
                        width);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        lhs.get_val_u() - rhs.get_val_u(),
                        is_signed,
                        width);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::Div: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() / rhs.get_val_s()),
                        is_signed,
                        width);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        lhs.get_val_u() / rhs.get_val_u(),
                        is_signed,
                        width);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::Mul: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() * rhs.get_val_s()),
                        is_signed,
                        width);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        lhs.get_val_u() * rhs.get_val_u(),
                        is_signed,
                        width);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::Mod: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() % rhs.get_val_s()),
                        is_signed,
                        width);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        lhs.get_val_u() % rhs.get_val_u(),
                        is_signed,
                        width);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::BinAnd: {
            if (width <= 64) {
                ret = m_ctxt->mkValRefInt(
                    (lhs.get_val_u() & rhs.get_val_u()),
                    false,
                    width
                );
            } else {
                // TODO:
            }
        } break;
        case BinOp::BinOr: {
            if (width <= 64) {
                ret = m_ctxt->mkValRefInt(
                    (lhs.get_val_u() | rhs.get_val_u()),
                    false,
                    width
                );
            } else {
                // TODO:
            }
        } break;
        case BinOp::BinXor: {
            if (width <= 64) {
                ret = m_ctxt->mkValRefInt(
                    (lhs.get_val_u() ^ rhs.get_val_u()),
                    false,
                    width
                );
            } else {
                // TODO:
            }
        } break;
        case BinOp::LogAnd: {
            if (width <= 64) {
                ret = m_ctxt->mkValRefInt(
                    (lhs.get_val_u() && rhs.get_val_u()),
                    false,
                    1
                );
            } else {
                // TODO:
            }
        } break;
        case BinOp::LogOr: {
            if (width <= 64) {
                ret = m_ctxt->mkValRefInt(
                    (lhs.get_val_u() || rhs.get_val_u()),
                    false,
                    1
                );
            } else {
                // TODO:
            }
        } break;
        case BinOp::LogXor: {
            if (width <= 64) {
                ret = m_ctxt->mkValRefInt(
                    ((lhs.get_val_u() != 0) ^ (rhs.get_val_u() != 0)),
                    false,
                    1
                );
            } else {
                // TODO:
            }
        } break;
        case BinOp::Sll: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() << rhs.get_val_s()),
                        is_signed,
                        width);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        lhs.get_val_u() << rhs.get_val_u(),
                        is_signed,
                        width);
                }
            } else {
                // TODO:
            }
        } break;
        case BinOp::Srl: {
            if (width <= 64) {
                if (is_signed) {
                    ret = m_ctxt->mkValRefInt(
                        (lhs.get_val_s() >> rhs.get_val_s()),
                        is_signed,
                        width);
                } else {
                    ret = m_ctxt->mkValRefInt(
                        lhs.get_val_u() >> rhs.get_val_u(),
                        is_signed,
                        width);
                }
            } else {
                // TODO:
            }
        } break;
    }
    return ret;
}

ValRefInt TaskEvalBinOpInt::Add(const ValRefInt &lhs, const ValRefInt &rhs) {
    return ValRefInt(ValRef());
}

}
}
