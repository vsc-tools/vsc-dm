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

using ModelFieldFlags=uint32_t;
static const uint32_t ModelFieldFlag_DeclRand = (1 << 0);
static const uint32_t ModelFieldFlag_UsedRand = (1 << 1);
static const uint32_t ModelFieldFlag_Resoved  = (1 << 2);

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

	ModelFieldFlags flags() const { return m_flags; }

	void clear_flag(ModelFieldFlags flags) {
		m_flags &= (~flags);
	}

	void set_flag(ModelFieldFlags flags) {
		m_flags |= flags;
	}

	bool is_flag_set(ModelFieldFlags flags) const {
		return ((m_flags & flags) == flags);
	}

protected:
	ModelField						*m_parent;

	// Typically only really used for scalar fields
	ModelVal						m_val;

	std::vector<ModelFieldUP>		m_fields;
	std::vector<ModelConstraintUP>	m_constraints;
	ModelFieldFlags					m_flags;

};

} /* namespace vsc */

