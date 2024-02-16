/*
 * TypeExprFieldRef.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeExprFieldRef.h"

namespace vsc {
namespace dm {

class TypeExprFieldRef : public ITypeExprFieldRef {
public:

	TypeExprFieldRef(
        ITypeExprFieldRef::RootRefKind  kind,
        int32_t                         offset,
        int32_t                         index);

	virtual ~TypeExprFieldRef();

    virtual RootRefKind getRootRefKind() const override {
        return m_root_ref_kind;
    }

    virtual int32_t getRootRefOffset() const override {
        return m_root_ref_offset;
    }

    virtual int32_t getSubFieldIndex() const override {
        return m_subfield_index;
    }

	virtual void accept(IVisitor *v) override { v->visitTypeExprFieldRef(this); }

private:
    RootRefKind                                 m_root_ref_kind;
    int32_t                                     m_root_ref_offset;
    int32_t                                     m_subfield_index;
};

}
} /* namespace vsc */

