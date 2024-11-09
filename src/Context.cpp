/*
 * Copyright 2019-2021 Matthew Ballance and contributors
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
 * Context.cpp
 *
 *  Created on: Sep 8, 2021
 *      Author: mballance
 */

#include "vsc/dm/impl/ModelBuildContext.h"
#include "vsc/dm/impl/ValRef.h"
#include "vsc/dm/impl/ValRefArr.h"
#include "vsc/dm/impl/ValRefInt.h"
#include "vsc/dm/impl/ValRefStr.h"
#include "Context.h"
#include "DataTypeArray.h"
#include "DataTypeBool.h"
#include "DataTypeEnum.h"
#include "DataTypeList.h"
#include "DataTypePtr.h"
#include "DataTypeString.h"
#include "DataTypeStruct.h"
#include "DataTypeWrapper.h"
#include "ModelConstraintBlock.h"
#include "ModelConstraintExpr.h"
#include "ModelConstraintIfElse.h"
#include "ModelConstraintImplies.h"
#include "ModelConstraintRef.h"
#include "ModelConstraintScope.h"
#include "ModelConstraintSoft.h"
#include "ModelConstraintSubst.h"
#include "ModelConstraintUnique.h"
#include "ModelCoverBinCollection.h"
#include "ModelCoverBinSingleRange.h"
#include "ModelCoverBinSingleVal.h"
#include "ModelCoverCross.h"
#include "ModelCovergroup.h"
#include "ModelCoverpoint.h"
#include "ModelCoverpointTargetExpr.h"
#include "ModelExprBin.h"
#include "ModelExprCond.h"
#include "ModelExprFieldRef.h"
#include "ModelExprIn.h"
#include "ModelExprIndexedFieldRef.h"
#include "ModelExprPartSelect.h"
#include "ModelExprRange.h"
#include "ModelExprRangelist.h"
#include "ModelExprRef.h"
#include "ModelExprUnary.h"
#include "ModelExprVal.h"
#include "ModelFieldRefRoot.h"
#include "ModelFieldRefType.h"
#include "ModelFieldRoot.h"
#include "ModelFieldType.h"
#include "ModelVal.h"
#include "RefSelector.h"
#include "vsc/dm/impl/TaskSetUsedRand.h"
#include "TaskEvalBinOpInt.h"
#include "TaskEvalBinOpStr.h"
#include "TypeConstraintBlock.h"
#include "TypeConstraintExpr.h"
#include "TypeConstraintForeach.h"
#include "TypeConstraintIfElse.h"
#include "TypeConstraintImplies.h"
#include "TypeConstraintScope.h"
#include "TypeConstraintSoft.h"
#include "TypeConstraintUnique.h"
#include "TypeExprArrayLiteral.h"
#include "TypeExprArrIndex.h"
#include "TypeExprBin.h"
#include "TypeExprFieldRef.h"
#include "TypeExprRange.h"
#include "TypeExprRangelist.h"
#include "TypeExprRef.h"
#include "TypeExprRefInline.h"
#include "TypeExprRefBottomUp.h"
#include "TypeExprRefPath.h"
#include "TypeExprRefTopDown.h"
#include "TypeExprStructLiteral.h"
#include "TypeExprSubField.h"
#include "TypeExprVal.h"
#include "TypeExprUnary.h"
#include "TypeFieldPhy.h"
#include "TypeFieldRef.h"
#include "TypeFieldVec.h"
#include "VscImpl.h"

