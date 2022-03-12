/*
 * IRandomizer.h
 *
 *  Created on: Feb 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelField.h"
#include "vsc/IModelConstraint.h"

namespace vsc {

class IRandomizer {
public:

	virtual ~IRandomizer() { }

	virtual bool randomize(
			const std::vector<IModelField *>		&fields,
			const std::vector<IModelConstraint *>	&constraints,
			bool									diagnost_failures) = 0;

};

}
