/*
 * TestRandomDist.cpp
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#include "TestRandomDist.h"

using namespace vsc::facade;

namespace vsc {

TestRandomDist::TestRandomDist() {
	// TODO Auto-generated constructor stub

}

TestRandomDist::~TestRandomDist() {
	// TODO Auto-generated destructor stub
}

#ifdef UNDEFINED
TEST_F(TestRandomDist, if_then_dist) {

	class BranchInstr : public rand_obj {
	public:
		BranchInstr(const scope &s) : rand_obj(this) { }

		rand_attr<ui_t<1>>		type {"type"};
		rand_attr<ui_t<22>>		disp {"disp"};

		constraint short_offset_cnstr { "short_offset_cnstr", [&] {
			if_then(type == ui_t<8>(0), [&] {
				disp <= 4096;
			}).else_then([&] {
				disp <= 4096;
			});
		}};
	};

	uint32_t *hist = new uint32_t[4097];
	memset(hist, 0, sizeof(uint32_t)*4097);

	BranchInstr instr("instr");

	for (uint32_t i=0; i<4096; i++) {
		instr.randomize();
		hist[instr.disp()]++;
	}

	fprintf(stdout, "hist: ");
	for (uint32_t i=0; i<4097; i++) {
		fprintf(stdout, "%d ", hist[i]);
	}
	fprintf(stdout, "\n");
}

TEST_F(TestRandomDist, multivar_rel) {

	class it_c : public rand_obj {
	public:
		it_c(const scope &s) : rand_obj(this) { }

		rand_attr<ui_t<8>>		a {"a"};
		rand_attr<ui_t<8>>		b {"b"};

		constraint ab_c {"ab_c", [this] {
			a < b;
		}};
	};

	it_c it("it");

	uint32_t *hist_a = new uint32_t[256];
	uint32_t *hist_b = new uint32_t[256];

	memset(hist_a, 0, sizeof(uint32_t)*256);
	memset(hist_b, 0, sizeof(uint32_t)*256);

	for (uint32_t i=0; i<256*20; i++) {
		it.randomize();
		ASSERT_LT(it.a(), it.b());
		hist_a[it.a()]++;
		hist_b[it.b()]++;
	}

	fprintf(stdout, "hist_a: ");
	for (uint32_t i=0; i<256; i++) {
		fprintf(stdout, "%d ", hist_a[i]);
	}
	fprintf(stdout, "\n");
	fprintf(stdout, "hist_b: ");
	for (uint32_t i=0; i<256; i++) {
		fprintf(stdout, "%d ", hist_b[i]);
	}
	fprintf(stdout, "\n");
}
#endif

} /* namespace vsc */
