/*
 * tasks.h
 *
 *  Created on: Jun 29, 2022
 *      Author: mballance
 */
#pragma once
#include <string>
#include "vsc/dm/IContext.h"
#include "vsc/dm/IDataType.h"

namespace vsc {
namespace dm {

IModelField *Task_BuildModelField(
		IContext				*ctxt,
		IDataType				*type,
		const std::string		&name);

void Task_RollbackConstraintSubst(
		IModelConstraint		*scope);

}
}
