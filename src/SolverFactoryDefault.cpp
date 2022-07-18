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
 *
 * SolverFactoryDefault.cpp
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#include "SolverFactoryDefault.h"
#include "SolverBitwuzla.h"
#include "SolverBoolector.h"

namespace vsc {

SolverFactoryDefault::SolverFactoryDefault() {
	// TODO Auto-generated constructor stub

}

SolverFactoryDefault::~SolverFactoryDefault() {
	// TODO Auto-generated destructor stub
}

ISolver *SolverFactoryDefault::createSolverInst(SolveSet *sset) {
//	return new SolverBitwuzla();
	return new SolverBoolector();
}

ISolverFactory *SolverFactoryDefault::inst() {
	return &m_inst;
}

SolverFactoryDefault SolverFactoryDefault::m_inst;

} /* namespace vsc */
