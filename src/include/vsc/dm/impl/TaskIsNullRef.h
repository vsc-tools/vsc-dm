
#pragma once
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

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
}
