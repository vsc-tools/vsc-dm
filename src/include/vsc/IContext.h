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
#include "vsc/IDataTypeStruct.h"
#include "vsc/IDataTypeVec.h"
#include "vsc/IDebugMgr.h"
#include "vsc/IModelConstraintBlock.h"
#include "vsc/IModelConstraintExpr.h"
#include "vsc/IModelConstraintForeach.h"
#include "vsc/IModelConstraintIfElse.h"
#include "vsc/IModelConstraintImplies.h"
#include "vsc/IModelConstraintScope.h"
#include "vsc/IModelConstraintSoft.h"
#include "vsc/IModelConstraintSubst.h"
#include "vsc/IModelConstraintUnique.h"
#include "vsc/IModelCoverBin.h"
#include "vsc/IModelCoverBinCollection.h"
#include "vsc/IModelCoverCross.h"
#include "vsc/IModelCovergroup.h"
#include "vsc/IModelCoverpoint.h"
#include "vsc/IModelCoverpointTarget.h"
#include "vsc/IModelExpr.h"
#include "vsc/IModelExprBin.h"
#include "vsc/IModelExprCond.h"
#include "vsc/IModelExprFieldRef.h"
#include "vsc/IModelExprIn.h"
#include "vsc/IModelExprIndexedFieldRef.h"
#include "vsc/IModelExprPartSelect.h"
#include "vsc/IModelExprRange.h"
#include "vsc/IModelExprRangelist.h"
#include "vsc/IModelExprRef.h"
#include "vsc/IModelExprUnary.h"
#include "vsc/IModelExprVal.h"
#include "vsc/IModelFieldRef.h"
#include "vsc/IModelFieldRoot.h"
#include "vsc/IModelFieldVecRoot.h"
#include "vsc/IModelFieldType.h"
#include "vsc/IModelVal.h"
#include "vsc/IModelValOp.h"
#include "vsc/IRandomizer.h"
#include "vsc/IRandState.h"
#include "vsc/IRefSelector.h"
#include "vsc/ISolverFactory.h"
#include "vsc/ITask.h"
#include "vsc/ITypeConstraintBlock.h"
#include "vsc/ITypeConstraintExpr.h"
#include "vsc/ITypeConstraintIfElse.h"
#include "vsc/ITypeConstraintImplies.h"
#include "vsc/ITypeConstraintScope.h"
#include "vsc/ITypeConstraintSoft.h"
#include "vsc/ITypeConstraintUnique.h"
#include "vsc/ITypeExprBin.h"
#include "vsc/ITypeExprFieldRef.h"
#include "vsc/ITypeExprRange.h"
#include "vsc/ITypeExprRangelist.h"
#include "vsc/ITypeExprVal.h"
#include "vsc/ITypeFieldPhy.h"
#include "vsc/ITypeFieldRef.h"
#include "vsc/ITypeFieldVec.h"

namespace vsc {

enum class TaskE {
	SetUsedRand
};

class IContext;
using IContextUP=std::unique_ptr<IContext>;
class IContext {
public:

	virtual ~IContext() { }

	virtual IModelField *buildModelField(
			IDataTypeStruct			*dt,
			const std::string		&name) = 0;

	virtual IDebugMgr *getDebugMgr() = 0;

	virtual IModelValOp *getModelValOp() = 0;

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

	virtual IDataTypeVec *findDataTypeVec(IDataType *t) = 0;

	virtual IDataTypeVec *mkDataTypeVec(IDataType *t) = 0;

	virtual bool *addDataTypeVec(IDataTypeVec *t) = 0;

	virtual IModelConstraintBlock *mkModelConstraintBlock(
			const std::string &name) = 0;

	virtual IModelConstraintExpr *mkModelConstraintExpr(
			IModelExpr		*expr) = 0;

	virtual IModelConstraintForeach *mkModelConstraintForeach(
			IModelExpr			*target,
			const std::string	&index_it_name) = 0;

	virtual IModelConstraintIfElse *mkModelConstraintIfElse(
			IModelExpr			*cond,
			IModelConstraint	*true_c,
			IModelConstraint	*false_c) = 0;

	virtual IModelConstraintImplies *mkModelConstraintImplies(
			IModelExpr			*cond,
			IModelConstraint	*body) = 0;

	virtual IModelConstraintRef *mkModelConstraintRef(
			IModelConstraint	*target) = 0;

	virtual IModelConstraintScope *mkModelConstraintScope() = 0;

	virtual IModelConstraintSoft *mkModelConstraintSoft(
		IModelConstraintExpr	*c) = 0;

