/*
 * IContext.h
 *
 *  Created on: Jan 27, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ICompoundSolver.h"
#include "vsc/IDataTypeEnum.h"
#include "vsc/IDataTypeInt.h"
#include "vsc/IModelConstraintBlock.h"
#include "vsc/IModelConstraintExpr.h"
#include "vsc/IModelExpr.h"
#include "vsc/IModelExprBin.h"
#include "vsc/IModelExprFieldRef.h"
#include "vsc/IModelExprVal.h"
#include "vsc/IModelFieldRef.h"
#include "vsc/IModelFieldRoot.h"
#include "vsc/IModelFieldType.h"
#include "vsc/IRandomizer.h"
#include "vsc/IRandState.h"
#include "vsc/ISolverFactory.h"
#include "vsc/ITask.h"
#include "vsc/ITypeConstraintBlock.h"
#include "vsc/ITypeConstraintExpr.h"
#include "vsc/ITypeConstraintScope.h"
#include "vsc/ITypeExprBin.h"
#include "vsc/ITypeExprFieldRef.h"
#include "vsc/ITypeExprVal.h"
#include "vsc/ITypeFieldPhy.h"
#include "vsc/ITypeFieldRef.h"

namespace vsc {

enum class TaskE {
	SetUsedRand
};

class IContext {
public:

	virtual ~IContext() { }

	virtual IModelField *buildModelField(
			IDataTypeStruct			*dt,
			const std::string		&name) = 0;

	virtual ICompoundSolver *mkCompoundSolver() = 0;

	virtual IDataTypeEnum *findDataTypeEnum(const std::string &name) = 0;

	virtual IDataTypeEnum *mkDataTypeEnum(
			const std::string 	&name,
			bool				is_signed) = 0;

	virtual bool addDataTypeEnum(IDataTypeEnum *e) = 0;

	virtual IDataTypeInt *findDataTypeInt(
			bool			is_signed,
			int32_t			width) = 0;

	/**
	 * Returns a new datatype. The expectation is that
	 * it will be subsequently added to the context
	 */
	virtual IDataTypeInt *mkDataTypeInt(
			bool			is_signed,
			int32_t			width) = 0;

	virtual bool addDataTypeInt(IDataTypeInt *t) = 0;

	virtual IDataTypeStruct *findDataTypeStruct(const std::string &name) = 0;

	virtual IDataTypeStruct *mkDataTypeStruct(const std::string &name) = 0;

	virtual bool addDataTypeStruct(IDataTypeStruct *t) = 0;

	virtual IModelConstraintBlock *mkModelConstraintBlock(
			const std::string &name) = 0;

	virtual IModelConstraintExpr *mkModelConstraintExpr(
			IModelExpr		*expr) = 0;

	virtual IModelExprBin *mkModelExprBin(
			IModelExpr		*lhs,
			BinOp			op,
			IModelExpr		*rhs) = 0;

	virtual IModelExprFieldRef *mkModelExprFieldRef(
			IModelField		*field) = 0;

	virtual IModelExprVal *mkModelExprVal(IModelVal *) = 0;

	virtual IModelFieldRef *mkModelFieldRefRoot(
			IDataType			*type,
			const std::string	&name) = 0;

	virtual IModelFieldRef *mkModelFieldRefType(
			ITypeField			*type) = 0;

	virtual IModelFieldRoot *mkModelFieldRoot(
			IDataType 			*type,
			const std::string	&name) = 0;

	virtual IModelFieldType *mkModelFieldType(
			ITypeField			*type) = 0;

	virtual IModelVal *mkModelVal() = 0;

	virtual IRandomizer *mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) = 0;

	virtual IRandState *mkRandState(uint32_t seed) = 0;

	virtual ITask *mkTask(TaskE id) = 0;

	virtual ITypeExprBin *mkTypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs) = 0;

	virtual ITypeConstraintBlock *mkTypeConstraintBlock(const std::string &name) = 0;

	virtual ITypeConstraintExpr *mkTypeConstraintExpr(ITypeExpr *) = 0;

	virtual ITypeConstraintScope *mkTypeConstraintScope() = 0;

	virtual ITypeExprFieldRef *mkTypeExprFieldRef() = 0;

	virtual ITypeExprVal *mkTypeExprVal(const IModelVal *) = 0;

	virtual ITypeFieldPhy *mkTypeFieldPhy(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			IModelVal				*init) = 0;

	virtual ITypeFieldRef *mkTypeFieldRef(
			const std::string		&name,
			IDataType				*dtype,
			TypeFieldAttr			attr) = 0;

};

}