namespace vsc {
namespace dm {

Context::Context(dmgr::IDebugMgr *dm) : m_dbg_mgr(dm) {
	// TODO Auto-generated constructor stub
    m_type_bool = IDataTypeBoolUP(new DataTypeBool(this));
    m_type_vptr = IDataTypeUP(new DataTypePtr(this));
    m_type_string = IDataTypeStringUP(new DataTypeString(this));

}

Context::~Context() {
	// TODO Auto-generated destructor stub
}

IModelField *Context::buildModelField(
		IDataTypeStruct			*dt,
		const std::string		&name) {
	ModelBuildContext ctxt(this);
	return dt->mkRootField(&ctxt, name, false);
}

dmgr::IDebugMgr *Context::getDebugMgr() {
    return m_dbg_mgr;
}

#ifdef UNDEFINED
ICompoundSolver *Context::mkCompoundSolver() {
	return new CompoundSolverDefault(this);
}
#endif

IDataType *Context::getDataTypeCore(DataTypeCoreE t) {
    switch (t) {
        case DataTypeCoreE::Bool: return m_type_bool.get();
        case DataTypeCoreE::Ptr: return m_type_vptr.get();
        case DataTypeCoreE::String: return m_type_string.get();
    }
    return 0;
}

IDataTypeArray *Context::findDataTypeArray(
        IDataType               *type,
        uint32_t                size,
        bool                    create) {
    IDataTypeArray *ret = 0;
    std::unordered_map<IDataType *, ArrayTypeInfo>::iterator it_t;

    if ((it_t=m_array_type_m.find(type)) == m_array_type_m.end()) {
        if (create) {
            it_t = m_array_type_m.insert({type, ArrayTypeInfo()}).first;
        }
    }

    if (it_t != m_array_type_m.end()) {
        ArrayTypeInfo::iterator it_s;
        
        if ((it_s=it_t->second.find(size)) == it_t->second.end()) {
            if (create) {

            }
        }

        if (it_s != it_t->second.end()) {
            ret = it_s->second;
        } else if (create) {
            ret = mkDataTypeArray(type, false, size);
            it_t->second.insert({size, ret});
            m_array_type_l.push_back(IDataTypeArrayUP(ret));
        }
    }

    return ret;
}

IDataTypeArray *Context::mkDataTypeArray(
        IDataType               *type,
        bool                    owned,
        uint32_t                size) {
    return new DataTypeArray(type, owned, size);
}

bool Context::addDataTypeArray(IDataTypeArray *t) {
    std::unordered_map<IDataType *, ArrayTypeInfo>::iterator it_t;

    if ((it_t=m_array_type_m.find(t->getElemType())) == m_array_type_m.end()) {
        it_t = m_array_type_m.insert({t->getElemType(), ArrayTypeInfo()}).first;
    }

    ArrayTypeInfo::iterator it_s;
        
    if ((it_s=it_t->second.find(t->getSize())) == it_t->second.end()) {
        it_t->second.insert({t->getSize(), t});
        m_array_type_l.push_back(IDataTypeArrayUP(t));
        return true;
    } else {
        return false;
    }
}

IDataTypeEnum *Context::findDataTypeEnum(const std::string &name) {
	std::unordered_map<std::string, IDataTypeEnum *>::const_iterator it;
	it = m_enum_type_m.find(name);

	if (it != m_enum_type_m.end()) {
		return it->second;
	} else {
		return 0;
	}
}

IDataTypeEnum *Context::mkDataTypeEnum(
			const std::string 	&name,
			bool				is_signed) {
	return new DataTypeEnum(name, is_signed);
}

bool Context::addDataTypeEnum(IDataTypeEnum *e) {
	std::unordered_map<std::string, IDataTypeEnum *>::const_iterator it;

    e->finalize(this);

	it = m_enum_type_m.find(e->name());

	if (it != m_enum_type_m.end()) {
		m_enum_type_m.insert({e->name(), e});
		m_enum_type_l.push_back(IDataTypeEnumUP(e));
		return true;
	} else {
		return false;
	}
}

ValRefInt Context::evalBinOpInt(
        const vsc::dm::ValRefInt        &lhs,
        BinOp                           op,
        const vsc::dm::ValRefInt        &rhs) {
    return TaskEvalBinOpInt(this).eval(lhs, op, rhs);
}

ValRef Context::evalBinOpStr(
        const vsc::dm::ValRefStr        &lhs,
        BinOp                           op,
        const vsc::dm::ValRefStr        &rhs) {
    return TaskEvalBinOpStr(this).eval(lhs, op, rhs);
}

IModelConstraintBlock *Context::mkModelConstraintBlock(
			const std::string &name) {
	return new ModelConstraintBlock(name);
}

IModelConstraintExpr *Context::mkModelConstraintExpr(
			IModelExpr		*expr) {
	return new ModelConstraintExpr(expr);
}

IModelConstraintForeach *Context::mkModelConstraintForeach(
			IModelExpr			*target,
			const std::string	&index_it_name) {
//	return new ModelConstraintForeach(this, target, index_it_name);
    return 0;
}

IModelConstraintIfElse *Context::mkModelConstraintIfElse(
			IModelExpr			*cond,
			IModelConstraint	*true_c,
			IModelConstraint	*false_c) {
	return new ModelConstraintIfElse(cond, true_c, false_c);
}

IModelConstraintImplies *Context::mkModelConstraintImplies(
			IModelExpr			*cond,
			IModelConstraint	*body,
            bool                cond_owned,
            bool                body_owned) {
	return new ModelConstraintImplies(cond, body, cond_owned, body_owned);
}

IModelConstraintRef *Context::mkModelConstraintRef(
			IModelConstraint	*target) {
	return new ModelConstraintRef(target);
}

IModelConstraintScope *Context::mkModelConstraintScope() {
	return new ModelConstraintScope();
}

IModelConstraintSoft *Context::mkModelConstraintSoft(
			IModelConstraintExpr	*c) {
	return new ModelConstraintSoft(c);
}

IModelConstraintSubst *Context::mkModelConstraintSubst(
			IModelConstraint	*c) {
	return new ModelConstraintSubst(c);
}

IModelConstraintUnique *Context::mkModelConstraintUnique(
			const std::vector<IModelExpr *>		&exprs) {
	return new ModelConstraintUnique(exprs);
}

IModelCoverBinCollection *Context::mkModelCoverBinCollection(
		ModelCoverBinType			type) {
	return new ModelCoverBinCollection(type);
}

IModelCoverBin *Context::mkModelCoverBinSingleRange(
		const std::string			&name,
		ModelCoverBinType			type,
		bool						is_signed,
		IModelVal					*lower,
		IModelVal					*upper) {
	return new ModelCoverBinSingleRange(name, type, is_signed, lower, upper);
}

IModelCoverBin *Context::mkModelCoverBinSingleVal(
		const std::string			&name,
		ModelCoverBinType			type,
		IModelVal					*value) {
	return new ModelCoverBinSingleVal(name, type, value);
}

IModelCoverCross *Context::mkModelCoverCross(
		const std::string			&name,
		IModelCoverpointIff			*iff) {
	return new ModelCoverCross(name, iff);
}

IModelCovergroup *Context::mkModelCovergroup(
		const std::string			&name) {
	return new ModelCovergroup(name);
}

IModelCoverpoint *Context::mkModelCoverpoint(
		const std::string			&name,
		IModelCoverpointTarget		*target,
		IModelCoverpointIff			*iff) {
	return new ModelCoverpoint(name, target, iff);
}

IModelCoverpointTarget *Context::mkModelCoverpointTargetExpr(
		IModelExpr					*expr,
		int32_t						width) {
	return new ModelCoverpointTargetExpr(this, expr, width);
}

IDataTypeInt *Context::findDataTypeInt(
			bool			is_signed,
			int32_t			width,
            bool            create) {
	if (is_signed) {
		auto it = m_sint_type_m.find(width);
		if (it != m_sint_type_m.end()) {
			return it->second;
		}
	} else {
		auto it = m_uint_type_m.find(width);
		if (it != m_uint_type_m.end()) {
			return it->second;
		}
	}

    if (create) {
        IDataTypeInt *t = mkDataTypeInt(is_signed, width);
        addDataTypeInt(t);
        return t;
    } else {
    	return 0;
    }
}

IDataTypeInt *Context::mkDataTypeInt(
			bool			is_signed,
			int32_t			width) {
	return new DataTypeInt(is_signed, width);
}

bool Context::addDataTypeInt(IDataTypeInt *t) {
    t->finalize(this);
	if (t->is_signed()) {
		auto it = m_sint_type_m.find(t->width());
		if (it == m_sint_type_m.end()) {
			m_sint_type_m.insert({t->width(), t});
			m_sint_type_l.push_back(IDataTypeIntUP(t));
			return true;
		}
	} else {
		auto it = m_uint_type_m.find(t->width());
		if (it == m_uint_type_m.end()) {
			m_uint_type_m.insert({t->width(), t});
			m_uint_type_l.push_back(IDataTypeIntUP(t));
			return true;
		}
	}
	return false;
}

IDataTypeList *Context::findDataTypeList(
        IDataType               *elem_t,
        bool                    create) {
    IDataTypeList *ret = 0;
    std::unordered_map<IDataType *, IDataTypeList *>::const_iterator it;

    if ((it=m_list_type_m.find(elem_t)) != m_list_type_m.end()) {
        ret = it->second;
    } else if (create) {
        ret = new DataTypeList(elem_t);
    }
    return ret;
}

IDataTypeStruct *Context::findDataTypeStruct(const std::string &name) {
	auto it = m_struct_type_m.find(name);

	if (it != m_struct_type_m.end()) {
		return it->second;
	} else {
		return 0;
	}
}

IDataTypeStruct *Context::mkDataTypeStruct(const std::string &name) {
	return new DataTypeStruct(name);
}

bool Context::addDataTypeStruct(IDataTypeStruct *t) {
    t->finalize(this);

	auto it = m_struct_type_m.find(t->name());

	if (it == m_struct_type_m.end()) {
		m_struct_type_m.insert({t->name(), t});
		m_struct_type_l.push_back(IDataTypeStructUP(t));
		return true;
	} else {
		return false;
	}
}

const std::vector<IDataTypeStructUP> &Context::getDataTypeStructs() const {
    return m_struct_type_l;
}

IDataTypeVec *Context::findDataTypeVec(IDataType *t) {
	std::unordered_map<IDataType*,IDataTypeVec*>::const_iterator it;

	if ((it=m_vec_type_m.find(t)) != m_vec_type_m.end()) {
		return it->second;
	} else {
		return 0;
	}
}

IDataTypeWrapper *Context::findDataTypeWrapper(
        IDataType       *type_phy,
        IDataType       *type_virt,
        bool            create) {
    std::unordered_map<IDataType *, DataTypeWrapperM *>::iterator it;

    it = m_wrapper_type_phy_m.find(type_phy);

    if (it == m_wrapper_type_phy_m.end()) {
        if (create) {
            DataTypeWrapperM *wm = new DataTypeWrapperM();
            it = m_wrapper_type_phy_m.insert({type_phy, wm}).first;
            m_wrapper_m_l.push_back(DataTypeWrapperMUP(wm));
        } else {
            return 0;
        }
    }
    std::unordered_map<IDataType *, IDataTypeWrapper *>::iterator itw;

    itw = it->second->m_wrapper_type_virt_m.find(type_virt);
    if (itw == it->second->m_wrapper_type_virt_m.end()) {
        if (create) {
            DataTypeWrapper *w = new DataTypeWrapper(type_phy, type_virt);
            itw = it->second->m_wrapper_type_virt_m.insert({type_virt, w}).first;
            m_wrapper_l.push_back(IDataTypeWrapperUP(w));
        } else {
            return 0;
        }
    }
    return itw->second;
}

IDataTypeWrapper *Context::mkDataTypeWrapper(
        IDataType       *type_phy,
        IDataType       *type_virt) {
    return new DataTypeWrapper(type_phy, type_virt);
}

bool Context::addDataTypeWrapper(IDataTypeWrapper *t) {
    std::unordered_map<IDataType *, DataTypeWrapperM *>::iterator it;

    it = m_wrapper_type_phy_m.find(t->getDataTypePhy());

    if (it == m_wrapper_type_phy_m.end()) {
        DataTypeWrapperM *wm = new DataTypeWrapperM();
        it = m_wrapper_type_phy_m.insert({t->getDataTypePhy(), wm}).first;
        m_wrapper_m_l.push_back(DataTypeWrapperMUP(wm));
    }
    std::unordered_map<IDataType *, IDataTypeWrapper *>::iterator itw;

    itw = it->second->m_wrapper_type_virt_m.find(t->getDataTypeVirt());
    if (itw == it->second->m_wrapper_type_virt_m.end()) {
        it->second->m_wrapper_type_virt_m.insert({t->getDataTypeVirt(), t});
        m_wrapper_l.push_back(IDataTypeWrapperUP(t));
        return true;
    } else {
        return false;
    }
}

IDataTypeVec *Context::mkDataTypeVec(IDataType *t) {
	return 0;
}

bool Context::addDataTypeVec(IDataTypeVec *t) {
	return false;
}

IModelExprBin *Context::mkModelExprBin(
			IModelExpr		*lhs,
			BinOp			op,
			IModelExpr		*rhs) {
	return new ModelExprBin(lhs, op, rhs);
}

IModelExprCond *Context::mkModelExprCond(
			IModelExpr		*cond,
			IModelExpr		*true_e,
			IModelExpr		*false_e) {
	return new ModelExprCond(cond, true_e, false_e);
}

IModelExprFieldRef *Context::mkModelExprFieldRef(
			IModelField		*field) {
	return new ModelExprFieldRef(field);
}

IModelExprIn *Context::mkModelExprIn(
			IModelExpr				*lhs,
			IModelExprRangelist		*rnglist) {
	return new ModelExprIn(lhs, rnglist);
}

IModelExprIndexedFieldRef *Context::mkModelExprIndexedFieldRef() {
	return new ModelExprIndexedFieldRef();
}

IModelExprPartSelect *Context::mkModelExprPartSelect(
			IModelExpr				*lhs,
			int32_t					lower,
			int32_t					upper) {
	return new ModelExprPartSelect(lhs, lower, upper);
}

IModelExprRange *Context::mkModelExprRange(
			bool			is_single,
			IModelExpr		*lower,
			IModelExpr		*upper) {
	return new ModelExprRange(
			is_single,
			lower,
			upper);
}

IModelExprRangelist *Context::mkModelExprRangelist() {
	return new ModelExprRangelist();
}

IModelExprRef *Context::mkModelExprRef(IModelExpr *target) {
	return new ModelExprRef(target);
}

IModelExprUnary *Context::mkModelExprUnary(
		UnaryOp		op,
		IModelExpr	*e) {
	return new ModelExprUnary(op, e);
}

IModelExprVal *Context::mkModelExprVal(IModelVal *v) {
	if (v) {
		return new ModelExprVal(v);
	} else {
		return new ModelExprVal();
	}
}

IModelFieldRef *Context::mkModelFieldRefRoot(
			IDataType 			*type,
			const std::string	&name) {
	return new ModelFieldRefRoot(type, name);
}

IModelFieldRef *Context::mkModelFieldRefType(ITypeField *type) {
	return new ModelFieldRefType(type);
}

IModelFieldRoot *Context::mkModelFieldRoot(
			IDataType 			*type,
			const std::string	&name,
            const ValRef        &val) {
	return new ModelFieldRoot(type, name, val);
}

IModelFieldType *Context::mkModelFieldType(
			ITypeField			*type,
            const ValRef        &val) {
	return new ModelFieldType(type, val);
}

IModelFieldVec *Context::mkModelFieldVecRoot(
			IDataType			*type,
			const std::string	&name) {
    /*
	return new ModelFieldVecRoot(
			this,
			type,
			name);
     */
    return 0;
}

IModelVal *Context::mkModelVal() {
	return new ModelVal();
}

IModelVal *Context::mkModelValS(
            int64_t             val,
            int32_t             bits) {
    IModelVal *ret = new ModelVal();
    ret->setBits(bits);
    ret->set_val_i(val);
    return ret;
}

IModelVal *Context::mkModelValU(
            uint64_t            val,
            int32_t             bits) {
    IModelVal *ret = new ModelVal();
    ret->setBits(bits);
    ret->set_val_u(val);
    return ret;
}

#ifdef UNDEFINED
IRandomizer *Context::mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) {
	return new Randomizer(solver_factory, randstate);
}

IRandState *Context::mkRandState(const std::string &seed) {
	return new RandState(seed);
}
#endif

IRefSelector *Context::mkRefSelector(
			IModelFieldRef						*ref,
			const std::vector<IModelField *>	&candidates) {
	return new RefSelector(this, ref, candidates);
}

ITask *Context::mkTask(TaskE id) {
	switch (id) {
	/*
	case TaskE::SetUsedRand:
		return new TaskSetUsedRand();
		 */
	default:
		return 0;
	}
}

ITypeConstraintBlock *Context::mkTypeConstraintBlock(const std::string &name) {
	return new TypeConstraintBlock(name);
}

ITypeConstraintExpr *Context::mkTypeConstraintExpr(
    ITypeExpr       *expr,
    bool            owned) {
	return new TypeConstraintExpr(expr, owned);
}

ITypeConstraintForeach *Context::mkTypeConstraintForeach(
            ITypeExpr           *target,
            bool                target_owned,
            const std::string   &iter_name,
            ITypeConstraint     *body,
            bool                body_owned) {
    return new TypeConstraintForeach(
        this,
        target,
        target_owned,
        iter_name,
        body,
        body_owned);
}

ITypeConstraintIfElse *Context::mkTypeConstraintIfElse(
			ITypeExpr 		*cond,
			ITypeConstraint	*true_c,
			ITypeConstraint	*false_c,
            bool            cond_owned,
            bool            true_owned,
            bool            false_owned) {
	return new TypeConstraintIfElse(
        cond, 
        cond_owned,
        true_c, 
        true_owned,
        false_c,
        false_owned);
}

ITypeConstraintImplies *Context::mkTypeConstraintImplies(
			ITypeExpr 		*cond,
			ITypeConstraint	*body,
            bool            cond_owned,
            bool            body_owned) {
	return new TypeConstraintImplies(cond, body, cond_owned, body_owned);
}

ITypeConstraintScope *Context::mkTypeConstraintScope() {
	return new TypeConstraintScope();
}

ITypeConstraintSoft *Context::mkTypeConstraintSoft(
			ITypeConstraintExpr		*c) {
	return new TypeConstraintSoft(c);
}

ITypeConstraintUnique *Context::mkTypeConstraintUnique(
			const std::vector<ITypeExpr *>		&exprs) {
	return new TypeConstraintUnique(exprs);
}

ITypeExprArrayLiteral *Context::mkTypeExprArrayLiteral(
            IDataTypeArray                  *arr_t,
            bool                            arr_t_owned,
            const std::vector<ITypeExpr *>  &vals) {
    return new TypeExprArrayLiteral(arr_t, arr_t_owned, vals);
}

ITypeExprArrIndex *Context::mkTypeExprArrIndex(
            ITypeExpr       *root,
            bool            root_owned,
            ITypeExpr       *index,
            bool            index_owned) {
    return new TypeExprArrIndex(root, root_owned, index, index_owned);
}

ITypeExprBin *Context::mkTypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs,
            bool            lhs_owned,
            bool            rhs_owned) {
	return new TypeExprBin(lhs, op, rhs, lhs_owned, rhs_owned);
}

