/*
 * VscTestBase.cpp
 *
 *  Created on: Oct 6, 2021
 *      Author: mballance
 */

#include "VscTestBase.h"
#include "ctor.h"
#include "glog/logging.h"

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

void VscTestBase::send(::google::LogSeverity severity, const char* full_filename,
	                    const char* base_filename, int line,
	                    const struct ::tm* tm_time,
	                    const char* message, size_t message_len) {
	fprintf(stdout, "::send: %s\n", message);
}

} /* namespace vsc */
