/*
 * TypeFieldRef.cpp
 *
 *  Created on: May 9, 2022
 *      Author: mballance
 */

#include "TypeFieldRef.h"

namespace vsc {
namespace dm {

TypeFieldRef::TypeFieldRef(
		const std::string		&name,
		IDataType				*type,
		TypeFieldAttr			attr) : TypeField(name, type, false, attr) {

}

TypeFieldRef::~TypeFieldRef() {
	// TODO Auto-generated destructor stub
}

int32_t TypeFieldRef::getByteSize() const {
    return ValRefInt::native_sz();
}

}
} /* namespace vsc */

