/*
 * BinsType.h
 *
 *  Created on: Nov 16, 2021
 *      Author: mballance
 */

#pragma once

namespace vsc {

enum class BinsType {
	Bins,
	IgnoreBins,
	IllegalBins
};

const char *toString(BinsType t);

} /* namespace vsc */

