/*
 * ModelCoverpoint.cpp
 *
 *  Created on: Nov 15, 2021
 *      Author: mballance
 */

#include "ModelCoverpoint.h"

namespace vsc {

ModelCoverpoint::ModelCoverpoint(
		ModelExpr			*target,
		const std::string	&name,
		ModelExpr			*iff) : m_target(target), m_name(name), m_iff(iff) {
	// TODO Auto-generated constructor stub

}

ModelCoverpoint::~ModelCoverpoint() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
