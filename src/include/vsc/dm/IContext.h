/*
 * IContext.h
 *
 *  Created on: Jan 27, 2022
 *      Author: mballance
 */

#pragma once
#include "dmgr/IDebugMgr.h"
#include "vsc/dm/IDataTypeArray.h"
#include "vsc/dm/IDataTypeBool.h"
#include "vsc/dm/IDataTypeEnum.h"
#include "vsc/dm/IDataTypeList.h"
#include "vsc/dm/IDataTypeInt.h"
#include "vsc/dm/IDataTypeRef.h"
#include "vsc/dm/IDataTypeString.h"
#include "vsc/dm/IDataTypeStruct.h"
#include "vsc/dm/IDataTypeVec.h"
#include "vsc/dm/IDataTypeWrapper.h"
#include "vsc/dm/IModelConstraintBlock.h"
#include "vsc/dm/IModelConstraintExpr.h"
#include "vsc/dm/IModelConstraintForeach.h"
#include "vsc/dm/IModelConstraintIfElse.h"
#include "vsc/dm/IModelConstraintImplies.h"
#include "vsc/dm/IModelConstraintScope.h"
#include "vsc/dm/IModelConstraintSoft.h"
#include "vsc/dm/IModelConstraintSubst.h"
#include "vsc/dm/IModelConstraintUnique.h"
#include "vsc/dm/IModelCoverBin.h"
#include "vsc/dm/IModelCoverBinCollection.h"
#include "vsc/dm/IModelCoverCross.h"
#include "vsc/dm/IModelCovergroup.h"
#include "vsc/dm/IModelCoverpoint.h"
#include "vsc/dm/IModelCoverpointTarget.h"
#include "vsc/dm/IModelExpr.h"
#include "vsc/dm/IModelExprBin.h"
#include "vsc/dm/IModelExprCond.h"
#include "vsc/dm/IModelExprFieldRef.h"
#include "vsc/dm/IModelExprIn.h"
#include "vsc/dm/IModelExprIndexedFieldRef.h"
#include "vsc/dm/IModelExprPartSelect.h"
#include "vsc/dm/IModelExprRange.h"
#include "vsc/dm/IModelExprRangelist.h"
#include "vsc/dm/IModelExprRef.h"
#include "vsc/dm/IModelExprUnary.h"
#include "vsc/dm/IModelExprVal.h"
#include "vsc/dm/IModelFieldRef.h"
#include "vsc/dm/IModelFieldRoot.h"
#include "vsc/dm/IModelFieldVecRoot.h"
#include "vsc/dm/IModelFieldType.h"
#include "vsc/dm/IModelVal.h"
#include "vsc/dm/IModelValOp.h"
#include "vsc/dm/IRefSelector.h"
#include "vsc/dm/ITask.h"
#include "vsc/dm/ITypeConstraintBlock.h"
#include "vsc/dm/ITypeConstraintExpr.h"
#include "vsc/dm/ITypeConstraintForeach.h"
#include "vsc/dm/ITypeConstraintIfElse.h"
#include "vsc/dm/ITypeConstraintImplies.h"
#include "vsc/dm/ITypeConstraintScope.h"
#include "vsc/dm/ITypeConstraintSoft.h"
#include "vsc/dm/ITypeConstraintUnique.h"
#include "vsc/dm/ITypeExprArrayLiteral.h"
#include "vsc/dm/ITypeExprArrIndex.h"
#include "vsc/dm/ITypeExprBin.h"
#include "vsc/dm/ITypeExprEnumRef.h"
#include "vsc/dm/ITypeExprFieldRef.h"
#include "vsc/dm/ITypeExprRange.h"
#include "vsc/dm/ITypeExprRangelist.h"
#include "vsc/dm/ITypeExprRef.h"
#include "vsc/dm/ITypeExprRefBottomUp.h"
#include "vsc/dm/ITypeExprRefInline.h"
#include "vsc/dm/ITypeExprRefPath.h"
#include "vsc/dm/ITypeExprRefTopDown.h"
#include "vsc/dm/ITypeExprStructLiteral.h"
#include "vsc/dm/ITypeExprSubField.h"
#include "vsc/dm/ITypeExprUnary.h"
#include "vsc/dm/ITypeExprVal.h"
#include "vsc/dm/ITypeFieldPhy.h"
#include "vsc/dm/ITypeFieldRef.h"
#include "vsc/dm/ITypeFieldVec.h"
#include "vsc/dm/IValAlloc.h"
#include "vsc/dm/Val.h"
#include "vsc/dm/impl/ValRef.h"
#include "vsc/dm/impl/ValRefArr.h"
#include "vsc/dm/impl/ValRefBool.h"
#include "vsc/dm/impl/ValRefInt.h"
#include "vsc/dm/impl/ValRefStr.h"
#include "vsc/dm/impl/ValRefStruct.h"

