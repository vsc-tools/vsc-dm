/*
 * ModelValRange.h
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelValRange.h"
#include "ModelVal.h"

namespace vsc {

class ModelValRange : public IModelValRange {
public:
	ModelValRange(const IModelVal *lower);

	ModelValRange(
			const IModelVal	*lower,
			const IModelVal	*upper);

	ModelValRange(const IModelVal	&lower);

	ModelValRange(
			const IModelVal	&lower,
			const IModelVal	&upper);

	ModelValRange(const IModelValRange *rhs);

	virtual ~ModelValRange() { }

	virtual IModelVal *lower() override { return &m_lower; }

	virtual const IModelVal *lower() const override { return &m_lower; }

	virtual IModelVal *upper() override { return &m_upper; }

	virtual const IModelVal *upper() const override { return &m_upper; }

private:
	ModelVal				m_lower;
	ModelVal				m_upper;
};

}


