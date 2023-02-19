/*
 * IModelFieldRef.h
 *
 *  Created on: May 9, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/dm/IModelField.h"

namespace vsc {
namespace dm {

class IModelFieldRef;
using IModelFieldRefUP=UP<IModelFieldRef>;
class IModelFieldRef : public virtual IModelField {
public:

	virtual ~IModelFieldRef() { }

	virtual void setRef(IModelField *ref) = 0;

	virtual IModelField *getRef() const = 0;

};

}
}
