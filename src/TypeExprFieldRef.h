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
        int32_t                         offset
    );

	virtual ~TypeExprFieldRef();

    virtual RootRefKind getRootRefKind() const override {
        return m_root_ref_kind;
    }

    virtual int32_t getRootRefOffset() const override {
        return m_root_ref_offset;
    }

	virtual void addPathElem(int32_t idx) override;

	virtual uint32_t size() const override { return m_path.size(); }

	virtual int32_t at(int32_t idx) const override {
		return m_path.at(idx);
	}

	virtual const std::vector<int32_t> &getPath() const override {
		return m_path;
	}

	virtual void accept(IVisitor *v) override { v->visitTypeExprFieldRef(this); }

private:
    RootRefKind                                 m_root_ref_kind;
    int32_t                                     m_root_ref_offset;
	std::vector<int32_t>	      				m_path;
};

}
} /* namespace vsc */

