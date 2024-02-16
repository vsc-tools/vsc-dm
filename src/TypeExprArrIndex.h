/**
 * TypeExprArrIndex.h
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
#include "vsc/dm/ITypeExprArrIndex.h"

namespace vsc {
namespace dm {



class TypeExprArrIndex : public virtual ITypeExprArrIndex {
public:
    TypeExprArrIndex(
        ITypeExpr       *root,
        bool            root_owned,
        ITypeExpr       *index,
        bool            index_owned);

    virtual ~TypeExprArrIndex();

    virtual ITypeExpr *getRootExpr() const override {
        return m_root.get();
    }

    virtual ITypeExpr *getIndexExpr() const override {
        return m_index.get();
    }

    virtual void accept(IVisitor *v) override {
        return v->visitTypeExprArrIndex(this);
    }

private:
    ITypeExprUP                 m_root;
    ITypeExprUP                 m_index;

};

}
}


