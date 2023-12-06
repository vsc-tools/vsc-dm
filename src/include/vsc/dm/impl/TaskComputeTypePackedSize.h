/**
 * TaskComputeTypePackedSize.h
 *
 * Copyright 2023 Matthew Ballance and Contributors
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
#pragma once
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {



class TaskComputeTypePackedSize : public VisitorBase {
public:

    virtual ~TaskComputeTypePackedSize() { }

    uint32_t compute(IDataType *t) {
        m_sz = 0;
        t->accept(m_this);
        return m_sz;
    }

	virtual void visitDataTypeBool(IDataTypeBool *t) override { 
        m_sz += 1;
    }
    
	virtual void visitDataTypeEnum(IDataTypeEnum *t) override { 
        m_sz += 32; // TODO
    }

	virtual void visitDataTypeInt(IDataTypeInt *t) override { 
        m_sz += t->getWidth();
    }

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {
		for (auto it=t->getFields().begin(); it!=t->getFields().end(); it++) {
			(*it)->accept(m_this);
		}
    }

private:
    uint32_t                    m_sz;

};

} /* namespace dm */
} /* namespace vsc */


