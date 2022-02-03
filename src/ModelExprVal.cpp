/*
 * ModelExprVal.cpp
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#include "ModelExprVal.h"

namespace vsc {

ModelExprVal::ModelExprVal() {

}

ModelExprVal::ModelExprVal(const ModelVal &val) : m_val(val) {

}

ModelExprVal::~ModelExprVal() {
	// TODO Auto-generated destructor stub
}

void ModelExprVal::eval(IModelVal *dst) {
	dst->set(&m_val);
}

} /* namespace vsc */
