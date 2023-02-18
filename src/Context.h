/*
 * Context.h
 *
 *  Created on: Sep 8, 2021
 *      Author: mballance
 */

#pragma once
#include <unordered_map>
#include "dmgr/IDebugMgr.h"
#include "vsc/dm/IContext.h"
#include "DataTypeInt.h"
#include "DataTypeVec.h"
#include "DataTypeStruct.h"
#include "ModelValOp.h"

namespace vsc {
namespace dm {

class Context : public IContext {
public:
	Context(dmgr::IDebugMgr *dm);

	virtual ~Context();

	virtual IModelField *buildModelField(
			IDataTypeStruct			*dt,
			const std::string		&name) override;

	virtual dmgr::IDebugMgr *getDebugMgr() override;

	virtual IModelValOp *getModelValOp() override { return &m_model_val_op; }

	virtual IDataTypeEnum *findDataTypeEnum(const std::string &name) override;

	virtual IDataTypeEnum *mkDataTypeEnum(
			const std::string 	&name,
			bool				is_signed) override;

	virtual bool addDataTypeEnum(IDataTypeEnum *e) override;

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

	virtual IDataTypeVec *findDataTypeVec(IDataType *t) override;

	virtual IDataTypeVec *mkDataTypeVec(IDataType *t) override;

	virtual bool *addDataTypeVec(IDataTypeVec *t) override;

	virtual IModelConstraintBlock *mkModelConstraintBlock(
			const std::string &name) override;

	virtual IModelConstraintExpr *mkModelConstraintExpr(
			IModelExpr		*expr) override;

	virtual IModelConstraintIfElse *mkModelConstraintIfElse(
			IModelExpr			*cond,
			IModelConstraint	*true_c,
			IModelConstraint	*false_c) override;

	virtual IModelConstraintImplies *mkModelConstraintImplies(
			IModelExpr			*cond,
			IModelConstraint	*body,
            bool                cond_owned=true,
            bool                body_owned=true) override;

	virtual IModelConstraintScope *mkModelConstraintScope() override;

	virtual IModelConstraintSoft *mkModelConstraintSoft(
			IModelConstraintExpr	*c) override;

	virtual IModelConstraintSubst *mkModelConstraintSubst(
			IModelConstraint		*c) override;

	virtual IModelConstraintUnique *mkModelConstraintUnique(
			const std::vector<IModelExpr *>		&exprs) override;

	virtual IModelExprBin *mkModelExprBin(
			IModelExpr		*lhs,
			BinOp			op,
			IModelExpr		*rhs) override;

	virtual IModelExprCond *mkModelExprCond(
			IModelExpr		*cond,
			IModelExpr		*true_e,
			IModelExpr		*false_e) override;

	virtual IModelExprFieldRef *mkModelExprFieldRef(
			IModelField		*field) override;

	virtual IModelExprPartSelect *mkModelExprPartSelect(
			IModelExpr				*lhs,
			int32_t					lower,
			int32_t					upper) override;

	virtual IModelExprRange *mkModelExprRange(
			bool			is_single,
			IModelExpr		*lower,
			IModelExpr		*upper) override;

	virtual IModelExprRangelist *mkModelExprRangelist() override;

	virtual IModelExprRef *mkModelExprRef(IModelExpr *target) override;

	virtual IModelExprUnary *mkModelExprUnary(
		UnaryOp		op,
		IModelExpr	*e) override;

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

	virtual IModelFieldVec *mkModelFieldVecRoot(
			IDataType			*type,
			const std::string	&name) override;

	virtual IModelVal *mkModelVal() override;

	virtual IModelVal *mkModelValS(
            int64_t             val,
            int32_t             bits) override;

	virtual IModelVal *mkModelValU(
            uint64_t            val,
            int32_t             bits) override;

	virtual IRefSelector *mkRefSelector(
			IModelFieldRef						*ref,
			const std::vector<IModelField *>	&candidates) override;

	virtual ITask *mkTask(TaskE id) override;

	virtual ITypeConstraintBlock *mkTypeConstraintBlock(const std::string &name) override;

	virtual ITypeConstraintExpr *mkTypeConstraintExpr(
            ITypeExpr           *expr,
            bool                owned) override;

