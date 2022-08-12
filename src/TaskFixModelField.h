
#pragma once
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class TaskFixModelField : public virtual VisitorBase {
public:
    static const uint32_t       Flags_Scalar  = (1 << 0);
    static const uint32_t       Flags_VecSize = (1 << 1);
    static const uint32_t       Flags_All     = (Flags_Scalar | Flags_VecSize);


public:

    TaskFixModelField(uint32_t flags = Flags_All);

    virtual ~TaskFixModelField();

    void fix(const std::vector<IModelField *> &fields);

	virtual void visitModelField(IModelField *f) override;

private:
    uint32_t                            m_flags;

};

}