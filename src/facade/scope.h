/*
 * scope.h
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include <typeinfo>
#include "scope_base.h"

namespace vsc {
namespace facade {

class scope : public scope_base {
public:

	scope(const char *name) : scope_base(name) { }

	scope(const std::string &name) : scope_base(name) { }

	template <class T> scope(T *s) : scope_base(s, typeid(T)) { };

	template <class T> scope(
			T 					*s,
			const std::string	&name) : scope_base(s, typeid(T), name) { };

};

}
}
