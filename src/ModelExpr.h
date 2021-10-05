/*
 * ModelExpr.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "IAccept.h"

namespace vsc {

class ModelExpr;
using ModelExprUP = std::unique_ptr<ModelExpr>;

class ModelExpr : public IAccept {
public:
	ModelExpr();

	virtual ~ModelExpr();
};

} /* namespace vsc */

