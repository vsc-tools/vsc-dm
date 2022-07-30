/*
 * ModelCoverpointBinsBase.h
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelCoverBin.h"

namespace vsc {

class ModelCoverBin : public virtual IModelCoverBin {
public:
	ModelCoverBin(
		const std::string 		&name,
		ModelCoverBinType		type,
		bool					is_signed);

	virtual ~ModelCoverBin();

	virtual const std::string &name() const override { return m_name; }

	virtual ModelCoverBinType getType() const override { return m_type; }

    virtual void setCoverpoint(IModelCoverpoint *cp) override {
		m_cp = cp;
	}

    virtual IModelCoverpoint *getCoverpoint() const override {
		return m_cp;
	}

    virtual int32_t getNumBins() const override { return m_n_bins; }

protected:
	std::string			m_name;
	ModelCoverBinType	m_type;
	bool				m_is_signed;
	IModelCoverpoint	*m_cp;
	int32_t				m_bin_idx_base;
	int32_t				m_n_bins;
};

} /* namespace vsc */

