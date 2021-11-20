/*
 * ModelExpr.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "IAccept.h"
#include "ModelVal.h"

namespace vsc {

class ModelExpr;
using ModelExprUP = std::unique_ptr<ModelExpr>;

class ModelExpr : public IAccept {
public:
	ModelExpr();

	virtual ~ModelExpr();

	virtual int32_t width() const = 0;

	/**
	 * Evaluate the expression and return a result
	 */
	virtual void eval(ModelVal &dst) { }

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

