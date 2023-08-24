/*
 * ModelExprVal.cpp
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#include "ModelExprVal.h"

namespace vsc {
namespace dm {

ModelExprVal::ModelExprVal() {

}

ModelExprVal::ModelExprVal(const IModelVal *val) /*: m_val(val) */ {

}

ModelExprVal::ModelExprVal(const IModelVal &val) /*: m_val(&val) */ {

}

ModelExprVal::~ModelExprVal() {
	// TODO Auto-generated destructor stub
}

void ModelExprVal::eval(IModelVal *dst) {
    /*
	dst->set(&m_val);
     */
}

}
} /* namespace vsc */

