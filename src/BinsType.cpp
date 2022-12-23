/*
 * BinsType.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: mballance
 */

#include "BinsType.h"

namespace vsc {
namespace dm {

const char *toString(BinsType t) {
	switch (t) {
	case BinsType::Bins: return "Bins";
	case BinsType::IgnoreBins: return "IgnoreBins";
	case BinsType::IllegalBins: return "IllegalBins";
	default: return "BinsType::Unknown";
	}
}

}
} /* namespace vsc */
