/*
 * ModelValRangelist.h
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelValRangelist.h"
#include "ModelValRange.h"

namespace vsc {
namespace dm {

class ModelValRangelist : public IModelValRangelist {
public:
	ModelValRangelist(bool is_signed=true);

	virtual ~ModelValRangelist();

	virtual bool getIsSigned() const override { return m_is_signed; }

	virtual void setIsSigned(bool s) override { m_is_signed = s; }

	virtual void push_back(const IModelValRange *v) override;

	virtual void push_back(const IModelValRange &v) override;

	virtual uint32_t size() const override { return m_values.size(); }

	virtual void clear() override;

	virtual const IModelValRange *at(uint32_t i) const;

	virtual IModelValRange *at(uint32_t i);

private:
	bool							m_is_signed;
	std::vector<ModelValRange>		m_values;
	std::vector<IModelValRange *>	m_values_p;

};

}
} /* namespace vsc */

