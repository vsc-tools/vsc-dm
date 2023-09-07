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
#include "vsc/dm/impl/VisitorBase.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <stdarg.h>

namespace vsc {
namespace dm {

class PrettyPrinter : public virtual VisitorBase {
public:

    PrettyPrinter() : VisitorBase(), m_prefix_s(), m_ind(""), m_str_tmp("") { 
        fprintf(stdout, "PrettyPrinter::PrettyPrinter()\n");
        fprintf(stdout, "prefix.size=%d\n", m_prefix_s.size());

    }

    virtual ~PrettyPrinter() { }

    const char *print(IAccept *it) {
//        std::stringstream sstr;
//        m_out = &sstr;

        m_out = 0;
        m_str_tmp.clear();
        it->accept(m_this);

//        m_str_tmp = sstr.str();
        m_prefix_s.clear();
        return m_str_tmp.c_str();
    }

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) override {
        println("constraint %s {", c->name().c_str());
        inc_indent();
        for (std::vector<IModelConstraintUP>::const_iterator
            it=c->getConstraints().begin();
            it!=c->getConstraints().end(); it++) {
            (*it)->accept(m_this);
        }
        dec_indent();
        println("}");
    }

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override {
        // If we're prefixed by a single statement like 'soft',
        // don't indent
        if (prefix() != Prefix::SingleStmt) {
            indent();
        }
        print("EXPR");
        c->expr()->accept(m_this);
        println();
    }

	virtual void visitModelConstraintForeach(IModelConstraintForeach *c) override {
        indent();
        print("foreach (");
        c->getTarget()->accept(m_this);
        print(") {");
        println();
        push_prefix(Prefix::Block);
        inc_indent();
        visitModelConstraintScope(c);
        dec_indent();
        pop_prefix();
        println("}");

    }

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) override {
        print("if (");
        c->getCond()->accept(m_this);
    }

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override {
        indent();
        print("(");
        c->getCond()->accept(m_this);
        print(") -> ");
        c->getBody()->accept(m_this);
    }

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override {
        for (std::vector<IModelConstraintUP>::const_iterator
            it=c->getConstraints().begin();
            it!=c->getConstraints().end(); it++) {
            (*it)->accept(m_this);
        }
    }

	virtual void visitModelConstraintSelect(IModelConstraintSelect *c) override {
        println("TODO: ModelConstraintSelect");
    }

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override {
        indent();
        print("soft ");
        c->constraint()->accept(m_this);
    }

	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) override {
        println("TODO: ModelConstraintUnique");
    }

	virtual void visitModelExprBin(IModelExprBin *e) override {
        const char *BinOp_s[] = {
        	"==", "!=", ">", ">=", "<", "<=" 
            "+", "-", "/", "*", "%", "&", "|",
            "&&", "||", "<<", ">>", "^", "~"
        };

        print("(");
        e->lhs()->accept(m_this);
        print(") %s (", BinOp_s[static_cast<int32_t>(e->op())]);
        e->rhs()->accept(m_this);
        print(")");
    }

	virtual void visitModelExprCond(IModelExprCond *e) override {
        print("(");
        e->getCond()->accept(m_this);
        print(")?(");
        e->getTrue()->accept(m_this);
        print("):(");
        e->getFalse()->accept(m_this);
        print(")");
    }

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override {
        print("%s", e->field()->name().c_str());
    }

	virtual void visitModelExprIn(IModelExprIn *e) override {
        print("(");
        e->lhs()->accept(m_this);
        print(") in ");
        e->rangelist()->accept(m_this);
    }

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override {
        IModelField *field = 0;

        for (std::vector<ModelExprIndexedFieldRefElem>::const_iterator
            it=e->getPath().begin();
            it!=e->getPath().end(); it++) {
            if (it!=e->getPath().begin()) {
                print(".");
            }
            switch (it->kind) {
                case ModelExprIndexedFieldRefKind::Field:
                    field = it->field;
                    break;
                case ModelExprIndexedFieldRefKind::FieldIndex:
                    field = (field)?field->getField(it->offset):0;
                    break;
                case ModelExprIndexedFieldRefKind::VecIndex:
                    break;
            }
            print("%s(%p)", (field)?field->name().c_str():"null", field);
        }
    }

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override {

    }

	virtual void visitModelExprRange(IModelExprRange *e) override {

    }

	virtual void visitModelExprRangelist(IModelExprRangelist *e) override {

    }

	virtual void visitModelExprUnary(IModelExprUnary *e) override {
        const char *UnaryOp_s[] = {
            "!"
        };

    }

	virtual void visitModelExprVal(IModelExprVal *e) override {
#ifdef UNDEFINED
        print("%lld", e->val()->val_i());
#endif
    }

	virtual void visitModelExprVecSubscript(IModelExprVecSubscript *e) override {

    }

protected:
    enum class Prefix {
        None,
        SingleStmt,
        Block
    };

protected:

    void indent() {
    	if (m_ind.size()) {
            if (m_out) {
    	        m_out->write(m_ind.c_str(), m_ind.size());
            } else {
                m_str_tmp += m_ind;
            }
	    }
    }

    void print(const char *fmt, ...) {
        va_list ap;
        char tmp[1024];
        va_start(ap, fmt);

        int len = vsnprintf(tmp, sizeof(tmp), fmt, ap);
        if (m_out) {
            m_out->write(tmp, len);
        } else {
            m_str_tmp.append(tmp, len);
        }

        va_end(ap);
    }

    void println() {
        if (m_out) {
            m_out->write("\n", 1);
        } else {
            m_str_tmp += "\n";
        }
    }

    void println(const char *fmt, ...) {
        va_list ap;
        char tmp[4096];
        va_start(ap, fmt);

        int len = vsnprintf(tmp, sizeof(tmp), fmt, ap);
        if (m_out) {
            m_out->write(m_ind.c_str(), m_ind.size());
            m_out->write(tmp, len);
            m_out->write("\n", 1);
        } else {
            m_str_tmp += m_ind;
            m_str_tmp += tmp;
            m_str_tmp += "\n";
        }

        va_end(ap);
    }

    void dec_indent(int amt=1) {
        if (amt*4 < m_ind.size()) {
            m_ind = m_ind.substr(amt*4);
        } else {
            m_ind = "";
        }
    }

    void inc_indent(int amt=1) {
        for (uint32_t i=0; i<4*amt; i++) {
            m_ind.push_back(' ');
        }
    }

    void push_prefix(Prefix pref) {
        m_prefix_s.push_back(pref);
    }

    void pop_prefix() {
        m_prefix_s.pop_back();
    }

    Prefix prefix() {
        if (m_prefix_s.size() == 0) {
            return Prefix::None;
        } else {
            return m_prefix_s.back();
        }
    }


protected:
    std::string             m_ind;
    std::ostream            *m_out;
    std::vector<Prefix>     m_prefix_s;
    std::string             m_str_tmp;

};

}
}
