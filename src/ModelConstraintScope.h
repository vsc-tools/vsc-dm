/*
 * ModelConstraintScope.h
 *
 *  Created on: Oct 22, 2021
 *      Author: mballance
 * 
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
 * 
 */

#pragma once
#include <vector>
#include "vsc/dm/IModelConstraintScope.h"
#include "ModelConstraint.h"

namespace vsc {
namespace dm {

class ModelConstraintScope;
using ModelConstraintScopeUP=std::unique_ptr<ModelConstraintScope>;
class ModelConstraintScope : 
	public virtual IModelConstraintScope, 
	public virtual ModelConstraint {
public:
	ModelConstraintScope();

	virtual ~ModelConstraintScope();

	virtual const std::vector<IModelConstraint *> &getConstraints() const override {
		return m_constraints;
	}

	virtual void addConstraint(
        IModelConstraint    *c,
        bool                owned) override;

	virtual void accept(IVisitor *v) override { v->visitModelConstraintScope(this); }

private:
	std::vector<IModelConstraint *>		m_constraints;
    std::vector<IAcceptUP>              m_owned;
};

}
} /* namespace vsc */

