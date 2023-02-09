/*
 * Copyright 2019-2023 Matthew Ballance and contributors
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
 */
#pragma once
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/impl/TaskBuildModelConstraint.h"
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

template <class ConstraintBuilderT=TaskBuildModelConstraint<> > 
    class TaskBuildModelFieldConstraints : 
        public virtual VisitorBase {
public:

    TaskBuildModelFieldConstraints(IModelBuildContext *ctxt) : 
        m_ctxt(ctxt), m_constraint_builder(ctxt) { }

    void build(IModelField *model, IDataType *type) {
        m_ctxt->pushTopDownScope(model);
        type->accept(m_this);
        m_ctxt->popTopDownScope();
    }

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {
        for (std::vector<ITypeConstraintUP>::const_iterator
            it=t->getConstraints().begin();
            it!=t->getConstraints().end(); it++) {
            IModelConstraint *c = m_constraint_builder.build(it->get());
        }
    }


protected:
    IModelBuildContext                  *m_ctxt;
    ConstraintBuilderT                  m_constraint_builder;
};

}
}
