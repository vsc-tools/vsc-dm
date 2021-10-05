/*
 * rand_attr.h
 *
 *  Created on: Aug 10, 2021
 *      Author: mballance
 */

#pragma once
#include "attr_cls.h"
#include "attr_scalar.h"

namespace vsc {
namespace facade {

template <typename T> class rand_attr : public T {
public:
	rand_attr(const scope &name) : T(name) { }


};

template <> class rand_attr<int> : public attr_scalar {
public:

	rand_attr(
			const scope		&name,
			int32_t			width=32) : attr_scalar(true, width) {
		fprintf(stdout, "rand_attr<int>\n");
	}
};

template <> class rand_attr<unsigned int> : public attr_scalar {
public:

	rand_attr(
			const scope		&name,
			int32_t			width=32) : attr_scalar(true, width) {
		fprintf(stdout, "rand_attr<unsigned int>\n");
	}
};

}
}
