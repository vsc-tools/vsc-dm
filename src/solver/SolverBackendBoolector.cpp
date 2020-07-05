/*
 * SolverBackendBoolector.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#include "SolverBackendBoolector.h"
#include "boolector/boolector.h"

namespace vsc {

class BoolectorSolverInst : public ISolverData {
public:

	BoolectorSolverInst() {
		m_btor = boolector_new();
	}

	virtual ~BoolectorSolverInst() {
		boolector_delete(m_btor);
	}

private:
	Btor				*m_btor;
};

SolverBackendBoolector::SolverBackendBoolector() {
	// TODO Auto-generated constructor stub

}

SolverBackendBoolector::~SolverBackendBoolector() {
	// TODO Auto-generated destructor stub
}

ISolverData *SolverBackendBoolector::createSolverInst() {
	return new BoolectorSolverInst();
}

// Creates solver data for a field
ISolverData *SolverBackendBoolector::createFieldInst(
		ISolverData 		*solver,
		Field 				*f) {
	return 0;
}

// Creates solver data for a constraint
ISolverData* SolverBackendBoolector::createConstraintInst(
		ISolverData			*solver,
		ConstraintBlock		*constraint) {
	return 0;
}

void SolverBackendBoolector::addAssume(
		ISolverData			*solver,
		ISolverData			*constraint) {

}

void SolverBackendBoolector::addAssert(
		ISolverData			*solver,
		ISolverData			*constraint) {

}

bool SolverBackendBoolector::failed(
		ISolverData			*solver,
		ISolverData			*constraint) {
	return true;
}

bool SolverBackendBoolector::isSAT(ISolverData *solver) {
	return false;
}

} /* namespace vsc */
