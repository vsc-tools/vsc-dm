
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
 * FieldScalar.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#include "sav/FieldScalar.h"

namespace vsc {

FieldScalar::FieldScalar(
		const std::string		&name,
		int32_t					width,
		bool					is_signed,
		bool					is_rand) : Field(name, is_rand),
				m_val(new ExprValInt(0, width, is_signed)) {
	// TODO Auto-generated constructor stub

}

FieldScalar::~FieldScalar() {
	// TODO Auto-generated destructor stub
}

FieldScalarSP FieldScalar::mk(
			const std::string 	&name,
			int32_t				width,
			bool				is_signed,
			bool				is_rand) {
	return FieldScalarSP(new FieldScalar(name, width, is_signed, is_rand));
}

} /* namespace vsc */
