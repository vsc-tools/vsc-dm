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
    ValData         v) : m_type(type), m_val(v) {
	// TODO Auto-generated constructor stub

}

TypeExprVal::~TypeExprVal() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */

