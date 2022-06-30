/*
 * Tasks.cpp
 *
 *  Created on: Jun 29, 2022
 *      Author: mballance
 */
#include "VscTasks.h"
#include "vsc/impl/ModelBuildContext.h"
#include "vsc/impl/TaskBuildModelField.h"

namespace vsc {

IModelField *Task_BuildModelField(
		IContext				*ctxt,
		IDataType				*type,
		const std::string		&name) {
	ModelBuildContext build_ctxt(ctxt);
	return TaskBuildModelField(&build_ctxt).build(type, name);
}


}