	virtual IModelConstraintSubst *mkModelConstraintSubst(
		IModelConstraint		*c) = 0;

	virtual IModelConstraintUnique *mkModelConstraintUnique(
		const std::vector<IModelExpr *>		&exprs) = 0;

	virtual IModelCoverBinCollection *mkModelCoverBinCollection(
		ModelCoverBinType			type) = 0;

	virtual IModelCoverBin *mkModelCoverBinSingleRange(
		const std::string			&name,
		ModelCoverBinType			type,
		bool						is_signed,
		IModelVal					*lower,
		IModelVal					*upper) = 0;

	virtual IModelCoverBin *mkModelCoverBinSingleVal(
		const std::string			&name,
		ModelCoverBinType			type,
		IModelVal					*value) = 0;

	virtual IModelCoverCross *mkModelCoverCross(
		const std::string			&name,
		IModelCoverpointIff			*iff) = 0;

	virtual IModelCovergroup *mkModelCovergroup(
		const std::string			&name) = 0;

	virtual IModelCoverpoint *mkModelCoverpoint(
		const std::string			&name,
		IModelCoverpointTarget		*target,
		IModelCoverpointIff			*iff) = 0;

	virtual IModelCoverpointTarget *mkModelCoverpointTargetExpr(
		IModelExpr					*expr,
		int32_t						width) = 0;

	virtual IModelExprBin *mkModelExprBin(
			IModelExpr		*lhs,
			BinOp			op,
			IModelExpr		*rhs) = 0;
			
	virtual IModelExprCond *mkModelExprCond(
			IModelExpr		*cond,
			IModelExpr		*true_e,
			IModelExpr		*false_e) = 0;

	virtual IModelExprFieldRef *mkModelExprFieldRef(
			IModelField		*field) = 0;

	virtual IModelExprIn *mkModelExprIn(
			IModelExpr				*lhs,
			IModelExprRangelist		*rnglist) = 0;

	virtual IModelExprIndexedFieldRef *mkModelExprIndexedFieldRef() = 0;

	virtual IModelExprPartSelect *mkModelExprPartSelect(
			IModelExpr				*lhs,
			int32_t					lower,
			int32_t					upper) = 0;

	virtual IModelExprRange *mkModelExprRange(
			bool			is_single,
			IModelExpr		*lower,
			IModelExpr		*upper) = 0;

	virtual IModelExprRangelist *mkModelExprRangelist() = 0;

	virtual IModelExprRef *mkModelExprRef(IModelExpr *target) = 0;

	virtual IModelExprUnary *mkModelExprUnary(
		UnaryOp		op,
		IModelExpr	*e) = 0;

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

	virtual IModelFieldVec *mkModelFieldVecRoot(
			IDataType			*type,
			const std::string	&name) = 0;

	virtual IModelVal *mkModelVal() = 0;

	virtual IRandomizer *mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) = 0;

	virtual IRandState *mkRandState(const std::string &seed) = 0;

	virtual IRefSelector *mkRefSelector(
			IModelFieldRef						*ref,
			const std::vector<IModelField *>	&candidates) = 0;

	virtual ITask *mkTask(TaskE id) = 0;

	virtual ITypeExprBin *mkTypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs) = 0;

	virtual ITypeConstraintBlock *mkTypeConstraintBlock(const std::string &name) = 0;

	virtual ITypeConstraintExpr *mkTypeConstraintExpr(ITypeExpr *) = 0;

	virtual ITypeConstraintIfElse *mkTypeConstraintIfElse(
			ITypeExpr 		*cond,
			ITypeConstraint	*true_c,
			ITypeConstraint	*false_c) = 0;

	virtual ITypeConstraintImplies *mkTypeConstraintImplies(
			ITypeExpr		*cond,
			ITypeConstraint	*body) = 0;

	virtual ITypeConstraintScope *mkTypeConstraintScope() = 0;

	virtual ITypeConstraintSoft *mkTypeConstraintSoft(
			ITypeConstraintExpr	*c) = 0;

	virtual ITypeConstraintUnique *mkTypeConstraintUnique(
			const std::vector<ITypeExpr *>		&exprs) = 0;

	virtual ITypeExprFieldRef *mkTypeExprFieldRef() = 0;

	virtual ITypeExprRange *mkTypeExprRange(
			bool				is_single,
			ITypeExpr			*lower,
			ITypeExpr			*upper) = 0;

	virtual ITypeExprRangelist *mkTypeExprRangelist() = 0;

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

	virtual ITypeFieldVec *mkTypeFieldVec(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			IModelVal				*init_sz) = 0;

};

}
