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
 * Debug.cpp
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#include "Debug.h"
#include "DebugMgr.h"

namespace vsc {
namespace dm {

Debug::Debug(const std::string &name) : m_en(false), m_name(name) {
	m_mgr = DebugMgr::inst();
	m_mgr->addDebug(this);
}

Debug::~Debug() {
	// TODO Auto-generated destructor stub
}

void Debug::enter(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	m_mgr->enter(this, fmt, ap);
	va_end(ap);
}

void Debug::leave(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	m_mgr->leave(this, fmt, ap);
	va_end(ap);
}

void Debug::debug(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	m_mgr->debug(this, fmt, ap);
	va_end(ap);
}

}
} /* namespace vsc */
