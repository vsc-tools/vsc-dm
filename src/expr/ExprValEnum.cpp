/*
 * ExprValEnum.cpp
 *
 *  Created on: Jul 31, 2020
 *      Author: ballance
 */

#include "ExprValEnum.h"

namespace vsc {

ExprValEnum::ExprValEnum(
		EnumTypeInfo		*info,
		int64_t				val) : ExprVal(ValType_Enum),
				m_info(info), m_val(val) {

}

ExprValEnum::~ExprValEnum() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
