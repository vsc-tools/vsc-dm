/*
 * DataTypeKind.h
 *
 *  Created on: Nov 18, 2021
 *      Author: mballance
 */

#pragma one

namespace vsc {

enum class DataTypeKind {
	Bool,
	Enum,
	Int
};

const char *toString(DataTypeKind k);

} /* namespace vsc */
