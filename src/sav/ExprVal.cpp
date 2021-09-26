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
 * ExprVal.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "sav/ExprVal.h"

namespace vsc {

ExprVal::ExprVal(
		ExprValKind 	type,
		int32_t			width,
		bool			is_signed) : m_type(type),
				m_width(width), m_is_signed(is_signed) {
	m_value = 0;
	if (m_width <= 64) {
		m_value_ext = 0;
	} else {
		m_value_ext = new uint64_t[width/64+1];
		for (uint32_t i=0; i<width/64+1; i++) {
			m_value_ext[i] = 0;
		}
	}

	m_next = 0;
}

ExprVal::~ExprVal() {
	if (m_value_ext) {
		delete [] m_value_ext;
	}
}

void ExprVal::resize(int32_t width) {
	if (width > 64) {
		if (m_value_ext) {
			// See if we're exceeding the previous size
			if (((width/64)+1) > (m_width/64)+1) {
				// Need to reallocate
				delete [] m_value_ext;
				m_value_ext = new uint64_t[width/64+1];
				for (uint32_t i=0; i<width/64+1; i++) {
					m_value_ext[i] = 0;
				}
			}
		} else {
			m_value_ext = new uint64_t[width/64+1];
			for (uint32_t i=0; i<width/64+1; i++) {
				m_value_ext[i] = 0;
			}
		}
	}
	m_width = width;
}

uint64_t ExprVal::val_u() const {
	;
}

int64_t ExprVal::val_s() const {
	;
}


} /* namespace vsc */
