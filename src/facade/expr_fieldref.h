/*
 * expr_fieldref.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once

namespace vsc {
namespace facade {

class attr_base;

class expr_fieldref {
public:
	expr_fieldref();

	virtual ~expr_fieldref();

private:
	attr_base			*m_field;
};

} /* namespace facade */
} /* namespace vsc */

