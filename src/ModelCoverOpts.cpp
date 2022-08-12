/*
 * ModelCoverOpts.cpp
 *
 *  Created on: Nov 25, 2021
 *      Author: mballance
 */

#include "ModelCoverOpts.h"

namespace vsc {

ModelCoverOpts::ModelCoverOpts() :
	m_weight(1), m_goal(100),
	m_at_least(1), m_auto_bin_max(64) {

}

ModelCoverOpts::~ModelCoverOpts() {
	// TODO Auto-generated destructor stub
}

void ModelCoverOpts::init(const IModelCoverOpts *opts) {
	m_at_least = opts->getAtLeast();
	m_auto_bin_max = opts->getAutoBinMax();
}

} /* namespace vsc */
