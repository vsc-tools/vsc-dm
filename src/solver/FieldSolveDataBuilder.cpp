/*
 * FieldSolveDataBuilder.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "FieldSolveDataBuilder.h"

namespace vsc {

FieldSolveDataBuilder::FieldSolveDataBuilder(ISolverInst *inst) : m_inst(inst) {
	// TODO Auto-generated constructor stub

}

FieldSolveDataBuilder::~FieldSolveDataBuilder() {
	// TODO Auto-generated destructor stub
}

void FieldSolveDataBuilder::visitFieldScalar(FieldScalar *f) {
//	f->solver_data(m_inst->createFieldInst(f));
}

} /* namespace vsc */