ITypeExprFieldRef *Context::mkTypeExprFieldRef(
        ITypeExprFieldRef::RootRefKind      kind,
        int32_t                             offset,
        int32_t                             index) {
	return new TypeExprFieldRef(kind, offset, index);
}

ITypeExprRange *Context::mkTypeExprRange(
			bool				is_single,
			ITypeExpr			*lower,
			ITypeExpr			*upper) {
	return new TypeExprRange(
			is_single,
			lower,
			upper);
}

ITypeExprRangelist *Context::mkTypeExprRangelist() {
	return new TypeExprRangelist();
}

ITypeExprRef *Context::mkTypeExprRef(
            ITypeExpr       *target,
            bool            owned) {
    return new TypeExprRef(target, owned);
}

ITypeExprRefInline *Context::mkTypeExprRefInline() {
    return new TypeExprRefInline();
}

ITypeExprRefBottomUp *Context::mkTypeExprRefBottomUp(
            int32_t         scope_offset,
            int32_t         field_index) {
    return new TypeExprRefBottomUp(scope_offset, field_index);
}

ITypeExprRefPath *Context::mkTypeExprRefPath(
        ITypeExpr       			*root,
        bool            			owned,
		const std::vector<int32_t>	&path) {
	return new TypeExprRefPath(root, owned, path);
}

