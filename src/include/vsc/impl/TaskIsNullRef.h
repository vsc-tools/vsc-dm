
#pragma once
#include "vsc/impl/VisitorBase.h"

namespace vsc {

/**
 * @brief Checks whether a reference passes through
 *        a FieldRef with a null target
 * 
 */
class TaskIsNullRef : public virtual VisitorBase {
public:

    TaskIsNullRef() : m_is_null(false) { }

    bool check(IModelExpr *e) {
        m_is_null = false;
        e->accept(m_this);
        return m_is_null;
    }

protected:
    bool                    m_is_null;

};

}