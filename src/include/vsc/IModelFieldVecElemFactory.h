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

class IModelFieldVecElemFactory;
using IModelFieldVecElemFactoryUP=std::unique_ptr<IModelFieldVecElemFactory>;

/**
 * Used to create vector elements when required
 * by the solver
 */
class IModelFieldVecElemFactory {
public:

	virtual ~IModelFieldVecElemFactory() { }

	virtual IModelField *create(
			const std::string 	&name,
			IModelField			*vec) = 0;

};

}
