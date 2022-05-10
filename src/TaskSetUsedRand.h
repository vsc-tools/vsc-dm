/*
 * VisitorTaskSetUsedRand.h
 *
 *  Created on: Mar 23, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/ITask.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class TaskSetUsedRand : public VisitorBase {
public:
	TaskSetUsedRand();

	virtual ~TaskSetUsedRand();

	virtual void apply(IAccept *item, bool set_root, int32_t max_depth=-1);

	virtual void visitModelField(IModelField *f) override;

private:
	bool is_used_rand();

private:
	bool							m_set_root;
	int32_t							m_max_depth;
	std::vector<bool>				m_used_rand;


};

} /* namespace vsc */

