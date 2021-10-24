/*
 * SolverBitwuzla.h
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include <unordered_map>
#include "ISolver.h"
#include "ModelConstraint.h"
#include "ModelField.h"

typedef struct Bitwuzla Bitwuzla;
typedef struct BitwuzlaTerm BitwuzlaTerm;
typedef struct BitwuzlaSort BitwuzlaSort;

namespace vsc {

class SolverBitwuzla : public ISolver {
public:
	SolverBitwuzla();

	virtual ~SolverBitwuzla();

	Bitwuzla *bitwuzla() const { return m_bitwuzla; }

	// Creates solver data for a field (and possibly sub-fields)
	virtual void initField(ModelField *f) override;

	// Creates solver data for a constraint
	virtual void initConstraint(ModelConstraint *c) override;

	virtual void addAssume(ModelConstraint *c) override;

	virtual void addAssert(ModelConstraint *c) override;

	virtual bool isSAT() override;

	virtual void setFieldValue(ModelField *f) override;

	BitwuzlaSort *get_sort(int32_t width);

	void addFieldData(ModelField *f, BitwuzlaTerm *n);

	BitwuzlaTerm *findFieldData(ModelField *f);

private:
	Bitwuzla				*m_bitwuzla;
	std::unordered_map<ModelField *,BitwuzlaTerm *>			m_field_node_m;
	std::unordered_map<ModelConstraint *,BitwuzlaTerm *>	m_constraint_node_m;
	std::unordered_map<uint32_t, BitwuzlaSort *>			m_sort_m;
	bool													m_issat_valid;
	bool													m_issat;
};

} /* namespace vsc */

