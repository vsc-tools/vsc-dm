/*
 * SolverBitwuzla.h
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include <unordered_map>
#include "vsc/ISolver.h"
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
	virtual void initField(IModelField *f) override;

	// Creates solver data for a constraint
	virtual void initConstraint(IModelConstraint *c) override;

	virtual void addAssume(IModelConstraint *c) override;

	virtual void addAssert(IModelConstraint *c) override;

	virtual bool isSAT() override;

	virtual void setFieldValue(IModelField *f) override;

	const BitwuzlaSort *get_sort(int32_t width);

	void addFieldData(IModelField *f, const BitwuzlaTerm *n);

	const BitwuzlaTerm *findFieldData(IModelField *f);

private:
	Bitwuzla				*m_bitwuzla;
	std::unordered_map<IModelField *,const BitwuzlaTerm *>		m_field_node_m;
	std::unordered_map<IModelConstraint *,const BitwuzlaTerm *>	m_constraint_node_m;
	std::unordered_map<uint32_t, const BitwuzlaSort *>			m_sort_m;
	bool														m_issat_valid;
	bool														m_issat;
};

} /* namespace vsc */

