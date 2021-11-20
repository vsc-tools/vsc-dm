/*
 * ModelVal.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <stdint.h>
#include <vector>

namespace vsc {

class DataType;

class ModelVal;
using ModelValUP=std::unique_ptr<ModelVal>;
class ModelVal {
public:

	ModelVal();

	ModelVal(int32_t bits, uint64_t val=0);

	ModelVal(const ModelVal &rhs);

	void operator = (const ModelVal &rhs);

	virtual ~ModelVal();

	uint32_t bits() const { return m_bits; }

	void bits(uint32_t b);

	void to_bits(char *bits) const;

	void from_bits(const char *bits, int32_t width=-1);

	inline int64_t val_i() const {
		if (m_bits <= 64) {
			int64_t ret = m_val.v;
			if (m_bits < 64) { // sign-extend
				ret <<= (64-m_bits);
				ret >>= (64-m_bits);
			}
			return ret;
		} else {
			return m_val.vp[0];
		}
	}

	inline uint64_t val_u() const { return (m_bits<=64)?m_val.v:m_val.vp[0]; }

	void val_u(uint64_t v, int32_t width=-1);

	ModelVal slice(
			int32_t		upper,
			int32_t		lower);

private:
	union val_t {
		uint64_t		v;
		uint64_t		*vp;
	} m_val;
	uint32_t			m_bits;
};

} /* namespace vsc */

