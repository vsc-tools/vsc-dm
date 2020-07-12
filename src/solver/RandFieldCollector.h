/*
 * RandFieldCollector.h
 *
 *  Created on: Jul 10, 2020
 *      Author: ballance
 */

#pragma once
#include <vector>
#include "VisitorBase.h"
#include "FieldScalar.h"


namespace vsc {

class RandFieldCollector : public VisitorBase {
public:
	RandFieldCollector();

	virtual ~RandFieldCollector();

	void collect(
			const std::vector<FieldSP> 		&fields,
			std::vector<FieldScalar *>		&rand_fields);

	virtual void visitFieldScalar(FieldScalar *f) override;


private:
	std::vector<FieldScalar *>			*m_rand_fields;

};

} /* namespace vsc */

