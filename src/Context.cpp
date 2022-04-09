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
#include "DataTypeStruct.h"
#include "ModelConstraintBlock.h"
#include "ModelConstraintExpr.h"
#include "ModelExprBin.h"
#include "ModelExprFieldRef.h"
#include "ModelExprVal.h"
#include "ModelFieldRoot.h"
#include "Randomizer.h"
#include "RandState.h"
#include "TaskSetUsedRand.h"
#include "TypeConstraintBlock.h"
#include "TypeConstraintExpr.h"
#include "TypeConstraintScope.h"
#include "TypeExprBin.h"
#include "TypeExprFieldRef.h"
#include "TypeExprVal.h"
#include "TypeField.h"

namespace vsc {

Context::Context() {
	// TODO Auto-generated constructor stub

}

Context::~Context() {
	// TODO Auto-generated destructor stub
}

ICompoundSolver *Context::mkCompoundSolver() {
	return new CompoundSolverDefault();
}

IModelConstraintBlock *Context::mkModelConstraintBlock(
			const std::string &name) {
	return new ModelConstraintBlock(name);
}

IModelConstraintExpr *Context::mkModelConstraintExpr(
			IModelExpr		*expr) {
	return new ModelConstraintExpr(expr);
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

IModelExprBin *Context::mkModelExprBin(
			IModelExpr		*lhs,
			BinOp			op,
			IModelExpr		*rhs) {
	return new ModelExprBin(lhs, op, rhs);
}

IModelExprFieldRef *Context::mkModelExprFieldRef(
			IModelField		*field) {
	return new ModelExprFieldRef(field);
}

IModelExprVal *Context::mkModelExprVal(IModelVal *v) {
	if (v) {
		return new ModelExprVal(v);
	} else {
		return new ModelExprVal();
	}
}

IModelField *Context::mkModelFieldRoot(
			IDataType 			*type,
			const std::string	&name) {
	return new ModelFieldRoot(type, name);
}

IRandomizer *Context::mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) {
	return new Randomizer(solver_factory, randstate);
}

IRandState *Context::mkRandState(uint32_t seed) {
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

ITypeConstraintScope *Context::mkTypeConstraintScope() {
	return new TypeConstraintScope();
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

ITypeExprVal *Context::mkTypeExprVal(const IModelVal *v) {
	return new TypeExprVal(v);
}

ITypeField *Context::mkTypeField(
			const std::string		&name,
			IDataType				*dtype,
			TypeFieldAttr			attr,
			IModelVal				*init) {
	return new TypeField(
			name,
			dtype,
			attr,
			init);
}

} /* namespace vsc */
