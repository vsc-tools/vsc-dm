/*
 * ModelFieldRef.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelFieldRef.h"
#include "ModelField.h"

namespace vsc {

class ModelFieldRef : public virtual IModelFieldRef {
public:
	ModelFieldRef();

	virtual ~ModelFieldRef();

	virtual IModelField *getParent() const override { return m_parent; }

	virtual void setParent(IModelField *p) override { m_parent = p; }

	virtual const std::vector<IModelConstraintUP> &constraints() const override {
		return m_ref->constraints();
	}

	virtual void addConstraint(IModelConstraint *c) override {
		m_ref->addConstraint(c);
	}

	virtual const std::vector<IModelFieldUP> &fields() const override {
		return m_ref->fields();
	}

	virtual void addField(IModelField *field) override {
		m_ref->addField(field);
	}

	virtual IModelField *getField(int32_t idx) override {
		return m_ref->getField(idx);;
	}

	virtual const IModelVal *val() const override {
		return m_ref->val();
	}

	virtual IModelVal *val() override {
		return m_ref->val();
	}

	virtual ModelFieldFlag flags() const override { return m_flags; }

	virtual void clearFlag(ModelFieldFlag flags) override {
		m_flags = (m_flags & (~flags));
	}

	virtual void setFlag(ModelFieldFlag flags) override {
		m_flags = (m_flags | flags);
	}

	virtual void setFlags(ModelFieldFlag flags) override {
		m_flags = flags;
	}

	virtual bool isFlagSet(ModelFieldFlag flags) const override {
		return ((m_flags & flags) == flags);
	}

	virtual void setFieldData(IModelFieldData *data) override {
		m_data = IModelFieldDataUP(data);
	}

	virtual IModelFieldData *getFieldData() override {
		return m_data.get();
	}

	virtual void setRef(IModelField *ref) override {
		m_ref = ref;
	}

	virtual IModelField *getRef() const override {
		return m_ref;
	}

protected:
	IModelField						*m_parent;
	IModelFieldDataUP				m_data;
	ModelFieldFlag					m_flags;

private:
	IModelField						*m_ref;

};

} /* namespace vsc */

