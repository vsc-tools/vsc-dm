/*
 * IModelFieldVecRoot.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelFieldVec.h"

namespace vsc {
namespace dm {

class IModelFieldVecRoot : public virtual IModelFieldVec {
public:

	virtual ~IModelFieldVecRoot() { }

	virtual void setName(const std::string &name) = 0;

};

}
}
