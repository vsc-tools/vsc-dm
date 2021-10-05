/*
 * rand_obj.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */
#pragma once

#include <functional>
#include <string>
#include "attr_base.h"
#include "scope.h"

namespace vsc {
namespace facade {

class rand_obj : public attr_base {
public:
	rand_obj(const scope &s);

	virtual ~rand_obj();

	virtual bool randomize();

	virtual bool randomize_with(
			const std::function<void()>	&body);

private:


};

} /* namespace facade */
} /* namespace vsc */