namespace vsc {
namespace dm {

enum class TaskE {
	SetUsedRand
};

enum class DataTypeCoreE {
    Bool,
    Ptr,
    String
};

class IContext;
using IContextUP=UP<IContext>;
class IContext : public virtual IValAlloc {
public:

	virtual ~IContext() { }

	virtual IModelField *buildModelField(
			IDataTypeStruct			*dt,
			const std::string		&name) = 0;

	virtual dmgr::IDebugMgr *getDebugMgr() = 0;

	virtual IModelValOp *getModelValOp() = 0;

#ifdef UNDEFINED
	virtual ICompoundSolver *mkCompoundSolver() = 0;
#endif

    virtual IDataType *getDataTypeCore(DataTypeCoreE t) = 0;

    virtual IDataTypeArray *findDataTypeArray(
        IDataType               *type,
        uint32_t                size,
        bool                    create=true) = 0;

    virtual IDataTypeArray *mkDataTypeArray(
        IDataType               *type,
        bool                    owned,
        uint32_t                size) = 0;

    virtual bool addDataTypeArray(IDataTypeArray *t) = 0;

	virtual IDataTypeEnum *findDataTypeEnum(const std::string &name) = 0;

	virtual IDataTypeEnum *mkDataTypeEnum(
			const std::string 	&name,
			bool				is_signed) = 0;

	virtual bool addDataTypeEnum(IDataTypeEnum *e) = 0;


	virtual IDataTypeInt *findDataTypeInt(
			bool			is_signed,
			int32_t			width,
            bool            create=true) = 0;

	/**
	 * Returns a new datatype. The expectation is that
	 * it will be subsequently added to the context
	 */
	virtual IDataTypeInt *mkDataTypeInt(
			bool			is_signed,
			int32_t			width) = 0;

	virtual bool addDataTypeInt(IDataTypeInt *t) = 0;

    virtual IDataTypeList *findDataTypeList(
        IDataType               *elem_t,
        bool                    create=true) = 0;

	virtual IDataTypeStruct *findDataTypeStruct(const std::string &name) = 0;

	virtual IDataTypeStruct *mkDataTypeStruct(const std::string &name) = 0;

	virtual bool addDataTypeStruct(IDataTypeStruct *t) = 0;

    virtual const std::vector<IDataTypeStructUP> &getDataTypeStructs() const = 0;

	virtual IDataTypeVec *findDataTypeVec(IDataType *t) = 0;

	virtual IDataTypeVec *mkDataTypeVec(IDataType *t) = 0;

	virtual bool addDataTypeVec(IDataTypeVec *t) = 0;

	virtual IDataTypeWrapper *findDataTypeWrapper(
        IDataType       *type_phy,
        IDataType       *type_virt,
        bool            create=true) = 0;

	virtual IDataTypeWrapper *mkDataTypeWrapper(
        IDataType       *type_phy,
        IDataType       *type_virt) = 0;

    virtual bool addDataTypeWrapper(IDataTypeWrapper *t) = 0;

    virtual ValRefInt evalBinOpInt(
        const vsc::dm::ValRefInt        &lhs,
        BinOp                           op,
        const vsc::dm::ValRefInt        &rhs) = 0;

    virtual ValRef evalBinOpStr(
        const vsc::dm::ValRefStr        &lhs,
        BinOp                           op,
        const vsc::dm::ValRefStr        &rhs) = 0;

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
			IModelConstraint	*body,
            bool                cond_owned=true,
            bool                body_owned=true) = 0;

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
			const std::string	&name,
            const ValRef        &val) = 0;

	virtual IModelFieldType *mkModelFieldType(
			ITypeField			*type,
            const ValRef        &val) = 0;

	virtual IModelFieldVec *mkModelFieldVecRoot(
			IDataType			*type,
			const std::string	&name) = 0;

	virtual IModelVal *mkModelVal() = 0;

	virtual IModelVal *mkModelValS(
            int64_t             val,
            int32_t             bits) = 0;

	virtual IModelVal *mkModelValU(
            uint64_t            val,
            int32_t             bits) = 0;

#ifdef UNDEFINED
	virtual IRandomizer *mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) = 0;

	virtual IRandState *mkRandState(const std::string &seed) = 0;
