/*
 * CoverBinSpec.h
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>

namespace vsc {

class CoverBinSpec;
using CoverBinSpecUP=std::unique_ptr<CoverBinSpec>;

/**
 * Specifies the content of a coverage bin
 */
class CoverBinSpec {
public:
	CoverBinSpec();

	virtual ~CoverBinSpec();

};

} /* namespace vsc */

