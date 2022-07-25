
#include "TaskFixModelField.h"

namespace vsc {

TaskFixModelField::TaskFixModelField(uint32_t flags) : m_flags(flags) {

}

TaskFixModelField::~TaskFixModelField() {

}

void TaskFixModelField::fix(const std::vector<IModelField *> &fields) {
    for (std::vector<IModelField *>::const_iterator
            it=fields.begin();
            it!=fields.end(); it++) {
        (*it)->accept(m_this);
    }
}

void TaskFixModelField::visitModelField(IModelField *f) {
    bool fix = (m_flags == Flags_All);

    fix |= (f->isFlagSet(ModelFieldFlag::VecSize) && (m_flags & Flags_VecSize));

    if (fix) {
        f->setFlag(ModelFieldFlag::Resolved);
    }
}

}
