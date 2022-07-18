/*
 * ModelFieldVecRoot.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#include "vsc/IContext.h"
#include "ModelFieldVecRoot.h"

namespace vsc {

ModelFieldVecRoot::ModelFieldVecRoot(
		IContext			*ctxt,
		IDataType			*type,
		const std::string	&name) :
				ModelFieldVec(ctxt), m_type(type), m_name(name) {

}

ModelFieldVecRoot::~ModelFieldVecRoot() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
