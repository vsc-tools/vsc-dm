/*
 * IContext.h
 *
 *  Created on: Jan 27, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IDataTypeInt.h"
#include "vsc/IModelConstraintExpr.h"
#include "vsc/IModelExpr.h"
#include "vsc/IModelExprBin.h"
#include "vsc/IModelExprFieldRef.h"
#include "vsc/IRandomizer.h"
#include "vsc/IRandState.h"
#include "vsc/ISolverFactory.h"

namespace vsc {

class IContext {
public:

	virtual ~IContext() { }



	/**
	 * Returns a new datatype. The returned handle
	 * is owned by the context, and must not be deleted
	 */
	virtual IDataTypeInt *mkDataTypeInt(
			bool			is_signed,
			int32_t			width) = 0;

	virtual IModelConstraintExpr *mkModelConstraintExpr(
			IModelExpr		*expr) = 0;

	virtual IModelExprBin *mkModelExprBin(
			IModelExpr		*lhs,
			BinOp			op,
			IModelExpr		*rhs) = 0;

	virtual IModelExprFieldRef *mkModelExprFieldRef(
			IModelField		*field) = 0;

	virtual IModelField *mkModelFieldRoot(
			IDataType 			*type,
			const std::string	&name) = 0;

	virtual IRandomizer *mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) = 0;

	virtual IRandState *mkRandState(uint32_t seed) = 0;

};

}
