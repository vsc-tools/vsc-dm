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
	constraint(const std::function<void()> &body);

	constraint(const std::string &name, const std::function<void()> &body);

	virtual ~constraint();

	const std::string &name() const { return m_name; }

	const std::function<void()> &body() const { return m_body; }

private:
	std::string							m_name;
	std::function<void()>				m_body;

};

} /* namespace facade */
} /* namespace vsc */

