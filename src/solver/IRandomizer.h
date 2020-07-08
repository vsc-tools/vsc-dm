/*
 * IRandomizer.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include <memory>
#include "datamodel/Field.h"
#include "constraints/ConstraintBlock.h"

namespace vsc {

class IRandomizer {
public:

	virtual ~IRandomizer() { }

	virtual bool randomize(
			uint64_t								seed,
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintBlockSP>	&constraints) = 0;

};

typedef std::unique_ptr<IRandomizer> IRandomizerUP;

}

