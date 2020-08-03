/*
 * FieldEnum.cpp
 *
 *  Created on: Jul 31, 2020
 *      Author: ballance
 */

#include "FieldEnum.h"

namespace vsc {

FieldEnum::FieldEnum(
		const std::string	&name,
		bool				is_rand,
		EnumTypeInfo		*info) : Field(name, is_rand), m_info(info) {
	// TODO Auto-generated constructor stub

}

FieldEnum::~FieldEnum() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