ITypeExprRefTopDown *Context::mkTypeExprRefTopDown() {
    return new TypeExprRefTopDown();
}

ITypeExprStructLiteral *Context::mkTypeExprStructLiteral(
            IDataTypeStruct                             *type,
            bool                                        owned,
            const std::vector<vsc::dm::ITypeExpr *>     &elems) {
    return new TypeExprStructLiteral(type, owned, elems);
}

ITypeExprSubField *Context::mkTypeExprSubField(
            ITypeExpr       *root,
            bool            owned,
            int32_t         index) {
    return new TypeExprSubField(root, owned, index);
}

ITypeExprUnary *Context::mkTypeExprUnary(
        ITypeExpr       *target,
        bool            owned,
        UnaryOp         op) {
    return new TypeExprUnary(target, owned, op);
}

ITypeExprVal *Context::mkTypeExprVal(
    IDataType           *type,
    ValData              v) {
	return new TypeExprVal(type, v);
}

ITypeExprVal *Context::mkTypeExprVal(const ValRef &v) {
    return new TypeExprVal(v);
}

ITypeFieldPhy *Context::mkTypeFieldPhy(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
            ITypeExpr				*init) {
	return new TypeFieldPhy(
			name,
			dtype,
			own_dtype,
			attr,
			init);
}

