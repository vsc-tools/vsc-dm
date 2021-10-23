/*
 * ExprValPool.cpp
 *
 *  Created on: Aug 21, 2021
 *      Author: mballance
 */

#include "sav/ExprValPool.h"

namespace vsc {

ExprValPool::ExprValPool() {
	// TODO Auto-generated constructor stub

}

ExprValPool::~ExprValPool() {
	// TODO Auto-generated destructor stub
}

ExprVal *ExprValPool::alloc(uint32_t sz) {
	while (m_pool.size() < sz) {
		m_pool.push_back(0);
	}

	ExprVal *ret = 0;
	if (m_pool.at(sz)) {
		ExprVal *ret = m_pool.at(sz);
		m_pool.at(sz) = m_pool.at(sz)->m_next;
	} else {
		// Create a new one
	}
}

} /* namespace vsc */
