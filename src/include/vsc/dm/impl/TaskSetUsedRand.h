/*
 * VisitorTaskSetUsedRand.h
 *
 *  Created on: Mar 23, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/dm/ITask.h"
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

class TaskSetUsedRand : public VisitorBase {
public:
	TaskSetUsedRand() {}

	virtual ~TaskSetUsedRand() {}

	virtual void apply(IAccept *item, bool set_root, int32_t max_depth=-1) {
		m_used_rand.clear();
		m_set_root = set_root;
		m_max_depth = max_depth;
		item->accept(this);
	}

	virtual void visitModelField(IModelField *f) override {
		bool used_rand = is_used_rand(f->flags());

		if (used_rand) {
			f->setFlag(ModelFieldFlag::UsedRand);
		}

		// Once we go through a non-rand section, there's no point in continuing
		if (used_rand && f->getFields().size() > 0) {
			m_used_rand.push_back(used_rand);
			for (auto fi=f->getFields().begin(); fi!=f->getFields().end(); fi++) {
				(*fi)->accept(this);
			}
			m_used_rand.pop_back();
		}
	}

protected:

	bool is_used_rand(ModelFieldFlag flags) {
		if (m_used_rand.size() > 0) {
			return ((m_max_depth == -1 || m_max_depth < m_used_rand.size()) &&
					m_used_rand.at(m_used_rand.size()-1) && 
					(flags & ModelFieldFlag::DeclRand) != ModelFieldFlag::NoFlags);
		} else {
			return m_set_root;
		}
	}

protected:
	bool							m_set_root;
	int32_t							m_max_depth;
	std::vector<bool>				m_used_rand;


};

}
} /* namespace vsc */

