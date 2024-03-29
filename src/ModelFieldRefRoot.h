/*
 * ModelFieldRefRoot.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "ModelFieldRef.h"

namespace vsc {
namespace dm {

class ModelFieldRefRoot : public ModelFieldRef {
public:
	ModelFieldRefRoot(
			IDataType			*type,
			const std::string	&name);

	virtual ~ModelFieldRefRoot();

	virtual const std::string &name() const override {
		return m_name;
	}

	virtual IDataType *getDataType() const override {
		return m_type;
	}

	virtual void setDataType(IDataType *t) override;

	virtual void accept(IVisitor *v) override { v->visitModelFieldRefRoot(this); }

private:
	IDataType					*m_type;
	std::string					m_name;
};

}
} /* namespace vsc */

