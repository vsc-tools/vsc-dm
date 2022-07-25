#pragma once
#include <vector>
#include <map>
#include "vsc/impl/TaskCopyModelConstraint.h"

namespace vsc {

class TaskUnrollModelIterativeConstraints : 
    public virtual TaskCopyModelConstraint {
public:

    TaskUnrollModelIterativeConstraints(IContext *ctxt) : TaskCopyModelConstraint(ctxt) { }

    virtual ~TaskUnrollModelIterativeConstraints() { }

    void unroll(IModelConstraintScope *c) {
        m_src_scope_s.push_back(c);
        m_src_scope_s.pop_back();
    }

protected:
    std::vector<IModelConstraintScope *>      m_src_scope_s;
    std::vector<uint32_t>                     m_src_index_s;
    std::map<IModelField *, IModelVal *>      m_iter_val_m;
};


}