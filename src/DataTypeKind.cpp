/*
 * DataTypeKind.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: mballance
 */

#include "DataTypeKind.h"

namespace vsc {
namespace dm {

const char *toString(DataTypeKind k) {
	switch (k) {
	case DataTypeKind::Bool: return "Bool";
	case DataTypeKind::Enum: return "Enum";
	case DataTypeKind::Int: return "Int";
	default: return "DataTypeKind::Unknown";
	}
}

}
} /* namespace vsc */
