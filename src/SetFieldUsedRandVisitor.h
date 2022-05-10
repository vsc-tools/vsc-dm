/*
 * SetFieldUsedRandVisitor.h
 *
 *  Created on: Oct 24, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class SetFieldUsedRandVisitor : public VisitorBase {
public:
	SetFieldUsedRandVisitor();

	virtual ~SetFieldUsedRandVisitor();

	void set(IModelField *f);

	virtual void visitModelField(IModelField *f) override;

private:
	std::vector<bool>		m_decl_rand_s;

};

} /* namespace vsc */

