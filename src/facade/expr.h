/*
 * expr.h
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <stdint.h>
#include "ModelExpr.h"

namespace vsc {

class ModelExpr;
using ModelExprUP=std::unique_ptr<ModelExpr>;
namespace facade {

class attr_scalar;

class expr {
public:
	expr(const attr_scalar &);

	expr(ModelExpr *core);

	virtual ~expr();

private:
//	ModelExprUP					m_core;
	ModelExpr					*m_core;
};

} /* namespace facade */
} /* namespace vsc */

