/*
 * ModelExpr.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IModelExpr.h"
#include "ModelVal.h"

namespace vsc {

class ModelExpr;
using ModelExprUP = std::unique_ptr<ModelExpr>;

class ModelExpr : public IModelExpr {
public:
	ModelExpr();

	virtual ~ModelExpr();

	/**
	 * Evaluate the expression and return a result
	 */
//	virtual void eval(IModelVal *dst) override { }

protected:
	/**
	 * Performs width conversion on a value
	 */
	typedef void (*op_width_f)(
			int32_t			width,
			ModelVal 		&dst,
			const ModelVal	&src);

	/**
	 * Performs a two-operand operation on values
	 */
	typedef void (*op2_f)(
			ModelVal 		&dst,
			const ModelVal	&s1,
			const ModelVal	&s2);

private:

};

} /* namespace vsc */

