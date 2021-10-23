/*
 * ModelField.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>
#include <vector>
#include "IAccept.h"
#include "ModelConstraint.h"
#include "ModelVal.h"
#include "TypeField.h"

namespace vsc {

class ModelField;
using ModelFieldUP=std::unique_ptr<ModelField>;
class ModelField : public IAccept {
public:
	ModelField(DataType *type);

	ModelField();

	virtual ~ModelField();

	virtual const std::string &name() const = 0;

	virtual DataType *datatype() const = 0;

	ModelField *parent() const { return m_parent; }

	void parent(ModelField *p) { m_parent = p; }

	const std::vector<ModelConstraintUP> &constraints() const {
		return m_constraints;
	}

	void add_constraint(ModelConstraint *c);

	const std::vector<ModelFieldUP> &fields() const { return m_fields; }

	void add_field(ModelField *field);

	const ModelVal &val() const { return m_val; }

	ModelVal &val() { return m_val; }

protected:
	ModelField						*m_parent;

	// Typically only really used for scalar fields
	ModelVal						m_val;

	std::vector<ModelFieldUP>		m_fields;
	std::vector<ModelConstraintUP>	m_constraints;

};

} /* namespace vsc */

