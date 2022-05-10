/*
 * PrettyPrinter.h
 *
 *  Created on: Oct 5, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class PrettyPrinter : public VisitorBase {
public:
	PrettyPrinter();
	virtual ~PrettyPrinter();
};

} /* namespace vsc */

