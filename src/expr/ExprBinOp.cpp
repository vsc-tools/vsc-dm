/*
 * ExprBinOp.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */
#include "ExprBinOp.h"

namespace vsc {

const char *toString(ExprBinOp op) {
	switch (op) {
	case BinOp_Eq: return "==";
	case BinOp_Ne: return "!=";
	case BinOp_Gt: return ">";
	case BinOp_Ge: return ">=";
	case BinOp_Lt: return "<";
	case BinOp_Le: return "<=";
	case BinOp_Add: return "+";
	case BinOp_Sub: return "-";
	case BinOp_Div: return "/";
	case BinOp_Mul: return "*";
	case BinOp_Mod: return "%";
	case BinOp_And: return "&";
	case BinOp_Or: return "|";
	case BinOp_Sll: return "<<";
	case BinOp_Srl: return ">>";
	case BinOp_Xor: return "^";
	case BinOp_Not: return "~";
	}
	return "UNK_OP";
}

}



