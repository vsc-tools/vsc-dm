/*
 * ITypeFieldRef.h
 *
 *  Created on: May 9, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>
#include "vsc/dm/ITypeField.h"

namespace vsc {
namespace dm {

class ITypeFieldRef : public virtual ITypeField {
public:

	virtual ~ITypeFieldRef() { }

};

}
}

