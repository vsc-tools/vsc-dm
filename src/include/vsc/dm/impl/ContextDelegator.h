/*
 * ContextDelegator.h
 *
 *  Created on: May 10, 2022
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
#include "vsc/dm/impl/UP.h"

namespace vsc {
namespace dm {

class ContextDelegator : public virtual vsc::dm::IContext {
public:

	ContextDelegator(IContext *ctxt, bool owned=true) : 
        m_ctxt(ctxt, owned) { }

	virtual ~ContextDelegator() {
	}

	virtual IModelField *buildModelField(
			IDataTypeStruct			*dt,
			const std::string		&name) override {
		return m_ctxt->buildModelField(dt, name);
	}

	virtual dmgr::IDebugMgr *getDebugMgr() override {
		return m_ctxt->getDebugMgr();
	}

	virtual IModelValOp *getModelValOp() override {
		return m_ctxt->getModelValOp();
	}

    virtual IDataType *getDataTypeCore(DataTypeCoreE t) override {
        return m_ctxt->getDataTypeCore(t);
    }

    virtual IDataTypeArray *findDataTypeArray(
        IDataType               *type,
        uint32_t                size,
        bool                    create=true) override {
        return m_ctxt->findDataTypeArray(type, size, create);
    }

    virtual IDataTypeArray *mkDataTypeArray(
        IDataType               *type,
        bool                    owned,
        uint32_t                size) override {
        return m_ctxt->mkDataTypeArray(type, owned, size);
    }

    virtual bool addDataTypeArray(IDataTypeArray *t) override {
        return m_ctxt->addDataTypeArray(t);
    }

	virtual IDataTypeEnum *findDataTypeEnum(const std::string &name) override {
		return m_ctxt->findDataTypeEnum(name);
	}

	virtual IDataTypeEnum *mkDataTypeEnum(
			const std::string 	&name,
			bool				is_signed) override {
		return m_ctxt->mkDataTypeEnum(name, is_signed);
	}

	virtual bool addDataTypeEnum(IDataTypeEnum *e) override {
		return m_ctxt->addDataTypeEnum(e);
	}

	virtual IDataTypeInt *findDataTypeInt(
			bool			is_signed,
			int32_t			width,
            bool            create=true) override {
		return m_ctxt->findDataTypeInt(is_signed, width, create);
	}

	/**
	 * Returns a new datatype. The expectation is that
	 * it will be subsequently added to the context
	 */
	virtual IDataTypeInt *mkDataTypeInt(
			bool			is_signed,
			int32_t			width) override {
		return m_ctxt->mkDataTypeInt(is_signed, width);
	}

	virtual bool addDataTypeInt(IDataTypeInt *t) override {
		return m_ctxt->addDataTypeInt(t);
	}

    virtual IDataTypeList *findDataTypeList(
        IDataType               *elem_t,
        bool                    create=true) override {
        return m_ctxt->findDataTypeList(elem_t, create);
    }

	virtual IDataTypeStruct *findDataTypeStruct(const std::string &name) override {
		return m_ctxt->findDataTypeStruct(name);
	}

	virtual bool addDataTypeStruct(IDataTypeStruct *t) override {
		return m_ctxt->addDataTypeStruct(t);
	}

	virtual IDataTypeStruct *mkDataTypeStruct(const std::string &name) override {
		return m_ctxt->mkDataTypeStruct(name);
	}

    virtual const std::vector<IDataTypeStructUP> &getDataTypeStructs() const override {
        return m_ctxt->getDataTypeStructs();
    }

	virtual IDataTypeVec *findDataTypeVec(IDataType *t) override {
		return m_ctxt->findDataTypeVec(t);
	}

	virtual IDataTypeVec *mkDataTypeVec(IDataType *t) override {
		return m_ctxt->mkDataTypeVec(t);
	}

	virtual bool addDataTypeVec(IDataTypeVec *t) override {
		return m_ctxt->addDataTypeVec(t);
	}

	virtual IDataTypeWrapper *findDataTypeWrapper(
        IDataType       *type_phy,
        IDataType       *type_virt,
        bool            create) override {
        return m_ctxt->findDataTypeWrapper(type_phy, type_virt, create);
    }

	virtual IDataTypeWrapper *mkDataTypeWrapper(
        IDataType       *type_phy,
        IDataType       *type_virt) override {
        return m_ctxt->mkDataTypeWrapper(type_phy, type_virt);
    }

    virtual bool addDataTypeWrapper(IDataTypeWrapper *t) override {
        return m_ctxt->addDataTypeWrapper(t);
    }

    virtual ValRefInt evalBinOpInt(
        const vsc::dm::ValRefInt        &lhs,
        BinOp                           op,
        const vsc::dm::ValRefInt        &rhs) override {
        return m_ctxt->evalBinOpInt(lhs, op, rhs);
    }

    virtual ValRef evalBinOpStr(
        const vsc::dm::ValRefStr        &lhs,
        BinOp                           op,
        const vsc::dm::ValRefStr        &rhs) override {
        return m_ctxt->evalBinOpStr(lhs, op, rhs);
    }

	virtual IModelConstraintBlock *mkModelConstraintBlock(
			const std::string &name) override {
		return m_ctxt->mkModelConstraintBlock(name);
	}

	virtual IModelConstraintExpr *mkModelConstraintExpr(
			IModelExpr		*expr) override {
		return m_ctxt->mkModelConstraintExpr(expr);
	}

	virtual IModelConstraintForeach *mkModelConstraintForeach(
			IModelExpr			*target,
			const std::string	&index_it_name) override {
		return m_ctxt->mkModelConstraintForeach(target, index_it_name);
	}

	virtual IModelConstraintIfElse *mkModelConstraintIfElse(
			IModelExpr			*cond,
			IModelConstraint	*true_c,
			IModelConstraint	*false_c) override {
		return m_ctxt->mkModelConstraintIfElse(cond, true_c, false_c);
	}

	virtual IModelConstraintImplies *mkModelConstraintImplies(
			IModelExpr			*cond,
			IModelConstraint	*body,
            bool                cond_owned=true,
            bool                body_owned=true) override {
		return m_ctxt->mkModelConstraintImplies(cond, body);
	}

	virtual IModelConstraintRef *mkModelConstraintRef(
			IModelConstraint	*target) override {
		return m_ctxt->mkModelConstraintRef(target);
	}

	virtual IModelConstraintScope *mkModelConstraintScope() override {
		return m_ctxt->mkModelConstraintScope();
	}

	virtual IModelConstraintSoft *mkModelConstraintSoft(
		IModelConstraintExpr	*c) override {
		return m_ctxt->mkModelConstraintSoft(c);
	}

	virtual IModelConstraintSubst *mkModelConstraintSubst(
		IModelConstraint		*c) override {
		return m_ctxt->mkModelConstraintSubst(c);
	}

	virtual IModelConstraintUnique *mkModelConstraintUnique(
		const std::vector<IModelExpr *>		&exprs) override {
		return m_ctxt->mkModelConstraintUnique(exprs);
	}

	virtual IModelCoverBinCollection *mkModelCoverBinCollection(
		ModelCoverBinType			type) override {
		return m_ctxt->mkModelCoverBinCollection(type);
	}

	virtual IModelCoverBin *mkModelCoverBinSingleRange(
		const std::string			&name,
		ModelCoverBinType			type,
		bool						is_signed,
		IModelVal					*lower,
		IModelVal					*upper) override {
		return m_ctxt->mkModelCoverBinSingleRange(
			name, type, is_signed, lower, upper);
	}

	virtual IModelCoverBin *mkModelCoverBinSingleVal(
		const std::string			&name,
		ModelCoverBinType			type,
		IModelVal					*value) override {
		return m_ctxt->mkModelCoverBinSingleVal(name, type, value);
	}

	virtual IModelCoverCross *mkModelCoverCross(
		const std::string			&name,
		IModelCoverpointIff			*iff) override {
		return m_ctxt->mkModelCoverCross(name, iff);
	}

	virtual IModelCovergroup *mkModelCovergroup(
		const std::string			&name) override {
		return m_ctxt->mkModelCovergroup(name);
	}

	virtual IModelCoverpoint *mkModelCoverpoint(
		const std::string			&name,
		IModelCoverpointTarget		*target,
		IModelCoverpointIff			*iff) override {
		return m_ctxt->mkModelCoverpoint(name, target, iff);
	}

	virtual IModelCoverpointTarget *mkModelCoverpointTargetExpr(
		IModelExpr					*expr,
		int32_t						width) override {
		return m_ctxt->mkModelCoverpointTargetExpr(expr, width);
	}

	virtual IModelExprBin *mkModelExprBin(
			IModelExpr		*lhs,
			BinOp			op,
			IModelExpr		*rhs) override {
		return m_ctxt->mkModelExprBin(lhs, op, rhs);
	}

	virtual IModelExprCond *mkModelExprCond(
			IModelExpr		*cond,
			IModelExpr		*true_e,
			IModelExpr		*false_e) override {
		return m_ctxt->mkModelExprCond(cond, true_e, false_e);
	}

	virtual IModelExprFieldRef *mkModelExprFieldRef(
			IModelField		*field) override {
		return m_ctxt->mkModelExprFieldRef(field);
	}

	virtual IModelExprIn *mkModelExprIn(
			IModelExpr				*lhs,
			IModelExprRangelist		*rhs) override {
		return m_ctxt->mkModelExprIn(lhs, rhs);
	}

	virtual IModelExprIndexedFieldRef *mkModelExprIndexedFieldRef() override {
		return m_ctxt->mkModelExprIndexedFieldRef();
	}

	virtual IModelExprPartSelect *mkModelExprPartSelect(
			IModelExpr				*lhs,
			int32_t					lower,
			int32_t					upper) override {
		return m_ctxt->mkModelExprPartSelect(lhs, lower, upper);
	}

	virtual IModelExprRef *mkModelExprRef(IModelExpr *target) override {
		return m_ctxt->mkModelExprRef(target);
	}

	virtual IModelExprUnary *mkModelExprUnary(
		UnaryOp		op,
		IModelExpr	*e) override {
		return m_ctxt->mkModelExprUnary(op, e);
	}

	virtual IModelExprVal *mkModelExprVal(IModelVal *v) override {
		return m_ctxt->mkModelExprVal(v);
	}

	virtual IModelFieldRef *mkModelFieldRefRoot(
			IDataType			*type,
			const std::string	&name) override {
		return m_ctxt->mkModelFieldRefRoot(type, name);
	}

	virtual IModelFieldRef *mkModelFieldRefType(
			ITypeField			*type) override {
		return m_ctxt->mkModelFieldRefType(type);
	}

	virtual IModelFieldRoot *mkModelFieldRoot(
			IDataType 			*type,
			const std::string	&name,
            const ValRef        &val) override {
		return m_ctxt->mkModelFieldRoot(type, name, val);
	}

	virtual IModelFieldType *mkModelFieldType(
			ITypeField			*type,
            const ValRef        &val) override {
		return m_ctxt->mkModelFieldType(type, val);
	}

	virtual IModelFieldVec *mkModelFieldVecRoot(
			IDataType			*type,
			const std::string	&name) override {
		return m_ctxt->mkModelFieldVecRoot(type, name);
	}

	virtual IModelVal *mkModelVal() override {
		return m_ctxt->mkModelVal();
	}

	virtual IModelVal *mkModelValS(
            int64_t             val,
            int32_t             bits) override {
        return m_ctxt->mkModelValS(val, bits);
    }

	virtual IModelVal *mkModelValU(
            uint64_t            val,
            int32_t             bits) override {
        return m_ctxt->mkModelValU(val, bits);
    }
             

	virtual IRefSelector *mkRefSelector(
			IModelFieldRef						*ref,
			const std::vector<IModelField *>	&candidates) override {
		return m_ctxt->mkRefSelector(ref, candidates);
	}

	virtual ITask *mkTask(TaskE id) override {
		return m_ctxt->mkTask(id);
	}

    virtual ITypeExprArrayLiteral *mkTypeExprArrayLiteral(
            IDataTypeArray                  *arr_t,
            bool                            arr_t_owned,
            const std::vector<ITypeExpr *>  &vals) override {
        return m_ctxt->mkTypeExprArrayLiteral(arr_t, arr_t_owned, vals);
    }

    virtual ITypeExprArrIndex *mkTypeExprArrIndex(
            ITypeExpr       *root,
            bool            root_owned,
            ITypeExpr       *index,
            bool            index_owned) override {
        return m_ctxt->mkTypeExprArrIndex(root, root_owned, index, index_owned);
    }

	virtual ITypeExprBin *mkTypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs,
            bool            lhs_owned=true,
            bool            rhs_owned=true) override {
		return m_ctxt->mkTypeExprBin(lhs, op, rhs, lhs_owned, rhs_owned);
	}

    virtual ITypeExprEnumRef *mkTypeExprEnumRef(
        IDataTypeEnum       *enum_t,
        int32_t             enum_id) override {
        return m_ctxt->mkTypeExprEnumRef(enum_t, enum_id);
    }

	virtual ITypeExprRef *mkTypeExprRef(
            ITypeExpr       *target,
            bool            owned) override {
        return m_ctxt->mkTypeExprRef(target, owned);
    }

	virtual ITypeExprRefInline *mkTypeExprRefInline() override {
        return m_ctxt->mkTypeExprRefInline();
    }

	virtual ITypeExprRefBottomUp *mkTypeExprRefBottomUp(
            int32_t         scope_offset,
            int32_t         field_index) override {
        return m_ctxt->mkTypeExprRefBottomUp(scope_offset, field_index);
    }

	virtual ITypeExprRefPath *mkTypeExprRefPath(
        ITypeExpr       			*target,
        bool            			owned,
		const std::vector<int32_t>	&path) override {
		return m_ctxt->mkTypeExprRefPath(target, owned, path);
	}

	virtual ITypeExprRefTopDown *mkTypeExprRefTopDown() {
        return m_ctxt->mkTypeExprRefTopDown();
    }

    virtual ITypeExprStructLiteral *mkTypeExprStructLiteral(
            IDataTypeStruct                             *type,
            bool                                        owned,
            const std::vector<vsc::dm::ITypeExpr *>     &elems) override {
        return m_ctxt->mkTypeExprStructLiteral(type, owned, elems);
    }

    virtual ITypeExprSubField *mkTypeExprSubField(
            ITypeExpr       *root,
            bool            owned,
            int32_t         index) override {
        return m_ctxt->mkTypeExprSubField(root, owned, index);
    }

	virtual ITypeConstraintBlock *mkTypeConstraintBlock(const std::string &name) override {
		return m_ctxt->mkTypeConstraintBlock(name);
	}

	virtual ITypeConstraintExpr *mkTypeConstraintExpr(
            ITypeExpr       *e,
            bool            owned) override {
		return m_ctxt->mkTypeConstraintExpr(e, owned);
	}

    virtual ITypeConstraintForeach *mkTypeConstraintForeach(
            ITypeExpr           *target,
            bool                target_owned,
            const std::string   &iter_name,
            ITypeConstraint     *body,
            bool                body_owned) override {
        return m_ctxt->mkTypeConstraintForeach(
            target, target_owned, iter_name, body, body_owned);
    }

	virtual ITypeConstraintIfElse *mkTypeConstraintIfElse(
			ITypeExpr 		*cond,
			ITypeConstraint	*true_c,
			ITypeConstraint	*false_c,
            bool            cond_owned,
            bool            true_owned,
            bool            false_owned) override {
		return m_ctxt->mkTypeConstraintIfElse(
            cond, 
            true_c, 
            false_c,
            cond_owned,
            true_owned,
            true_owned);
	}

	virtual ITypeConstraintImplies *mkTypeConstraintImplies(
			ITypeExpr		*cond,
			ITypeConstraint	*body,
            bool            cond_owned=true,
            bool            body_owned=true) override {
		return m_ctxt->mkTypeConstraintImplies(cond, body, cond_owned, body_owned);
	}

	virtual ITypeConstraintScope *mkTypeConstraintScope() override {
		return m_ctxt->mkTypeConstraintScope();
	}

	virtual ITypeConstraintSoft *mkTypeConstraintSoft(
			ITypeConstraintExpr	*c) override {
		return m_ctxt->mkTypeConstraintSoft(c);
	}

	virtual ITypeConstraintUnique *mkTypeConstraintUnique(
			const std::vector<ITypeExpr *>		&exprs) override {
		return m_ctxt->mkTypeConstraintUnique(exprs);
	}

	virtual ITypeExprFieldRef *mkTypeExprFieldRef(
        ITypeExprFieldRef::RootRefKind      kind,
        int32_t                             offset,
        int32_t                             index) override {
		return m_ctxt->mkTypeExprFieldRef(kind, offset, index);
	}

	virtual ITypeExprRange *mkTypeExprRange(
			bool				is_single,
			ITypeExpr			*lower,
			ITypeExpr			*upper) override {
		return m_ctxt->mkTypeExprRange(is_single, lower, upper);
	}

	virtual ITypeExprRangelist *mkTypeExprRangelist() override {
		return m_ctxt->mkTypeExprRangelist();
	}

	virtual IModelExprRange *mkModelExprRange(
			bool			is_single,
			IModelExpr		*lower,
			IModelExpr		*upper) override {
		return m_ctxt->mkModelExprRange(is_single, lower, upper);
	}

	virtual IModelExprRangelist *mkModelExprRangelist() override {
		return m_ctxt->mkModelExprRangelist();
	}

    virtual ITypeExprUnary *mkTypeExprUnary(
        ITypeExpr       *target,
        bool            owned,
        UnaryOp         op) {
        return m_ctxt->mkTypeExprUnary(target, owned, op);
    }

	virtual ITypeExprVal *mkTypeExprVal(
        IDataType       *type,
        ValData         v) override {
		return m_ctxt->mkTypeExprVal(type, v);
	}

    virtual ITypeExprVal *mkTypeExprVal(const ValRef &v) override {
        return m_ctxt->mkTypeExprVal(v);
    }

	virtual ITypeFieldPhy *mkTypeFieldPhy(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
            ITypeExpr				*init) override {
		return m_ctxt->mkTypeFieldPhy(name, dtype, own_dtype, attr, init);
	}

	virtual ITypeFieldRef *mkTypeFieldRef(
			const std::string		&name,
			IDataType				*dtype,
			TypeFieldAttr			attr) override {
		return m_ctxt->mkTypeFieldRef(name, dtype, attr);
	}

	virtual ITypeFieldVec *mkTypeFieldVec(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			IModelVal				*init_sz) override {
		return m_ctxt->mkTypeFieldVec(name, dtype,
			own_dtype, attr, init_sz);
	}

    virtual ValRef mkValRef(IDataType *t) override {
        return m_ctxt->mkValRef(t);
    }
    
    virtual ValRefArr mkValRefArr(IDataTypeArray *t) override {
        return m_ctxt->mkValRefArr(t);
    }

    virtual ValRefBool mkValRefBool(
        bool        value) override {
        return m_ctxt->mkValRefBool(value);
    }

    virtual ValRefInt mkValRefInt(
        int64_t value,
        bool    is_signed, 
        int32_t width) {
        return m_ctxt->mkValRefInt(value, is_signed, width);
    }

    virtual ValRef mkValRefRawPtr(void *ptr) override {
        return m_ctxt->mkValRefRawPtr(ptr);
    }

    virtual ValRefStr mkValRefStr(const std::string &str, int32_t reserve=0) override {
        return m_ctxt->mkValRefStr(str, reserve);
    }

    virtual ValRefStruct mkValRefStruct(IDataTypeStruct *t) override {
        return m_ctxt->mkValRefStruct(t);
    }

    virtual Val *mkVal(uint32_t nbytes) override {
        return m_ctxt->mkVal(nbytes);
    }

    virtual void freeVal(Val *v) override {
        return m_ctxt->freeVal(v);
    }

protected:
    IContext *ctxt() const { return m_ctxt.get(); }

protected:
	UP<IContext>				m_ctxt;

};


}
}
