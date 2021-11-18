/*
 * ModelCoverpointBinsBase.h
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#pragma once
#include "IModelCoverpointBins.h"

namespace vsc {

class ModelCoverpointBinsBase : public IModelCoverpointBins {
public:
	ModelCoverpointBinsBase();

	virtual ~ModelCoverpointBinsBase();

	virtual BinsType bin_type() override { return m_type; }

	virtual void bin_type(BinsType t) override { m_type = t; }

	virtual int32_t n_bins() override { return m_n_bins; }

protected:

	ModelCoverpoint		*m_cp;
	int32_t				m_bin_idx_base;
	BinsType			m_type;
	int32_t				m_n_bins;
};

} /* namespace vsc */

