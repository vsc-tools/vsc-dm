/*
 * ExprBinOp.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRBINOP_H_
#define SRC_EXPR_EXPRBINOP_H_

namespace vsc {

enum ExprBinOp {
    BinOp_Eq,
    BinOp_Ne,
    BinOp_Gt,
    BinOp_Ge,
    BinOp_Lt,
    BinOp_Le,
    BinOp_Add,
    BinOp_Sub,
    BinOp_Div,
    BinOp_Mul,
    BinOp_Mod,
    BinOp_And,
    BinOp_Or,
    BinOp_Sll,
    BinOp_Srl,
    BinOp_Xor,
    BinOp_Not,
};

const char *toString(ExprBinOp op);

}



#endif /* SRC_EXPR_EXPRBINOP_H_ */