	virtual IModelConstraintForeach *mkModelConstraintForeach(
			IModelExpr			*target,
			const std::string	&index_it_name) override;

	virtual ITypeConstraintIfElse *mkTypeConstraintIfElse(
			ITypeExpr 		*cond,
			ITypeConstraint	*true_c,
			ITypeConstraint	*false_c,
            bool            cond_owned,
            bool            true_owned,
            bool            false_owned) override;

	virtual ITypeConstraintImplies *mkTypeConstraintImplies(
			ITypeExpr 		*cond,
			ITypeConstraint	*body,
            bool            cond_owned,
            bool            body_owned) override;
			
	virtual IModelConstraintRef *mkModelConstraintRef(
			IModelConstraint	*target) override;

	virtual ITypeConstraintScope *mkTypeConstraintScope() override;

	virtual ITypeConstraintSoft *mkTypeConstraintSoft(
			ITypeConstraintExpr		*c) override;

	virtual ITypeConstraintUnique *mkTypeConstraintUnique(
			const std::vector<ITypeExpr *>		&exprs) override;

	virtual IModelCoverBinCollection *mkModelCoverBinCollection(
		ModelCoverBinType			type) override;

	virtual IModelCoverBin *mkModelCoverBinSingleRange(
		const std::string			&name,
		ModelCoverBinType			type,
		bool						is_signed,
		IModelVal					*lower,
		IModelVal					*upper) override;

	virtual IModelCoverBin *mkModelCoverBinSingleVal(
		const std::string			&name,
		ModelCoverBinType			type,
		IModelVal					*value) override;

	virtual IModelCoverCross *mkModelCoverCross(
		const std::string			&name,
		IModelCoverpointIff			*iff) override;

	virtual IModelCovergroup *mkModelCovergroup(
		const std::string			&name) override;

	virtual IModelCoverpoint *mkModelCoverpoint(
		const std::string			&name,
		IModelCoverpointTarget		*target,
		IModelCoverpointIff			*iff) override;

	virtual IModelCoverpointTarget *mkModelCoverpointTargetExpr(
		IModelExpr					*expr,
		int32_t						width) override;

	virtual ITypeExprBin *mkTypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs,
            bool            lhs_owned,
            bool            rhs_owned) override;

	virtual ITypeExprFieldRef *mkTypeExprFieldRef(
        ITypeExprFieldRef::RootRefKind      kind,
        int32_t                             offset) override;

	virtual ITypeExprFieldRef *mkTypeExprFieldRef(
        ITypeExprFieldRef::RootRefKind          kind,
        int32_t                                 offset,
        const std::initializer_list<int32_t>    path) override;

	virtual IModelExprIn *mkModelExprIn(

			IModelExpr				*lhs,
			IModelExprRangelist		*rnglist) override;

	virtual IModelExprIndexedFieldRef *mkModelExprIndexedFieldRef() override;

	virtual ITypeExprRange *mkTypeExprRange(
			bool				is_single,
			ITypeExpr			*lower,
			ITypeExpr			*upper) override;

	virtual ITypeExprRangelist *mkTypeExprRangelist() override;

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

	virtual ITypeFieldVec *mkTypeFieldVec(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			IModelVal				*init_sz) override;


private:
    dmgr::IDebugMgr                                         *m_dbg_mgr;
	ModelValOp												m_model_val_op;
	std::unordered_map<std::string,IDataTypeEnum *>			m_enum_type_m;
	std::vector<IDataTypeEnumUP>							m_enum_type_l;

	std::unordered_map<IDataType *, IDataTypeVec *>			m_vec_type_m;
	std::vector<IDataTypeVecUP>								m_vec_type_l;

	std::unordered_map<std::string,IDataTypeStruct *>		m_struct_type_m;
	std::vector<IDataTypeStructUP>							m_struct_type_l;

	std::unordered_map<int32_t, IDataTypeInt*>				m_uint_type_m;
	std::vector<IDataTypeIntUP>								m_uint_type_l;

	std::unordered_map<int32_t, IDataTypeInt*>				m_sint_type_m;
	std::vector<IDataTypeIntUP>								m_sint_type_l;

};

}
} /* namespace vsc */

