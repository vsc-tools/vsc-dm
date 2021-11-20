/*
 * ModelValOp.h
 *
 *  Created on: Nov 19, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelVal.h"

namespace vsc {

class ModelValOp {
public:
	ModelValOp();
	virtual ~ModelValOp();

	static void eq(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void ne(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void sge(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);
};

} /* namespace vsc */

