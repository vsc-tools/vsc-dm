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
 * DataType.cpp
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#include "DataType.h"
#include "ValIteratorDefault.h"
#include "ValMutIteratorDefault.h"

namespace vsc {
namespace dm {

DataType::DataType(IContext *ctxt) : 
    m_ctxt(ctxt), m_bytesz(-1) {
	// TODO Auto-generated constructor stub

}

DataType::~DataType() {
	// TODO Auto-generated destructor stub
}

IValIterator *DataType::mkValIterator(const ValRef &src) {
    return new ValIteratorDefault(src);
}

IValMutIterator *DataType::mkValMutIterator(const ValRef &src) {
    return new ValMutIteratorDefault(src);
}

}
} /* namespace vsc */
