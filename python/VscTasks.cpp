/*
 * Tasks.cpp
 *
 *  Created on: Jun 29, 2022
 *      Author: mballance
 */
#include "VscTasks.h"
#include "vsc/impl/ModelBuildContext.h"
#include "vsc/impl/TaskBuildModelField.h"
#include "vsc/impl/TaskRollbackConstraintSubst.h"

namespace vsc {

IModelField *Task_BuildModelField(
		IContext				*ctxt,
		IDataType				*type,
		const std::string		&name) {
	ModelBuildContext build_ctxt(ctxt);
	return TaskBuildModelField(&build_ctxt).build(type, name);
}

void Task_RollbackConstraintSubst(
		IModelConstraint		*scope) {
	TaskRollbackConstraintSubst().rollback(scope);
}


}

