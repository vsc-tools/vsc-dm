/*
 * rand_obj.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */
#pragma once

#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "attr_base.h"
#include "scope.h"

namespace vsc {
namespace facade {

class constraint;

class rand_obj : public attr_base {
public:
	rand_obj(const scope &s);

	virtual ~rand_obj();

	virtual bool randomize();

	virtual bool randomize_with(
			const std::function<void()>	&body);

	void add_constraint(constraint *c);

	void build_constraints();

private:
	std::vector<constraint *>					m_constraints;
	std::unordered_map<std::string,int32_t>		m_constraint_name_m;
	std::unordered_set<int32_t>					m_constraint_en_s;


};

} /* namespace facade */
} /* namespace vsc */

