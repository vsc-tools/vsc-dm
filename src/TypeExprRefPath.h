/**
 * TypeExprRefPath.h
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
#include "vsc/dm/ITypeExprRefPath.h"
#include "TypeExprRef.h"

namespace vsc {
namespace dm {



class TypeExprRefPath : 
    public virtual ITypeExprRefPath,
    public virtual TypeExprRef {
public:
    TypeExprRefPath(
        ITypeExpr                   *root,
        bool                        owned,
        const std::vector<int32_t>  &path);

    virtual ~TypeExprRefPath();

    virtual const std::vector<int32_t> &getPath() const override {
        return m_path;
    }

    virtual void accept(IVisitor *v) override {
        v->visitTypeExprRefPath(this);
    }

private:
    std::vector<int32_t>            m_path;
};

}
}


