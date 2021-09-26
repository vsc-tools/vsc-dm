
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * FieldBoundInfo.h
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#pragma once
#include <memory>
#include <vector>

#include "ExprValInt.h"
#include "sav/FieldBoundPropagator.h"

namespace vsc {

//class range_t : public std::pair<uint64_t, uint64_t> {
//public:
//	range_t(uint64_t low, uint64_t high) :
//		std::pair<uint64_t,uint64_t>(low, high) { }
//
//	int64_t low_s() const { return static_cast<int64_t>(first); }
//	uint64_t low_u() const { return first; }
//
//	void low_s(int64_t v) { first = v; }
//	void low_u(uint64_t v) { first = v; }
//
//	int64_t high_s() const { return static_cast<int64_t>(second); }
//	uint64_t high_u() const { return second; }
//
//	void high_s(int64_t v) { second = v; }
//	void high_u(uint64_t v) { second = v; }
//
//};

typedef std::pair<ExprValNumericSP,ExprValNumericSP> range_t;
typedef std::vector<range_t> domain_t;

class FieldBoundInfo {
public:
	FieldBoundInfo(bool is_signed);

	virtual ~FieldBoundInfo();

	domain_t &domain() { return m_domain; }

	const domain_t &domain() const { return m_domain; }

	bool is_constrained() const { return m_is_constrained; }

	void is_constrained(bool i) { m_is_constrained = i; }

	void add_propagator(FieldBoundPropagator *p) {
		m_propagators.push_back(FieldBoundPropagatorUP(p));
	}

	virtual void propagate();

	// Update derived calculations
	virtual void update();

private:
	bool										m_is_signed;
	domain_t									m_domain;
	std::vector<FieldBoundPropagatorUP>			m_propagators;
	bool										m_is_constrained;


};

typedef std::unique_ptr<FieldBoundInfo> FieldBoundInfoUP;

} /* namespace vsc */

