/*
 * RandState.h
 *
 *  Created on: Oct 31, 2021
 *      Author: mballance
 */

#pragma once
#include <random>
#include <stdint.h>
#include "vsc/IRandState.h"
#include "ModelVal.h"

namespace vsc {

class RandState;
using RandStateUP=std::unique_ptr<RandState>;
class RandState : public IRandState {
public:
	RandState(const std::string &seed);

	RandState(const std::mt19937_64 &state);

	virtual ~RandState();

	virtual const std::string &seed() const override {
		return m_seed;
	}

	virtual int32_t randint32(
			int32_t		min,
			int32_t		max) override;

	virtual uint64_t rand_ui64() override;

	virtual int64_t rand_i64() override;

	/**
	 * Fills the value with a random bit pattern
	 */
	virtual void randbits(IModelVal *val) override;
	
	virtual void setState(IRandState *other) override;

	virtual IRandState *clone() const override;

	virtual IRandState *next() override;

protected:
	uint64_t next_ui64();

private:
	std::string			m_seed;
	std::mt19937_64 	m_state;

};

} /* namespace vsc */

