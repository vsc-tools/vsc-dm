/*
 * VscTestBase.cpp
 *
 *  Created on: Oct 6, 2021
 *      Author: mballance
 */

#include "VscTestBase.h"
#include "ctor.h"

namespace vsc {

using namespace facade;

VscTestBase::VscTestBase() {
	// TODO Auto-generated constructor stub

}

VscTestBase::~VscTestBase() {
	// TODO Auto-generated destructor stub
}

void VscTestBase::SetUp() {
	ctor::reset();
}

void VscTestBase::TearDown() {
	ASSERT_EQ(ctor::inst()->scope_depth(), 0);
	ASSERT_EQ(ctor::inst()->expr_depth(), 0);
	ctor::reset();
}

} /* namespace vsc */
