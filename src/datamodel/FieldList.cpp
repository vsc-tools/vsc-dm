/*
 * FieldArray.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#include "FieldList.h"

namespace vsc {

FieldList::FieldList(
		const std::string		&name,
		bool					is_scalar,
		int32_t					width,
		bool					is_signed,
		bool					is_rand,
		bool					is_rand_sz) : FieldComposite(name, is_rand),
				m_is_scalar(is_scalar), m_width(width), m_is_signed(is_signed),
				m_is_rand_sz(is_rand_sz) {
	// TODO Auto-generated constructor stub

}

FieldList::~FieldList() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
