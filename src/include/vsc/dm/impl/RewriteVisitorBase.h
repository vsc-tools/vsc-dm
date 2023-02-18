/**
 * RewriteVisitorBase.h
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
#pragma once
#include <vector>
#include "vsc/dm/IRewriteVisitor.h"
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {



class RewriteVisitorBase : 
    public virtual IRewriteVisitor,
    public virtual VisitorBase {
public:
    using Res=std::pair<IAccept *, bool>;
    template <class T> struct ResT : public std::pair<T *, bool> {
    public:
        ResT(const Res &i) : 
            std::pair<T *, bool>(dynamic_cast<T *>(i.first), i.second) { }
    };

public:
    RewriteVisitorBase() { }

    virtual ~RewriteVisitorBase() { }

    virtual void rewrite(IRewriteContext *ctxt) override {
        std::vector<IAccept *> new_roots;
        m_ctxt = ctxt;
        m_initContextDepth = ctxt->contextDepth();

        uint32_t i;
        for (i=0; i<ctxt->getRoots().size(); i++) {
            IAccept *it = ctxt->getRoots().at(i).get();
            m_res = 0;
            m_owned = false;
            m_new.clear();

            it->accept(m_this);

            if (m_new.size()) {
                new_roots.insert(
                    new_roots.end(),
                    m_new.begin(),
                    m_new.end());
                m_new.clear();
            }

            if (m_res != it) {
                // Change to a root elem.
                if (m_initContextDepth == ctxt->contextDepth()) {
                    // Ensure we've pushed a new context
                    ctxt->pushContext();
                }

                ctxt->setRoot(i, m_res, m_owned);
            }
        }

        if (new_roots.size()) {
            if (m_initContextDepth == ctxt->contextDepth()) {
                // Ensure we've pushed a new context
                ctxt->pushContext();
            }

            for (std::vector<IAccept *>::const_iterator
                it=new_roots.begin();
                it!=new_roots.end(); it++) {
                ctxt->addRoot(*it, true);
            }
        }
    }

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {
        std::vector<ITypeField *> new_fields;
        std::vector<ITypeConstraint *> new_constraints;
        IDataTypeStruct *new_t = 0;

        uint32_t i;
		for (i=0; !new_t && i<t->getFields().size(); i++) {
            ITypeField *f = t->getFields().at(i).get();

            m_res = 0;
            m_owned = false;
            m_new.clear();
            f->accept(m_this);

            if (m_res != f || m_new.size()) {
                new_t = m_ctxt->mkDataTypeStruct(t->name());

                // Add fields up to i-1
                for (uint32_t j=0; j<i; j++) {
                    new_t->addField(t->getFields().at(j).get(), false);
                }
                new_t->addField(dynamic_cast<ITypeField *>(m_res), m_owned);

                if (m_new.size()) {
                    for (std::vector<IAccept *>::const_iterator
                        it=m_new.begin();
                        it!=m_new.end(); it++) {
                        new_fields.push_back(dynamic_cast<ITypeField *>(*it));
                    }
                    m_new.clear();
                }
            }
        }

        // Finish propagating fields (if we cloned the type)
        for (; i<t->getFields().size(); i++) {
            ITypeField *f = t->getFields().at(i).get();

            m_res = 0;
            m_owned = false;
            m_new.clear();
            f->accept(m_this);

            new_t->addField(dynamic_cast<ITypeField *>(m_res), m_owned);

            if (m_new.size()) {
                for (std::vector<IAccept *>::const_iterator
                    it=m_new.begin();
                    it!=m_new.end(); it++) {
                    new_fields.push_back(dynamic_cast<ITypeField *>(*it));
                }
                m_new.clear();
            }
        }

        // This loop doesn't execute if new_t is being filled
        for (i=0; !new_t && i<t->getConstraints().size(); i++) {
            ITypeConstraint *c = t->getConstraints().at(i).get();

            ResT<ITypeConstraint> res = visit(c);

            if (res.first != c) {
                new_t = m_ctxt->mkDataTypeStruct(t->name());

                // Add all fields as non-owned entities
                for (std::vector<ITypeFieldUP>::const_iterator
                    it=t->getFields().begin();
                    it!=t->getFields().end(); it++) {
                    new_t->addField(it->get(), false);
                }
                // Add constraints up to i-1
                for (uint32_t j=0; j<i; j++) {
                    new_t->addConstraint(t->getConstraints().at(j).get(), false);
                }
                new_t->addConstraint(res.first, m_owned);

                if (m_new.size()) {
                    for (std::vector<IAccept *>::const_iterator
                        it=m_new.begin();
                        it!=m_new.end(); it++) {
                        new_constraints.push_back(dynamic_cast<ITypeConstraint *>(*it));
                    }
                    m_new.clear();
                }
            }
        }

        // Finish with constraints (if we cloned the type)
        for (; i<t->getConstraints().size(); i++) {
            ITypeConstraint *c = t->getConstraints().at(i).get();

            ResT<ITypeConstraint> res = visit(c);

            new_t->addConstraint(res.first, res.second);
            if (m_new.size()) {
                for (std::vector<IAccept *>::const_iterator
                    it=m_new.begin();
                    it!=m_new.end(); it++) {
                    new_constraints.push_back(dynamic_cast<ITypeConstraint *>(*it));
                }
                m_new.clear();
            }
        }

        if (new_t) {
            m_res = new_t;
            m_owned = true;
            for (std::vector<ITypeField *>::const_iterator
                it=new_fields.begin();
                it!=new_fields.end(); it++) {
                new_t->addField(*it, true);
            }
            for (std::vector<ITypeConstraint *>::const_iterator
                it=new_constraints.begin();
                it!=new_constraints.end(); it++) {
                new_t->addConstraint(*it, true);
            }
        } else {
            m_res = t;
            m_owned = false;
        }
	}

    virtual void visitTypeConstraintBlock(ITypeConstraintBlock *c) override {
        m_res = 0;
        m_owned = false;
        m_new.clear();
		m_this->visitTypeConstraintScope(c);
        m_new.clear();
	}
	
	virtual void visitTypeConstraintExpr(ITypeConstraintExpr *c) override {
		ResT<ITypeExpr> res = visit(c->expr());
        if (c->expr() != res.first) {
            // Clone constraint and propagate up
            ITypeConstraintExpr *ci = m_ctxt->mkTypeConstraintExpr(res.first, res.second);

            m_res = ci;
            m_owned = true;
        } else {
            m_res = c;
        }
	}

	virtual void visitTypeConstraintIfElse(ITypeConstraintIfElse *c) override {
        ResT<ITypeExpr> cond_r = visit(c->getCond());
        ResT<ITypeConstraint> true_r = visit(c->getTrue());
        ResT<ITypeConstraint> false_r = visit(c->getFalse());

        if (cond_r.first != c->getCond() || 
            true_r.first != c->getTrue() ||
            false_r.first != c->getFalse()) {
            ITypeConstraintIfElse *ci = m_ctxt->mkTypeConstraintIfElse(
                cond_r.first,
                true_r.first,
                false_r.first,
                cond_r.second,
                true_r.second,
                false_r.second);
        } else {
            m_res = c;
            m_owned = false;
        }
	}

	virtual void visitTypeConstraintImplies(ITypeConstraintImplies *c) override {
		c->getCond()->accept(m_this);
		c->getBody()->accept(m_this);
	}

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) override {
        ITypeConstraintScope *ci = 0;
        std::vector<ITypeConstraint *> new_c;
        uint32_t i;
		for (i=0; !ci && i<c->getConstraints().size(); i++) {
            ResT<ITypeConstraint> res = visit(c->getConstraints().at(i).get());

            if (c->getConstraints().at(i).get() != res.first || m_new.size()) {
                ci = m_ctxt->mkTypeConstraintScope();
                for (uint32_t j=0; j<i; j++) {
                    ci->addConstraint(c->getConstraints().at(j).get(), false);
                }
                ci->addConstraint(res.first, res.second);
            }
        }

        for (; i<c->getConstraints().size(); i++) {
            ResT<ITypeConstraint> res = visit(c->getConstraints().at(i).get());
            ci->addConstraint(res.first, res.second);
        }

        // Finally, add new constraints
        for (std::vector<ITypeConstraint *>::const_iterator
            it=new_c.begin();
            it!=new_c.end(); it++) {
            ci->addConstraint(*it, true);
        }

        if (ci) {
            m_res = ci;
            m_owned = true;
        }
	}

	virtual void visitTypeConstraintSoft(ITypeConstraintSoft *c) override {
		c->constraint()->accept(m_this);
	}

	virtual void visitTypeConstraintUnique(ITypeConstraintUnique *c) override {
		for (std::vector<ITypeExprUP>::const_iterator
			it=c->getExprs().begin();
			it!=c->getExprs().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitTypeField(ITypeField *f) override {
        m_res = f;
        m_owned = false;
	}

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override {
		m_this->visitTypeField(f);
	}

	virtual void visitTypeFieldRef(ITypeFieldRef *f) override {
		m_this->visitTypeField(f);
	}

	virtual void visitTypeFieldVec(ITypeFieldVec *f) override {
		m_this->visitTypeField(f);
	}

protected:
    Res visit(IAccept *i) {
        m_res = 0;
        m_owned = false;
        m_new.clear();
        if (i) {
            i->accept(m_this);
        }
        return {m_res, m_owned};
    }

    void add(IAccept *i, bool owned=true) {
        m_new.push_back(i);
        if (m_initContextDepth == m_ctxt->contextDepth()) {
            m_ctxt->pushContext();
        }
    }

    void retain(IAccept *i) {
        m_res = i;
        m_owned = false;
    }

    void rewrite(IAccept *i, bool owned=true) {
        m_res = i;
        m_owned = owned;
        if (m_initContextDepth == m_ctxt->contextDepth()) {
            m_ctxt->pushContext();
        }
    }

protected:
    IRewriteContext             *m_ctxt;
    int32_t                     m_initContextDepth;
    IAccept                     *m_res;
    bool                        m_owned;
    std::vector<IAccept *>      m_new;

};

}
}


