/*
 * Factory.cpp
 *
 * Copyright 2022 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author:
 */
#include "Context.h"
#include "Factory.h"


namespace vsc {
namespace dm {


Factory::Factory() : m_dbg_mgr(0) {

}

Factory::~Factory() {

}

void Factory::init(dmgr::IDebugMgr *dm) {
    m_dbg_mgr = dm;
}

dmgr::IDebugMgr *Factory::getDebugMgr() const {
    return m_dbg_mgr;
}

IContext *Factory::mkContext() {
    return new Context(m_dbg_mgr);

}

IFactory *Factory::inst() {
    if (!m_inst) {
        m_inst = FactoryUP(new Factory());
    }
    return m_inst.get();
}

}
}

