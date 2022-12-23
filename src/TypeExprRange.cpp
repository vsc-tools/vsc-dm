/*
 * TypeExprRange.cpp
 *
 *  Created on: Jun 27, 2022
 *      Author: mballance
 */

#include "TypeExprRange.h"

namespace vsc {
namespace dm {

TypeExprRange::TypeExprRange(
		bool				is_single,
		ITypeExpr			*lower,
		ITypeExpr			*upper) :
			m_is_single(is_single),
			m_lower(lower),
			m_upper(upper) {

}

TypeExprRange::~TypeExprRange() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */

