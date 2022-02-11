/*
 * ModelFieldVecRoot.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#include "ModelFieldVecRoot.h"

namespace vsc {

ModelFieldVecRoot::ModelFieldVecRoot(
		IDataType			*type,
		const std::string	&name,
		IModelField			*size) :
				ModelFieldVec(size), m_type(type), m_name(name) {

}

ModelFieldVecRoot::~ModelFieldVecRoot() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
