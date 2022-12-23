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
#include "vsc/dm/IModelVal.h"

namespace vsc {
namespace dm {

class DataType;

class ModelVal;
using ModelValUP=std::unique_ptr<ModelVal>;
class ModelVal : public IModelVal {
public:

	ModelVal();

	ModelVal(int32_t bits, uint64_t val=0);

	ModelVal(const ModelVal &rhs);

	ModelVal(const IModelVal *rhs);

	void operator = (const ModelVal &rhs);

	virtual ~ModelVal();

	virtual void set(const IModelVal *v) override;

	virtual uint32_t bits() const override {
		return m_bits;
	}

	virtual void bits(uint32_t b) override;

	virtual void setBits(uint32_t b) override;

	virtual void to_bits(char *bits) const override;

	virtual void from_bits(const char *bits, int32_t width=-1) override;

	virtual void val_u(uint64_t v, int32_t width=-1) override;

	virtual void set_val_u(uint64_t v, int32_t width=-1) override;

	virtual void set_val_i(int64_t v, int32_t width=-1) override;

	inline uint64_t val_u() const { return (bits()<=64)?val().v:val().vp[0]; }

	virtual const val_t &val() const override { return m_val; }

	virtual val_t &val() override { return m_val; }

	virtual IModelVal *clone(IContext *ctxt=0) const override;

	ModelVal slice(
			int32_t		upper,
			int32_t		lower);

private:
	val_t				m_val;
	uint32_t			m_bits;
};

}
} /* namespace vsc */

namespace std {
template <>
struct hash<vsc::dm::ModelVal>
{
  std::size_t operator()(const vsc::dm::ModelVal & k) const
  {
    using std::size_t;
    using std::hash;
    using std::string;

    // Compute individual hash values for first,
    // second and third and combine them using XOR
    // and bit shifting:

    return (k.bits() ^ k.val_u());
  }
};

}

