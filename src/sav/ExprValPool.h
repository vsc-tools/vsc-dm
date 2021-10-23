/*
 * ExprValPool.h
 *
 *  Created on: Aug 21, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>

#include "sav/ExprVal.h"
#include "sav/ExprValEnum.h"

namespace vsc {

class ExprValPool {
public:
	ExprValPool();

	virtual ~ExprValPool();

	ExprVal *alloc(uint32_t sz);

	void free(ExprVal *val);

private:
	std::vector<ExprVal *>		m_pool;
};

} /* namespace vsc */

