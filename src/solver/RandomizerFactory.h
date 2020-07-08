/*
 * RandomizerFactory.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "solver/IRandomizer.h"

namespace vsc {

class RandomizerFactory {
public:
	RandomizerFactory();

	virtual ~RandomizerFactory();

	static IRandomizer *inst();

private:
	static IRandomizerUP			m_inst;

};

} /* namespace vsc */

