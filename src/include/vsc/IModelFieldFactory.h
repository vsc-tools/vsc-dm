/*
 * IModelFieldFactory.h
 *
 *  Created on: Jun 28, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IModelField.h"

namespace vsc {

class IModelFieldFactory;
using IModelFieldFactoryUP=std::unique_ptr<IModelFieldFactory>;

/**
 * Used to create vector elements when required
 * by the solver
 */
class IModelFieldFactory {
public:

	virtual ~IModelFieldFactory() { }

	virtual IModelField *create(const std::string &name) = 0;

};

}
