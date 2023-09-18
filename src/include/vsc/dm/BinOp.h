/*
 * BinOp.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once

namespace vsc {
namespace dm {

enum class BinOp {
	Eq,
	Ne,
	Gt,
	Ge,
	Lt,
	Le,
	Add,
	Sub,
	Div,
	Mul,
	Mod,
	BinAnd,
	BinOr,
	BinXor,
	LogAnd,
	LogOr,
	LogXor,
	Sll,
	Srl,
	Not
};

const char *BinOp2Str_s(BinOp op);


}
} /* namespace vsc */

