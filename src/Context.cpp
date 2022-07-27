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

#include "Context.h"
#include "CompoundSolverDefault.h"
#include "DataTypeEnum.h"
#include "DataTypeStruct.h"
#include "ModelConstraintBlock.h"
#include "ModelConstraintExpr.h"
#include "ModelConstraintForeach.h"
#include "ModelConstraintIfElse.h"
#include "ModelConstraintImplies.h"
#include "ModelConstraintScope.h"
#include "ModelConstraintSoft.h"
#include "ModelConstraintUnique.h"
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
#include "ModelFieldVecRoot.h"
#include "ModelVal.h"
#include "Randomizer.h"
#include "RandState.h"
#include "TaskModelFieldBuilder.h"
#include "TaskSetUsedRand.h"
#include "TypeConstraintBlock.h"
#include "TypeConstraintExpr.h"
#include "TypeConstraintIfElse.h"
#include "TypeConstraintImplies.h"
#include "TypeConstraintScope.h"
#include "TypeConstraintSoft.h"
#include "TypeConstraintUnique.h"
#include "TypeExprBin.h"
#include "TypeExprFieldRef.h"
#include "TypeExprRange.h"
#include "TypeExprRangelist.h"
#include "TypeExprVal.h"
#include "TypeFieldPhy.h"
#include "TypeFieldRef.h"
#include "TypeFieldVec.h"

namespace vsc {

Context::Context() {
	// TODO Auto-generated constructor stub

}

Context::~Context() {
	// TODO Auto-generated destructor stub
}

IModelField *Context::buildModelField(
		IDataTypeStruct			*dt,
		const std::string		&name) {
	return TaskModelFieldBuilder(this).build(dt, name);
}

ICompoundSolver *Context::mkCompoundSolver() {
	return new CompoundSolverDefault(this);
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
	it = m_enum_type_m.find(e->name());

	if (it != m_enum_type_m.end()) {
		m_enum_type_m.insert({e->name(), e});
		m_enum_type_l.push_back(IDataTypeEnumUP(e));
		return true;
	} else {
		return false;
	}
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
	return new ModelConstraintForeach(this, target, index_it_name);
}

IModelConstraintIfElse *Context::mkModelConstraintIfElse(
			IModelExpr			*cond,
			IModelConstraint	*true_c,
			IModelConstraint	*false_c) {
	return new ModelConstraintIfElse(cond, true_c, false_c);
}

IModelConstraintImplies *Context::mkModelConstraintImplies(
			IModelExpr			*cond,
			IModelConstraint	*body) {
	return new ModelConstraintImplies(cond, body);
}

IModelConstraintScope *Context::mkModelConstraintScope() {
	return new ModelConstraintScope();
}

IModelConstraintSoft *Context::mkModelConstraintSoft(
			IModelConstraintExpr	*c) {
	return new ModelConstraintSoft(c);
}

IModelConstraintUnique *Context::mkModelConstraintUnique(
			const std::vector<IModelExpr *>		&exprs) {
	return new ModelConstraintUnique(exprs);
}

IDataTypeInt *Context::findDataTypeInt(
			bool			is_signed,
			int32_t			width) {
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
	return 0;
}

IDataTypeInt *Context::mkDataTypeInt(
			bool			is_signed,
			int32_t			width) {
	return new DataTypeInt(is_signed, width);
}

bool Context::addDataTypeInt(IDataTypeInt *t) {
	if (t->is_signed()) {
		auto it = m_sint_type_m.find(t->width());
		if (it != m_sint_type_m.end()) {
			m_sint_type_m.insert({t->width(), t});
			m_sint_type_l.push_back(IDataTypeIntUP(t));
			return true;
		}
	} else {
		auto it = m_uint_type_m.find(t->width());
		if (it != m_uint_type_m.end()) {
			m_uint_type_m.insert({t->width(), t});
			m_uint_type_l.push_back(IDataTypeIntUP(t));
			return true;
		}
	}
	return false;
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
	auto it = m_struct_type_m.find(t->name());

	if (it == m_struct_type_m.end()) {
		m_struct_type_m.insert({t->name(), t});
		m_struct_type_l.push_back(IDataTypeStructUP(t));
		return true;
	} else {
		return false;
	}
}

IDataTypeVec *Context::findDataTypeVec(IDataType *t) {
	std::unordered_map<IDataType*,IDataTypeVec*>::const_iterator it;

	if ((it=m_vec_type_m.find(t)) != m_vec_type_m.end()) {
		return it->second;
	} else {
		return 0;
	}
}

IDataTypeVec *Context::mkDataTypeVec(IDataType *t) {

}

bool *Context::addDataTypeVec(IDataTypeVec *t) {

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
			const std::string	&name) {
	return new ModelFieldRoot(type, name);
}

IModelFieldType *Context::mkModelFieldType(
			ITypeField			*type) {
	return new ModelFieldType(type);
}

IModelFieldVec *Context::mkModelFieldVecRoot(
			IDataType			*type,
			const std::string	&name) {
	return new ModelFieldVecRoot(
			this,
			type,
			name);
}

IModelVal *Context::mkModelVal() {
	return new ModelVal();
}

IRandomizer *Context::mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) {
	return new Randomizer(solver_factory, randstate);
}

IRandState *Context::mkRandState(const std::string &seed) {
	return new RandState(seed);
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

ITypeConstraintExpr *Context::mkTypeConstraintExpr(ITypeExpr *expr) {
	return new TypeConstraintExpr(expr);
}

ITypeConstraintIfElse *Context::mkTypeConstraintIfElse(
			ITypeExpr 		*cond,
			ITypeConstraint	*true_c,
			ITypeConstraint	*false_c) {
	return new TypeConstraintIfElse(cond, true_c, false_c);
}

ITypeConstraintImplies *Context::mkTypeConstraintImplies(
			ITypeExpr 		*cond,
			ITypeConstraint	*body) {
	return new TypeConstraintImplies(cond, body);
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

ITypeExprBin *Context::mkTypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs) {
	return new TypeExprBin(lhs, op, rhs);
}

ITypeExprFieldRef *Context::mkTypeExprFieldRef() {
	return new TypeExprFieldRef();
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

ITypeExprVal *Context::mkTypeExprVal(const IModelVal *v) {
	return new TypeExprVal(v);
}

ITypeFieldPhy *Context::mkTypeFieldPhy(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			IModelVal				*init) {
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

} /* namespace vsc */
