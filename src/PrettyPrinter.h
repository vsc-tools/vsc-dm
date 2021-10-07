/*
 * PrettyPrinter.h
 *
 *  Created on: Oct 5, 2021
 *      Author: mballance
 */

#pragma once
#include "VisitorBase.h"

namespace vsc {

class PrettyPrinter : public VisitorBase {
public:
	PrettyPrinter();
	virtual ~PrettyPrinter();
};

} /* namespace vsc */

