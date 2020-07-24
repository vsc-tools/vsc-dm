/*
 * FieldWideScalar.h
 *
 *  Created on: Jul 20, 2020
 *      Author: ballance
 */

#pragma once
#include "FieldScalar.h"

namespace vsc {

class FieldWideScalar : public FieldScalar {
public:
	FieldWideScalar(
			const std::string		&name,
			int32_t					width,
			bool					is_signed,
			bool					is_rand);

	virtual ~FieldWideScalar();
};

}
