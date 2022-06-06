/*
 * Context.h
 *
 *  Created on: Sep 8, 2021
 *      Author: mballance
 */

#pragma once
#include <unordered_map>
#include "vsc/IContext.h"
#include "DataTypeInt.h"
#include "DataTypeStruct.h"

namespace vsc {

class Context : public IContext {
public:
	Context();

	virtual ~Context();

	virtual IModelField *buildModelField(
			IDataTypeStruct			*dt,
			const std::string		&name) override;

	virtual ICompoundSolver *mkCompoundSolver() override;

	virtual IDataTypeInt *findDataTypeInt(
			bool			is_signed,
			int32_t			width) override;

	virtual IDataTypeInt *mkDataTypeInt(
			bool			is_signed,
			int32_t			width) override;

	virtual bool addDataTypeInt(IDataTypeInt *t) override;

	virtual IDataTypeStruct *findDataTypeStruct(
			const std::string &name) override;

	virtual IDataTypeStruct *mkDataTypeStruct(
			const std::string &name) override;

	virtual bool addDataTypeStruct(
			IDataTypeStruct *t) override;

	virtual IModelConstraintBlock *mkModelConstraintBlock(
			const std::string &name) override;

	virtual IModelConstraintExpr *mkModelConstraintExpr(
			IModelExpr		*expr) override;

	virtual IModelExprBin *mkModelExprBin(
			IModelExpr		*lhs,
			BinOp			op,
			IModelExpr		*rhs) override;

	virtual IModelExprFieldRef *mkModelExprFieldRef(
			IModelField		*field) override;

	virtual IModelExprVal *mkModelExprVal(IModelVal *) override;

	virtual IModelFieldRef *mkModelFieldRefRoot(
			IDataType 			*type,
			const std::string	&name) override;

	virtual IModelFieldRef *mkModelFieldRefType(
			ITypeField			*type) override;

	virtual IModelFieldRoot *mkModelFieldRoot(
			IDataType 			*type,
			const std::string	&name) override;

	virtual IModelFieldType *mkModelFieldType(
			ITypeField			*type
			) override;

	virtual IModelVal *mkModelVal() override;

	virtual IRandomizer *mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) override;

	virtual IRandState *mkRandState(uint32_t seed) override;

	virtual ITask *mkTask(TaskE id) override;

	virtual ITypeConstraintBlock *mkTypeConstraintBlock(const std::string &name) override;

	virtual ITypeConstraintExpr *mkTypeConstraintExpr(ITypeExpr *) override;

	virtual ITypeConstraintScope *mkTypeConstraintScope() override;

	virtual ITypeExprBin *mkTypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs) override;

	virtual ITypeExprFieldRef *mkTypeExprFieldRef() override;

	virtual ITypeExprVal *mkTypeExprVal(const IModelVal *) override;

	virtual ITypeFieldPhy *mkTypeFieldPhy(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			IModelVal				*init) override;

	virtual ITypeFieldRef *mkTypeFieldRef(
			const std::string		&name,
			IDataType				*dtype,
			TypeFieldAttr			attr) override;


private:

	std::unordered_map<std::string,IDataTypeStruct *>		m_struct_type_m;
	std::vector<IDataTypeStructUP>							m_struct_type_l;

	std::unordered_map<int32_t, IDataTypeInt*>				m_uint_type_m;
	std::vector<IDataTypeIntUP>								m_uint_type_l;

	std::unordered_map<int32_t, IDataTypeInt*>				m_sint_type_m;
	std::vector<IDataTypeIntUP>								m_sint_type_l;

};

} /* namespace vsc */

