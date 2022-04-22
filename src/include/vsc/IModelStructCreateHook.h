/*
 * IModelStructCreateHook.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>

namespace vsc {

class IModelField;

class IModelStructCreateHook;
using IModelStructCreateHookUP=std::unique_ptr<IModelStructCreateHook>;
class IModelStructCreateHook {
public:

	virtual ~IModelStructCreateHook() { }

	virtual void create(IModelField *field) = 0;

};

}

