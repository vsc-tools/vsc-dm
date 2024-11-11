/*
 * TestModelVal.cpp
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#include "TestModelVal.h"
#include "ModelVal.h"

namespace vsc {
namespace dm {

TestModelVal::TestModelVal() {
	// TODO Auto-generated constructor stub

}

TestModelVal::~TestModelVal() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestModelVal, push_val_bit) {
	FAIL() << "ModelVal updates";
#ifdef UNDEFINED
	uint32_t val_lit = 0x242526;
	ModelVal val;

	for (uint32_t i=0; i<24; i++) {
		val.push_bit(val_lit & 1);
		val_lit >>= 1;
	}

	ASSERT_EQ(val.bits(), 24);
	char *val_s = (char *)alloca(val.bits()+1);
	val.to_bits(val_s);
	ASSERT_EQ(std::string("001001000010010100100110"), val_s);
#endif
}

TEST_F(TestModelVal, push_val_word) {
	FAIL() << "ModelVal updates";
#ifdef UNDEFINED
	uint32_t val_lit = 0x242526;
	ModelVal val;

	val.push_word(val_lit);

	ASSERT_EQ(val.bits(), 32);
	char *val_s = (char *)alloca(val.bits()+1);
	val.to_bits(val_s);
	ASSERT_EQ(std::string("00000000001001000010010100100110"), val_s);
#endif
}

}
} /* namespace vsc */