#endif

	virtual IRefSelector *mkRefSelector(
			IModelFieldRef						*ref,
			const std::vector<IModelField *>	&candidates) = 0;

	virtual ITask *mkTask(TaskE id) = 0;

    virtual ITypeExprArrayLiteral *mkTypeExprArrayLiteral(
            IDataTypeArray                  *arr_t,
            bool                            arr_t_owned,
            const std::vector<ITypeExpr *>  &vals) = 0;

    virtual ITypeExprArrIndex *mkTypeExprArrIndex(
            ITypeExpr       *root,
            bool            root_owned,
            ITypeExpr       *index,
            bool            index_owned) = 0;

	virtual ITypeExprBin *mkTypeExprBin(
			ITypeExpr		*lhs,
			BinOp			op,
			ITypeExpr		*rhs,
            bool            lhs_owned=true,
            bool            rhs_owned=true) = 0;

    virtual ITypeExprEnumRef *mkTypeExprEnumRef(
        IDataTypeEnum       *enum_t,
        int32_t             enum_id) = 0;

	virtual ITypeExprRef *mkTypeExprRef(
            ITypeExpr       *target,
            bool            owned) = 0;

	virtual ITypeExprRefInline *mkTypeExprRefInline() = 0;

	virtual ITypeExprRefBottomUp *mkTypeExprRefBottomUp(
            int32_t         scope_offset,
            int32_t         field_index) = 0;

	virtual ITypeExprRefPath *mkTypeExprRefPath(
        ITypeExpr       			*root,
        bool            			owned,
		const std::vector<int32_t>	&path) = 0;

	virtual ITypeExprRefTopDown *mkTypeExprRefTopDown() = 0;

    virtual ITypeExprStructLiteral *mkTypeExprStructLiteral(
            IDataTypeStruct                             *type,
            bool                                        owned,
            const std::vector<vsc::dm::ITypeExpr *>     &elems) = 0;

    virtual ITypeExprSubField *mkTypeExprSubField(
            ITypeExpr       *root,
            bool            owned,
            int32_t         index) = 0;

	virtual ITypeConstraintBlock *mkTypeConstraintBlock(const std::string &name) = 0;

	virtual ITypeConstraintExpr *mkTypeConstraintExpr(
            ITypeExpr       *expr,
            bool            owned=true) = 0;

    virtual ITypeConstraintForeach *mkTypeConstraintForeach(
            ITypeExpr           *target,
            bool                target_owned,
            const std::string   &iter_name,
            ITypeConstraint     *body,
            bool                body_owned) = 0;

	virtual ITypeConstraintIfElse *mkTypeConstraintIfElse(
			ITypeExpr 		*cond,
			ITypeConstraint	*true_c,
			ITypeConstraint	*false_c,
            bool            cond_owned=true,
            bool            true_owned=true,
            bool            false_owned=true) = 0;

	virtual ITypeConstraintImplies *mkTypeConstraintImplies(
			ITypeExpr		*cond,
			ITypeConstraint	*body,
            bool            cond_owned=true,
            bool            body_owned=true) = 0;

	virtual ITypeConstraintScope *mkTypeConstraintScope() = 0;

	virtual ITypeConstraintSoft *mkTypeConstraintSoft(
			ITypeConstraintExpr	*c) = 0;

	virtual ITypeConstraintUnique *mkTypeConstraintUnique(
			const std::vector<ITypeExpr *>		&exprs) = 0;

	virtual ITypeExprFieldRef *mkTypeExprFieldRef(
        ITypeExprFieldRef::RootRefKind      kind,
        int32_t                             offset,
        int32_t                             index) = 0;

	virtual ITypeExprRange *mkTypeExprRange(
			bool				is_single,
			ITypeExpr			*lower,
			ITypeExpr			*upper) = 0;

	virtual ITypeExprRangelist *mkTypeExprRangelist() = 0;

	virtual ITypeExprUnary *mkTypeExprUnary(
        ITypeExpr       *target,
        bool            owned,
        UnaryOp         op) = 0;

	virtual ITypeExprVal *mkTypeExprVal(
        IDataType       *type,
        ValData         v) = 0;

	virtual ITypeExprVal *mkTypeExprVal(const ValRef &v) = 0;

	virtual ITypeFieldPhy *mkTypeFieldPhy(
			const std::string		&name,
			IDataType				*dtype,
			bool					own_dtype,
			TypeFieldAttr			attr,
			ITypeExpr				*init) = 0;

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

    virtual ValRef mkValRef(IDataType *t) = 0;

    virtual ValRefArr mkValRefArr(IDataTypeArray *t) = 0;

    virtual ValRefBool mkValRefBool(
        bool        value) = 0;

    virtual ValRefInt mkValRefInt(
        int64_t     value,
        bool        is_signed, 
        int32_t     width) = 0;

    virtual ValRef mkValRefRawPtr(void *ptr) = 0;

    virtual ValRefStr mkValRefStr(const std::string &str, int32_t reserve=0) = 0;

    virtual ValRefStruct mkValRefStruct(IDataTypeStruct *t) = 0;


};
}
}
