/*
 * FieldWideScalar.cpp
 *
 *  Created on: Jul 20, 2020
 *      Author: ballance
 */

#include "FieldWideScalar.h"

namespace vsc {

FieldWideScalar::FieldWideScalar(
		const std::string			&name,
		int32_t						width,
		bool						is_signed,
		bool						is_rand) : FieldScalar(name, width, is_signed, is_rand) {
	// TODO Auto-generated constructor stub

}

FieldWideScalar::~FieldWideScalar() {
	// TODO Auto-generated destructor stub
}

}
