/*
 * if_then.cpp
 *
 *  Created on: Aug 12, 2021
 *      Author: mballance
 */

#include "constraint_if_then.h"

namespace vsc {
namespace facade {

constraint_if_then::constraint_if_then(
		const expr						&cond,
		const std::function<void()>		&body,
		const char						*file,
		int32_t							lineno) {
	// TODO Auto-generated constructor stub

}

constraint_if_then::~constraint_if_then() {
	// TODO Auto-generated destructor stub
}

constraint_else_if constraint_if_then::else_if(
		const expr						&cond,
		const std::function<void()>		&body,
		const char						*file,
		int32_t							lineno) {

}

constraint_else_then constraint_if_then::else_then(
		const std::function<void()>		&body,
		const char						*file,
		int32_t							lineno) {

}

} /* namespace facade */
} /* namespace vsc */
