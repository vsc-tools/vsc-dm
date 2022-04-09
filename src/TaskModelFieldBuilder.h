/*
 * TaskModelFieldBuilder.h
 *
 *  Created on: Apr 9, 2022
 *      Author: mballance
 */

#pragma once
#include "VisitorBase.h"

namespace vsc {

class TaskModelFieldBuilder : public VisitorBase {
public:
	TaskModelFieldBuilder();
	virtual ~TaskModelFieldBuilder();
};

} /* namespace vsc */

