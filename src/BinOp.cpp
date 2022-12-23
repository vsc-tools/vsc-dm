/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * BinOp.cpp
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#include "vsc/dm/BinOp.h"

namespace vsc {
namespace dm {

const char *BinOp2Str_s(BinOp op) {
	switch (op) {
	case BinOp::Eq: return "Eq";
	case BinOp::Ne: return "Ne";
	case BinOp::Gt: return "Gt";
	case BinOp::Ge: return "Ge";
	case BinOp::Lt: return "Lt";
	case BinOp::Le: return "Le";
	case BinOp::Add: return "Add";
	case BinOp::Sub: return "Sub";
	case BinOp::Div: return "Div";
	case BinOp::Mul: return "Mul";
	case BinOp::Mod: return "Mod";
	case BinOp::BinAnd: return "BinAnd";
	case BinOp::BinOr: return "BinOr";
	case BinOp::LogAnd: return "LogAnd";
	case BinOp::LogOr: return "LogOr";
	case BinOp::Sll: return "Sll";
	case BinOp::Srl: return "Srl";
	case BinOp::Xor: return "Xor";
	case BinOp::Not: return "Not";
	default: return "BinOp::Unknown";
	}
}

}
} /* namespace vsc */
