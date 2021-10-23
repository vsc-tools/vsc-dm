/*
 * constraint_foreach.cpp
 *
 *  Created on: Oct 17, 2021
 *      Author: mballance
 */

#include "constraint_foreach.h"

namespace vsc {
namespace facade {

constraint_foreach::constraint_foreach(
		const expr								&target,
		const std::function<void(uint32_t i)>	&body,
		const char								*file,
		int32_t									lineno) {
	// TODO Auto-generated constructor stub

}

constraint_foreach::~constraint_foreach() {
	// TODO Auto-generated destructor stub
}

} /* namespace facade */
} /* namespace vsc */
