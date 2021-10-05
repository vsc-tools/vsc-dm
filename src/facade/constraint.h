/*
 * constraint.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#pragma once
#include <functional>
#include "scope.h"

namespace vsc {
namespace facade {

class rand_obj;

class constraint {
public:
	constraint(const scope &s, const std::function<void()> &body);

	virtual ~constraint();

private:
	std::function<void()>				m_body;

};

} /* namespace facade */
} /* namespace vsc */

