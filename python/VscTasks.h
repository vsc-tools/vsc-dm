/*
 * tasks.h
 *
 *  Created on: Jun 29, 2022
 *      Author: mballance
 */
#pragma once
#include <string>
#include "vsc/IContext.h"
#include "vsc/IDataType.h"

namespace vsc {

IModelField *Task_BuildModelField(
		IContext				*ctxt,
		IDataType				*type,
		const std::string		&name);

void Task_RollbackConstraintSubst(
		IModelConstraint		*scope);

}
