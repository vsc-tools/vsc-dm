/*
 * TestModelSmoke.cpp
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include "TestModelSmoke.h"
#include "Context.h"
#include "ModelFieldRoot.h"

namespace vsc {
namespace dm {

TestModelSmoke::TestModelSmoke() {
	// TODO Auto-generated constructor stub

}

TestModelSmoke::~TestModelSmoke() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestModelSmoke, smoke) {
	IDataTypeInt *vsc_uint32_t = m_ctxt->findDataTypeInt(false, 32);
	if (!vsc_uint32_t) {
		vsc_uint32_t = m_ctxt->mkDataTypeInt(false, 32);
		m_ctxt->addDataTypeInt(vsc_uint32_t);
	}
	IModelFieldRoot *a = new ModelFieldRoot(vsc_uint32_t, "a");
#ifdef UNDEFINED
	SolverBoolector *solver = new SolverBoolector();

	solver->initField(a);
	solver->isSAT();
	solver->setFieldValue(a);
#endif
}

}
} /* namespace vsc */

