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
#include "ModelConstraint.h"
#include "ModelVal.h"
#include "TypeField.h"

namespace vsc {

class ModelField;
using ModelFieldUP=std::unique_ptr<ModelField>;
class ModelField {
public:
	ModelField();

	virtual ~ModelField();

	virtual const std::string &name() const = 0;

	virtual DataType *datatype() const = 0;

	ModelField *parent() const { return m_parent; }

	void parent(ModelField *p) { m_parent = p; }

	const std::vector<ModelFieldUP> &fields() const { return m_fields; }

	const std::vector<ModelConstraintUP> &constraints() const {
		return m_constraints;
	}

protected:
	ModelField						*m_parent;

	// Typically only really used for scalar fields
	ModelVal						m_val;

	std::vector<ModelFieldUP>		m_fields;
	std::vector<ModelConstraintUP>	m_constraints;

};

} /* namespace vsc */

