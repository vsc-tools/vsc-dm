/*
 * CommitFieldValueVisitor.h
 *
 *  Created on: Oct 24, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "ISolver.h"
#include "VisitorBase.h"

namespace vsc {

class CommitFieldValueVisitor : public VisitorBase {
public:
	CommitFieldValueVisitor(ISolver *solver);

	virtual ~CommitFieldValueVisitor();

	void commit(ModelField *f);

	virtual void visitDataTypeInt(DataTypeInt *t) override;

	virtual void visitModelField(ModelField *f) override;

private:
	ISolver									*m_solver;
	std::vector<ModelField *>				m_field_s;

};

} /* namespace vsc */

