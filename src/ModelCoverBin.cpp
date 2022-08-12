/*
 * ModelCoverBin.cpp
 *
 *  Created on: Nov 17, 2021
 *      Author: mballance
 */

#include "ModelCoverBin.h"

namespace vsc {

ModelCoverBin::ModelCoverBin(
	const std::string		&name,
	ModelCoverBinType		type,
	bool					is_signed) :
		m_name(name), m_type(type), m_is_signed(is_signed),
		m_bin_idx_base(-1), m_n_bins(-1) {

}

ModelCoverBin::~ModelCoverBin() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
