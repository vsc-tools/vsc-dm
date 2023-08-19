/*
 * TypeExprVal.cpp
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */
#include "vsc/dm/IDataType.h"
#include "TypeExprVal.h"

namespace vsc {
namespace dm {

TypeExprVal::TypeExprVal(
    IDataType       *type,
    ValData         v) : m_val(v, type, ValRef::Flags::None) {
	// TODO Auto-generated constructor stub

}

TypeExprVal::TypeExprVal(const ValRef &v) : m_val(v) {

}

TypeExprVal::~TypeExprVal() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */

