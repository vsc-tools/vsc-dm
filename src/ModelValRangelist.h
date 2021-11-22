/*
 * ModelValRangelist.h
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelValRange.h"

namespace vsc {

class ModelValRangelist : public std::vector<ModelValRange> {
public:
	ModelValRangelist(bool is_signed=true);

	virtual ~ModelValRangelist();

	bool is_signed() const { return m_is_signed; }

	void is_signed(bool s) { m_is_signed = s; }

private:
	bool					m_is_signed;

};

} /* namespace vsc */

