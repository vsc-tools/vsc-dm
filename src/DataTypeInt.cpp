/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * DataTypeInt.cpp
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#include "DataTypeInt.h"

namespace vsc {

DataTypeInt::DataTypeInt(
		bool				is_signed,
		int32_t				width) : m_is_signed(is_signed), m_width(width) {
	// TODO Auto-generated constructor stub

}

DataTypeInt::~DataTypeInt() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
