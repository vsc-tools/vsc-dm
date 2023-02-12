/*
 * IModelStructCreateHook.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/impl/UP.h"

namespace vsc {
namespace dm {

class IModelField;

class IModelStructCreateHook;
using IModelStructCreateHookUP=UP<IModelStructCreateHook>;
class IModelStructCreateHook {
public:

	virtual ~IModelStructCreateHook() { }

	virtual void create(IModelField *field) = 0;

};

}
}