ITypeFieldRef *Context::mkTypeFieldRef(
			const std::string		&name,
			IDataType				*dtype,
			TypeFieldAttr			attr) {
	return new TypeFieldRef(name, dtype, attr);
}

ITypeFieldVec *Context::mkTypeFieldVec(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			IModelVal				*init_sz) {
	return new TypeFieldVec(this, name, dtype, own_dtype, attr, init_sz);
}

Val *Context::mkVal(uint32_t nbytes) {
    Val *ret = m_val_alloc.alloc(nbytes);
    ret->p.ap = this;
    return ret;
}

void Context::freeVal(Val *v) {
    m_val_alloc.free(v);
}

ValRef Context::mkValRef(IDataType *t) {

}

ValRefArr Context::mkValRefArr(IDataTypeArray *t) {
    Val *v = mkVal(t->getByteSize());
    return ValRefArr(ValRef(
        Val::Val2ValPtr(v), 
        t, 
        ValRef::Flags::Owned | ValRef::Flags::Mutable));
}

ValRefBool Context::mkValRefBool(bool value) {
    return ValRefBool(ValRef(value, m_type_bool.get(), 
        ValRef::Flags::Mutable|ValRef::Flags::Scalar));
}

ValRefInt Context::mkValRefInt(
    int64_t     value,
    bool        is_signed, 
    int32_t     width) {
    IDataTypeInt *type = findDataTypeInt(is_signed, width);
    if (!type) {
        type = mkDataTypeInt(is_signed, width);
        addDataTypeInt(type);
    }
    if (width <= ValRefInt::native_sz()) {
        return ValRefInt(
            value, 
            type, 
            ValRef::Flags::Mutable|ValRef::Flags::Scalar);
    } else {
        int32_t byte_sz = ((width-1)/8)+1;
        Val *vp = mkVal(byte_sz);
        ValRefInt ret(
            Val::Val2ValPtr(vp), 
            type, 
            (ValRef::Flags::Owned|ValRef::Flags::Mutable|ValRef::Flags::Scalar));
        ret.set_val(value);
        return ret;
    }
}

ValRef Context::mkValRefRawPtr(void *ptr) {
    return ValRef(
        reinterpret_cast<uintptr_t>(ptr), 
        getDataTypeCore(DataTypeCoreE::Ptr), 
        ValRef::Flags::None|ValRef::Flags::Scalar);
}

ValRefStr Context::mkValRefStr(const std::string &str, int32_t reserve) {
    return ValRefStr(
        this, 
        getDataTypeCore(DataTypeCoreE::String),
        str, 
        reserve);
}

ValRefStruct Context::mkValRefStruct(IDataTypeStruct *t) {
    Val *v = mkVal(t->getByteSize());
//    t->initVal(Val::Val2ValPtr(v));
    return ValRefStruct(Val::Val2ValPtr(v), t, 
        ValRef::Flags::Owned
        | ValRef::Flags::Mutable);
}

}
} /* namespace vsc */
