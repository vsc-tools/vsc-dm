
#pragma once
#include "vsc/impl/VisitorBase.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdarg.h>

namespace vsc {

class PrettyPrinter : public virtual VisitorBase {
public:

    const char *print(IAccept *it) {
        std::stringstream sstr;

        m_prefix_s.clear();

        m_out = &sstr;
        it->accept(m_this);

        m_str_tmp = sstr.str();
        return m_str_tmp.c_str();
    }

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) override {
        println("constraint %s {", c->name().c_str());
        inc_indent();
        for (std::vector<IModelConstraintUP>::const_iterator
            it=c->constraints().begin();
            it!=c->constraints().end(); it++) {
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
            it=c->constraints().begin();
            it!=c->constraints().end(); it++) {
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

    }

	virtual void visitModelExprVal(IModelExprVal *e) override {
        print("%lld", e->val()->val_i());
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
        m_out->write(m_ind.c_str(), m_ind.size());
    }

    void print(const char *fmt, ...) {
        va_list ap;
        char tmp[1024];
        va_start(ap, fmt);

        int len = vsnprintf(tmp, sizeof(tmp), fmt, ap);
        m_out->write(tmp, len);

        va_end(ap);
    }

    void println() {
        m_out->write("\n", 1);
    }

    void println(const char *fmt, ...) {
        va_list ap;
        char tmp[1024];
        va_start(ap, fmt);

        int len = vsnprintf(tmp, sizeof(tmp), fmt, ap);
        m_out->write(m_ind.c_str(), m_ind.size());
        m_out->write(tmp, len);
        m_out->write("\n", 1);

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

    static const char       *BinOp_s[];
    static const char       *UnaryOp_s[];

};

const char *PrettyPrinter::BinOp_s[] = {
    	"==", "!=", ">", ">=", "<", "<=" 
        "+", "-", "/", "*", "%", "&", "|",
        "&&", "||", "<<", ">>", "^", "~"
    };
const char *PrettyPrinter::UnaryOp_s[] = {
    "!"
};

}