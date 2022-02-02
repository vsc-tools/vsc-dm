/*
 * IModelExpr.h
 *
 *  Created on: Jan 27, 2022
 *      Author: mballance
 */

namespace vsc {

class IModelExpr {
public:
	virtual ~IModelExpr() { }

	virtual int32_t width() const = 0;

	/**
	 * Evaluate the expression and return a result
	 */
	virtual void eval(ModelVal &dst) = 0;
};

}
