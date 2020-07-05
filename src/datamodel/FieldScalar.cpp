/*
 * FieldScalar.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#include "FieldScalar.h"

namespace vsc {

FieldScalar::FieldScalar(
		const std::string		&name,
		int32_t					width,
		bool					is_signed,
		bool					is_rand) : Field(name, is_rand) {
	// TODO Auto-generated constructor stub

}

FieldScalar::~FieldScalar() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
