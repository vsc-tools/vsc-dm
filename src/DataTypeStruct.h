/*
 * DataTypeStruct.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IDataTypeStruct.h"
#include "DataType.h"

namespace vsc {

class TypeField;
using TypeFieldUP=std::unique_ptr<TypeField>;

class TypeConstraint;
using TypeConstraintUP=std::unique_ptr<TypeConstraint>;

class DataTypeStruct;
using DataTypeStructUP=std::unique_ptr<DataTypeStruct>;
class DataTypeStruct : public IDataTypeStruct {
public:
	DataTypeStruct(const std::string &name);

	virtual ~DataTypeStruct();

	virtual const std::string &name() const override {
		return m_name;
	}

	virtual void addField(ITypeField *f) override;

	virtual const std::vector<ITypeFieldUP> &getFields() const override;

	virtual void addConstraint(ITypeConstraint *c) override;

	virtual const std::vector<ITypeConstraintUP> &getConstraints() const override;

	virtual void accept(IVisitor *v) override { v->visitDataTypeStruct(this); }

private:
	std::string							m_name;
	std::vector<ITypeFieldUP>			m_fields;
	std::vector<ITypeConstraintUP>		m_constraints;

};

} /* namespace vsc */

