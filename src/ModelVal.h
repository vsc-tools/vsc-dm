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

#ifdef UNDEFINED
	class iterator {
	public:
		friend class ModelVal;

		iterator();

		uint32_t get32();

		void set32(uint32_t val);

		uint64_t get64();

		void set64(uint64_t val);

	private:
		iterator(ModelVal *v, int32_t idx);

	private:
		ModelVal			*m_val;
		int32_t				m_idx;

	};

	class const_iterator {
	public:
		friend class ModelVal;

		const_iterator();

	private:
		const_iterator(ModelVal *v, int32_t idx);

	private:
		ModelVal			*m_val;
		int32_t				m_idx;
	};
#endif

public:
	ModelVal();

	ModelVal(int32_t bits);

	ModelVal(const ModelVal &rhs);

	void operator = (const ModelVal &rhs);

#ifdef UNDEFINED
	ModelVal(DataType *type);
#endif

	virtual ~ModelVal();

#ifdef UNDEFINED
	DataType *type() const { return m_type; }

	void type(DataType *t) { m_type = t; }
#endif

	uint32_t bits() const { return m_bits; }

	void bits(uint32_t b);

#ifdef UNDEFINED
	uint32_t at(uint32_t b) const;
#endif

	uint32_t u32() const;

	void u32(uint32_t v);

	int32_t i32() const;

	uint64_t u64() const;

	void u64(uint64_t v);

	int64_t i64() const;

	void to_bits(char *bits) const;

	void from_bits(const char *bits, int32_t width=-1);

#ifdef UNDEFINED
	void set_bit(uint32_t bit, uint32_t val);

	uint32_t get_bit(uint32_t bit);

	void set_word(uint32_t wi, uint32_t val);

	uint32_t get_word(uint32_t wi) const { return m_val[wi]; }

	void push_bit(uint32_t b);

	void push_word(uint32_t v);

	void clear();
#endif

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

	void val_u(uint64_t v, int32_t width=64);

#ifdef UNDEFINED
	uint32_t val(uint32_t idx) const { return m_val[idx]; }

	ModelVal::iterator begin();

	ModelVal::const_iterator begin() const;
#endif

	ModelVal slice(
			int32_t		upper,
			int32_t		lower);

	/*
	ModelVal::iterator end();

	ModelVal::const_iterator end() const;
	 */

private:

	union val_t {
		uint64_t		v;
		uint64_t		*vp;
	} m_val;

//	val_t				m_val;
	uint32_t			m_bits;
	/*
	DataType						*m_type;
	std::vector<uint32_t>			m_val;
	bool							m_is_signed;
	 */
};

} /* namespace vsc */

