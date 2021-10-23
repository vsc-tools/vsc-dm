/*
 * BinOp.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once

namespace vsc {

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
	LogAnd,
	LogOr,
	Sll,
	Srl,
	Xor,
	Not
};

} /* namespace vsc */

