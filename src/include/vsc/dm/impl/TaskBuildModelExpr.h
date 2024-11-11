/*
 * TaskBuildModelExpr.h
 *
 *  Created on: Apr 28, 2022
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
#include "vsc/dm/IContext.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/ITypeExprFieldRef.h"
#include "vsc/dm/impl/TaskIsModelFieldRef.h"
#include "vsc/dm/impl/VisitorBase.h"


namespace vsc {
namespace dm {

class TaskBuildModelExpr : public VisitorBase {
public:
	TaskBuildModelExpr(
			IModelBuildContext	*ctxt,
			IVisitor			*this_p=0):
				VisitorBase(this_p), m_ctxt(ctxt), m_expr(0) { }

	virtual ~TaskBuildModelExpr() { }

	virtual IModelExpr *build(ITypeExpr *e) { return expr(e); }

	template <class T> T *buildT(ITypeExpr *e) {
		return dynamic_cast<T *>(build(e));
	}

	virtual void visitTypeExprBin(ITypeExprBin *e) override {
		IModelExpr *lhs = expr(e->lhs());
		IModelExpr *rhs = expr(e->rhs());
		m_expr = m_ctxt->ctxt()->mkModelExprBin(lhs, e->op(), rhs);
	}

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) override {
 		bool references_ref_fields = false;
		IModelField *f = 0;
        (void)f;
        (void)references_ref_fields;

        switch (e->getRootRefKind()) {
            case ITypeExprFieldRef::RootRefKind::TopDownScope: {
                f = m_ctxt->getTopDownScope();
            } break;
            case ITypeExprFieldRef::RootRefKind::BottomUpScope: {
                f = m_ctxt->getBottomUpScope(e->getRootRefOffset());
            } break;
            case ITypeExprFieldRef::RootRefKind::RootExpr: {
                fprintf(stdout, "TODO: handle RootExpr reference\n");
            } break;
        }

#ifdef UNDEFINED
		for (; it!=e->getPath().end(); it++) {
			f = f->getField(*it);

			if (TaskIsModelFieldRef().check(f)) {
				references_ref_fields = true;
				break;
			}
		}

		if (references_ref_fields) {
			// Rebuild as a relative-reference expression
            it = e->getPath().begin();
			IModelExprIndexedFieldRef *ref = m_ctxt->ctxt()->mkModelExprIndexedFieldRef();
            switch (e->getRootRefKind()) {
                case ITypeExprFieldRef::RootRefKind::TopDownScope: {
					ref->addField(m_ctxt->getTopDownScope());
                } break;
                case ITypeExprFieldRef::RootRefKind::BottomUpScope: {
					ref->addField(m_ctxt->getBottomUpScope(*it));
                    it++;
                } break;
                case ITypeExprFieldRef::RootRefKind::RootExpr: {
                    fprintf(stdout, "TODO: handle RootExpr reference\n");
                } break;
            }
//			int32_t width = -1;
			for (; it!=e->getPath().end(); it++) {
				ref->addFieldOffsetRef(*it);
			}

			m_expr = ref;
		} else {
			// Good to go:
			m_expr = m_ctxt->ctxt()->mkModelExprFieldRef(f);
		}
#endif // UNDEFINED


// 		IModelExprIndexedFieldRef *ref = m_ctxt->ctxt()->mkModelExprIndexedFieldRef();

// 		// On the first pass, confirm whether we have any indexed
// 		IModelField *f = 0;
// 		for (auto it=e->getPath().rbegin(); it!=e->getPath().rend(); it++) {
// 			switch (it->kind) {
// 			case TypeExprFieldRefElemKind::Root: {
// 				f = m_ctxt->getTopDownScope();
// 				ref->addField(f);
// 			} break;
// 			case TypeExprFieldRefElemKind::ActiveScope: {
// 				f = m_ctxt->getBottomUpScope(it->idx);
// 				ref->addField(f);
// 			} break;
// 			case TypeExprFieldRefElemKind::IdxOffset: {
// 				ref->addFieldOffsetRef(it->idx);
// //				f = f->getField(it->idx);
// 			} break;

// 			default:
// 				fprintf(stdout, "Unhandled case\n");
// 			}
// 		}

// //		m_expr = m_ctxt->ctxt()->mkModelExprFieldRef(f);
	}

	virtual void visitTypeExprRangelist(ITypeExprRangelist *e) override {
		IModelExprRangelist *rl = m_ctxt->ctxt()->mkModelExprRangelist();

		// TODO: Should really have a 'const' variant where everything
		// just flattens out

		for (std::vector<ITypeExprRangeUP>::const_iterator
				it=e->getRanges().begin();
				it!=e->getRanges().end(); it++) {
			if ((*it)->isSingle()) {
				rl->addRange(m_ctxt->ctxt()->mkModelExprRange(
						true,
						expr((*it)->lower()),
						0));
			} else {
				if ((*it)->lower() && (*it)->upper()) {
					IModelExpr *lower = expr((*it)->lower());
					IModelExpr *upper = expr((*it)->upper());

					rl->addRange(m_ctxt->ctxt()->mkModelExprRange(
						false,
						lower,
						upper));
				} else if ((*it)->lower()) {
					rl->addRange(m_ctxt->ctxt()->mkModelExprRange(
						false,
						expr((*it)->lower()),
						0));
				} else {
					rl->addRange(m_ctxt->ctxt()->mkModelExprRange(
						false,
						0,
						expr((*it)->upper())));
				}
			}
		}

		m_expr = rl;
	}

	virtual void visitTypeExprVal(ITypeExprVal *e) override {
        /* TODO:
		m_expr = m_ctxt->ctxt()->mkModelExprVal(e->val());
         */
	}

	virtual void visitTypeField(ITypeField *f) override {
		;
	}

protected:
	virtual IModelExpr *expr(ITypeExpr *expr) {
		m_expr = 0;
		expr->accept(m_this);
		return m_expr;
	}

protected:
	IModelBuildContext			*m_ctxt;
	IModelExpr					*m_expr;

};

}
}
