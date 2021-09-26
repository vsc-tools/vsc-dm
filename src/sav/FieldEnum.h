/*
 * FieldEnum.h
 *
 *  Created on: Jul 31, 2020
 *      Author: ballance
 */

#pragma once
#include "EnumTypeInfo.h"
#include "sav/Field.h"

namespace vsc {

class FieldEnum : public Field {
public:
	FieldEnum(
			const std::string		&name,
			bool					is_rand,
			EnumTypeInfo			*info);

	virtual ~FieldEnum();

private:
	EnumTypeInfoSP					m_info;

};

} /* namespace vsc */

