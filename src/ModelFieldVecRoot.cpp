/*
 * ModelFieldVecRoot.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#include "ModelFieldVecRoot.h"

namespace vsc {

ModelFieldVecRoot::ModelFieldVecRoot(
		DataType			*type,
		const std::string	&name,
		ModelField			*size) :
				ModelFieldVec(size), m_type(type), m_name(name) {

}

ModelFieldVecRoot::~ModelFieldVecRoot() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
