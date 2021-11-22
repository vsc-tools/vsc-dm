/*
 * ModelValRange.h
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelVal.h"

namespace vsc {

class ModelValRange {
public:
	ModelValRange(
			const ModelVal	&lower) :
				m_lower(lower), m_upper(lower) { }

	ModelValRange(
			const ModelVal	&lower,
			const ModelVal	&upper) :
				m_lower(lower), m_upper(upper) { }

	virtual ~ModelValRange() { }

	ModelVal &lower() { return m_lower; }

	const ModelVal &lower() const { return m_lower; }

	ModelVal &upper() { return m_upper; }

	const ModelVal &upper() const { return m_upper; }

private:
	ModelVal				m_lower;
	ModelVal				m_upper;
};

}


