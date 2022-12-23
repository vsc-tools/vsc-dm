
#pragma once
#include "vsc/dm/impl/VisitorBase.h"


namespace vsc {
namespace dm {

class TaskIsDataTypeSigned : public VisitorBase {
public:

    TaskIsDataTypeSigned() : m_result(false) {}

    bool check(IDataType *type) {
        m_result = false;
        type->accept(m_this);
        return m_result;
    }

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override { 
        m_result = t->isSigned();
    }

	virtual void visitDataTypeInt(IDataTypeInt *t) override { 
        m_result = t->isSigned();
    }

private:
    bool                        m_result;

};

}
}
