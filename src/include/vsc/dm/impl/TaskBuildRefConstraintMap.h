/**
 * TaskBuildRefConstraintMap.h
 *
 * Copyright 2022 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author: 
 */
#pragma once
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "vsc/dm/IContext.h"
#include "vsc/dm/IModelFieldRef.h"
#include "vsc/dm/impl/VisitorBase.h"
#include "dmgr/impl/DebugMacros.h"

namespace vsc {
namespace dm {

using RefSet=std::vector<int32_t>;
using ConstraintSet=std::vector<IModelConstraint *>;
using RefConstraintSet=std::pair<RefSet,ConstraintSet>;
struct RefConstraintMap {
    std::vector<RefConstraintSet>           ref_constraint_l;
};

/**
 * Builds a map between references through reference fields and 
 * constraints
 * 
 */
class TaskBuildRefConstraintMap : public VisitorBase {
public:
    TaskBuildRefConstraintMap(IContext *ctxt) {
        m_dbg = 0;
        DEBUG_INIT("TaskBuildRefConstraintMap", ctxt->getDebugMgr());
        m_atomic_scope_level = 0;
    }

    virtual ~TaskBuildRefConstraintMap() {}

    const std::vector<RefConstraintSet> &build(
        const std::vector<IModelField *>     &targets,
        const std::vector<IModelConstraint *>   &constraints) {
        DEBUG_ENTER("build targets=%d constraints=%d", targets.size(), constraints.size());
        m_target_l = &targets;
        m_atomic_scope_level = 0;

        for (std::vector<IModelConstraint *>::const_iterator
            it=constraints.begin();
            it!=constraints.end(); it++) {
            (*it)->accept(m_this);
        }

        DEBUG_LEAVE("build ref_constraint_l=%d", m_result.size());
        return m_result;
    }

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override {
        enter_scope(c);
		c->expr()->accept(m_this);
        exit_scope(c);
	}

	virtual void visitModelConstraintForeach(IModelConstraintForeach *c) override {
        enter_scope(c);
		c->getTarget()->accept(m_this);
		visitModelConstraintScope(c);
        exit_scope(c);
	}

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) override { 
        enter_scope(c);
		c->getCond()->accept(m_this);
		c->getTrue()->accept(m_this);
		if (c->getFalse()) {
			c->getFalse()->accept(m_this);
		}
        exit_scope(c);
	}

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override { 
        enter_scope(c);
		c->getCond()->accept(m_this);
		c->getBody()->accept(m_this);
        exit_scope(c);
	}

	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) override { 
        enter_scope(c);
		for (std::vector<IModelExprUP>::const_iterator
			it=c->getExprs().begin();
			it!=c->getExprs().end(); it++) {
			(*it)->accept(m_this);
		}
        exit_scope(c);
	}

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override { 
        IModelField *field = 0;

        int32_t i=0;
        for (i=0; i<e->getPath().size(); i++) {
            switch (e->getPath().at(i).kind) {
                case ModelExprIndexedFieldRefKind::Field:
                    field = e->getPath().at(i).field;
                    break;
                case ModelExprIndexedFieldRefKind::FieldIndex:
                    field = field->getField(e->getPath().at(i).offset);
                    break;
                case ModelExprIndexedFieldRefKind::VecIndex:
                    fprintf(stdout, "Error: VecIndex not supported\n");
                    field = 0;
                    break;
            }

            int32_t target_idx = findTargetIdx(field);

            if (target_idx != -1) {
                // Add the field to the referenced set
                if (m_target_ref_s.insert(field).second) {
                    m_target_ref_l.push_back(target_idx);
                }
                break;
            }
        }
    }

private:
    int32_t findTargetIdx(IModelField *f) {
        int32_t idx = -1;
        for (uint32_t i=0; i<m_target_l->size(); i++) {
            if (m_target_l->at(i) == f) {
                idx = i;
                break;
            }
        }

        return idx;
    }

    void enter_scope(IModelConstraint *c) {
        if (m_atomic_scope_level == 0) {
            // Clean up 
            m_target_ref_l.clear();
            m_target_ref_s.clear();
        }

        m_atomic_scope_level++;
    }

    void exit_scope(IModelConstraint *c) {
        m_atomic_scope_level--;

        if (m_atomic_scope_level == 0) {
            if (m_target_ref_l.size()) {
                // Found some references in this constraint
                std::vector<RefConstraintSet>::iterator it;

                // First, order the reference list
                std::sort(m_target_ref_l.begin(), m_target_ref_l.end());


                for (it=m_result.begin();
                    it!=m_result.end(); it++) {
                    if (m_target_ref_l.size() == it->first.size()) {
                        uint32_t i;
                        for (i=0; i<m_target_ref_l.size(); i++) {
                            if (m_target_ref_l.at(i) != it->first.at(i)) {
                                break;
                            }
                        }

                        if (i == m_target_ref_l.size()) {
                            break;
                        }
                    }
                }

                if (it == m_result.end()) {
                    it = m_result.insert(
                        m_result.end(),
                        RefConstraintSet({m_target_ref_l, {}}));
                }

                it->second.push_back(c);
            }
        }
    }

private:
    dmgr::IDebug                                     *m_dbg;
    const std::vector<IModelField *>                 *m_target_l;
    std::unordered_set<IModelField *>                m_target_ref_s;
    std::vector<int32_t>                             m_target_ref_l;
    uint32_t                                         m_atomic_scope_level;
    std::vector<RefConstraintSet>                    m_result;

};

}
}

#undef INCLUDED_DEBUG_MACROS_H

