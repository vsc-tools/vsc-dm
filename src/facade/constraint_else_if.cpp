/*
 * else_if.cpp
 *
 *  Created on: Aug 12, 2021
 *      Author: mballance
 */

#include "constraint_else_if.h"

namespace vsc {
namespace facade {

constraint_else_if::constraint_else_if(
		const expr						&cond,
		const std::function<void()>		&body,
		const char						*file,
		int32_t							line) {
	// TODO Auto-generated constructor stub

}

constraint_else_if::~constraint_else_if() {
	// TODO Auto-generated destructor stub
}

constraint_else_then constraint_else_if::else_then(
		const std::function<void()>		&body,
		const char						*file,
		int32_t							line) {

}

constraint_else_if constraint_else_if::else_if(
		const expr						&cond,
		const std::function<void()>		&body,
		const char						*file,
		int32_t							line) {

}

} /* namespace facade */
} /* namespace vsc */
