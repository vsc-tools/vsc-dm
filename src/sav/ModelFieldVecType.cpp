/*
 * ModelFieldVecType.cpp
 *
 *  Created on: Jul 2, 2022
 *      Author: mballance
 */

#include "ModelFieldVecType.h"

namespace vsc {
namespace dm {

ModelFieldVecType::ModelFieldVecType(
		IContext		*ctxt,
		ITypeField		*type) : ModelFieldVec(ctxt), m_type(type) {
	// TODO Auto-generated constructor stub

}

ModelFieldVecType::~ModelFieldVecType() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */

