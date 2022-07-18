/*
 * ContextDelegator.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IContext.h"

namespace vsc {

class ContextDelegator : public virtual vsc::IContext {
public:

	ContextDelegator(IContext *ctxt) : m_ctxt(ctxt) { }

	virtual ~ContextDelegator() {
		if (m_ctxt) {
			delete m_ctxt;
		}
	}

	virtual IModelField *buildModelField(
			IDataTypeStruct			*dt,
			const std::string		&name) override {
		return m_ctxt->buildModelField(dt, name);
	}

	virtual ICompoundSolver *mkCompoundSolver() override {
		return m_ctxt->mkCompoundSolver();
	}

	virtual IDataTypeInt *findDataTypeInt(
			bool			is_signed,
			int32_t			width) override {
		return m_ctxt->findDataTypeInt(is_signed, width);
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

	virtual IDataTypeStruct *findDataTypeStruct(const std::string &name) override {
		return m_ctxt->findDataTypeStruct(name);
	}

	virtual bool addDataTypeStruct(IDataTypeStruct *t) override {
		return m_ctxt->addDataTypeStruct(t);
	}

	virtual IDataTypeStruct *mkDataTypeStruct(const std::string &name) override {
		return m_ctxt->mkDataTypeStruct(name);
	}

	virtual IModelConstraintBlock *mkModelConstraintBlock(
			const std::string &name) override {
		return m_ctxt->mkModelConstraintBlock(name);
	}

	virtual IModelConstraintExpr *mkModelConstraintExpr(
			IModelExpr		*expr) override {
		return m_ctxt->mkModelConstraintExpr(expr);
	}

	virtual IModelExprBin *mkModelExprBin(
			IModelExpr		*lhs,
			BinOp			op,
			IModelExpr		*rhs) override {
		return m_ctxt->mkModelExprBin(lhs, op, rhs);
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

	virtual IModelExprPartSelect *mkModelExprPartSelect(
			IModelExpr				*lhs,
			int32_t					lower,
			int32_t					upper) override {
		return m_ctxt->mkModelExprPartSelect(lhs, lower, upper);
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
			const std::string	&name) override {
		return m_ctxt->mkModelFieldRoot(type, name);
	}

	virtual IModelFieldType *mkModelFieldType(
			ITypeField			*type) override {
		return m_ctxt->mkModelFieldType(type);
	}

	virtual IModelVal *mkModelVal() override {
		return m_ctxt->mkModelVal();
	}

	virtual IRandomizer *mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) override {
		return m_ctxt->mkRandomizer(solver_factory, randstate);
	}

	virtual IRandState *mkRandState(uint32_t seed) override {
		return m_ctxt->mkRandState(seed);
	}

	virtual ITask *mkTask(TaskE id) override {
		return m_ctxt->mkTask(id);
	}

	virtual ITypeExprBin *mkTypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs) override {
		return m_ctxt->mkTypeExprBin(lhs, op, rhs);
	}

	virtual ITypeConstraintBlock *mkTypeConstraintBlock(const std::string &name) override {
		return m_ctxt->mkTypeConstraintBlock(name);
	}

	virtual ITypeConstraintExpr *mkTypeConstraintExpr(ITypeExpr *e) override {
		return m_ctxt->mkTypeConstraintExpr(e);
	}

	virtual ITypeConstraintScope *mkTypeConstraintScope() override {
		return m_ctxt->mkTypeConstraintScope();
	}

	virtual ITypeExprFieldRef *mkTypeExprFieldRef() override {
		return m_ctxt->mkTypeExprFieldRef();
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

	virtual ITypeExprVal *mkTypeExprVal(const IModelVal *v) override {
		return m_ctxt->mkTypeExprVal(v);
	}

	virtual ITypeFieldPhy *mkTypeFieldPhy(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			IModelVal				*init) override {
		return m_ctxt->mkTypeFieldPhy(name, dtype, own_dtype, attr, init);
	}

	virtual ITypeFieldRef *mkTypeFieldRef(
			const std::string		&name,
			IDataType				*dtype,
			TypeFieldAttr			attr) override {
		return m_ctxt->mkTypeFieldRef(name, dtype, attr);
	}

protected:
	IContext				*m_ctxt;

};



}
