/*
 * covergroup.cpp
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#include "covergroup.h"

namespace vsc {
namespace facade {

covergroup::covergroup(const scope &s) : rand_obj(this) {
	// TODO Auto-generated constructor stub

}

covergroup::~covergroup() {
	// TODO Auto-generated destructor stub
}

void covergroup::sample() {
	;
}

covergroup::coverpoint::coverpoint(
		const scope					&name,
		const expr_base				&expr,
		const std::function<void()>	&body) {

}

covergroup::coverpoint::coverpoint(
		const scope											&name,
		const expr_base										&expr,
		const std::function<void(covergroup::options_t &)>	&body) {

}

covergroup::cross::cross(
		const scope					&name,
		const std::vector<cp_ref>	&terms) {

}

covergroup::bins::bins(
		const scope			&s,
		const std::vector<expr_range>	&ranges) {

}

covergroup::ignore_bins::ignore_bins(
		const scope			&s,
		const std::vector<expr_range>	&ranges) {

}

covergroup::illegal_bins::illegal_bins(
		const scope			&s,
		const std::vector<expr_range>	&ranges) {

}


} /* namespace facade */
} /* namespace vsc */
