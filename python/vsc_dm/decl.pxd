#*****************************************************************************
#* decl.pxd
#*****************************************************************************
cimport debug_mgr.decl as dm_decl
from libcpp.pair cimport pair as cpp_pair
from libcpp.set cimport set as cpp_set
from libcpp.string cimport string as cpp_string
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr
from libc.stdint cimport intptr_t
from libc.stdint cimport uintptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
cimport cpython.ref as cpy_ref

ctypedef IAccept *IAcceptP
ctypedef AssociatedDataClosure *AssociatedDataClosureP
ctypedef IDataType *IDataTypeP
ctypedef IDataTypeEnum *IDataTypeEnumP
ctypedef IDataTypeInt *IDataTypeIntP
ctypedef IDataTypeStruct *IDataTypeStructP
ctypedef IDataTypeVec *IDataTypeVecP
ctypedef IFactory *IFactoryP
ctypedef IModelConstraint *IModelConstraintP
ctypedef IModelConstraintBlock *IModelConstraintBlockP
ctypedef IModelConstraintExpr *IModelConstraintExprP
ctypedef IModelConstraintIfElse *IModelConstraintIfElseP
ctypedef IModelConstraintImplies *IModelConstraintImpliesP
ctypedef IModelConstraintScope *IModelConstraintScopeP
ctypedef IModelConstraintSoft *IModelConstraintSoftP
ctypedef IModelConstraintUnique *IModelConstraintUniqueP
ctypedef IModelExpr *IModelExprP
ctypedef IModelExprCond *IModelExprCondP
ctypedef IModelExprIn *IModelExprInP
ctypedef IModelExprPartSelect *IModelExprPartSelectP
ctypedef IModelExprRange *IModelExprRangeP
ctypedef IModelExprRangelist *IModelExprRangelistP
ctypedef IModelExprRef *IModelExprRefP
ctypedef IModelExprUnary *IModelExprUnaryP
ctypedef IModelExprVal *IModelExprValP
ctypedef IModelExprVecSubscript *IModelExprVecSubscriptP
ctypedef IModelField *IModelFieldP
ctypedef IModelFieldRef *IModelFieldRefP
ctypedef IModelFieldRoot *IModelFieldRootP
ctypedef IModelFieldType *IModelFieldTypeP
ctypedef IModelFieldTypeRef *IModelFieldTypeRefP
ctypedef IModelFieldVec *IModelFieldVecP
ctypedef IModelFieldVecRoot *IModelFieldVecRootP
ctypedef IModelFieldData *IModelFieldDataP
ctypedef ModelFieldDataClosure *ModelFieldDataClosureP
ctypedef IModelVal *IModelValP
ctypedef ITypeConstraint *ITypeConstraintP
ctypedef ITypeConstraintBlock *ITypeConstraintBlockP
ctypedef ITypeConstraintExpr *ITypeConstraintExprP
ctypedef ITypeConstraintIfElse *ITypeConstraintIfElseP
ctypedef ITypeConstraintImplies *ITypeConstraintImpliesP
ctypedef ITypeConstraintScope *ITypeConstraintScopeP
ctypedef ITypeConstraintSoft *ITypeConstraintSoftP
ctypedef ITypeConstraintUnique *ITypeConstraintUniqueP
ctypedef ITypeExpr *ITypeExprP
ctypedef ITypeExprBin *ITypeExprBinP
ctypedef ITypeExprEnumRef *ITypeExprEnumRefP
ctypedef ITypeExprFieldRef *ITypeExprFieldRefP
ctypedef ITypeExprRange *ITypeExprRangeP
ctypedef ITypeExprRangelist *ITypeExprRangelistP
ctypedef ITypeExprVal *ITypeExprValP
ctypedef ITypeField *ITypeFieldP
ctypedef ITypeFieldPhy *ITypeFieldPhyP
ctypedef ITypeFieldRef *ITypeFieldRefP
ctypedef IValIterator *IValIteratorP
ctypedef IVisitor *IVisitorP
ctypedef uintptr_t ValData

cdef extern from "vsc/dm/impl/UP.h" namespace "vsc::dm":
    cdef cppclass UP[T](unique_ptr[T]):
        UP()
        UP(T *, bool owned=True)
        T *get()

ctypedef UP[IDataTypeStruct] IDataTypeStructUP
ctypedef UP[IModelConstraint] IModelConstraintUP
ctypedef UP[IModelExpr] IModelExprUP
ctypedef UP[IModelExprRange] IModelExprRangeUP
ctypedef UP[IModelField] IModelFieldUP
ctypedef UP[ITypeExpr] ITypeExprUP
ctypedef UP[ITypeExprRange] ITypeExprRangeUP
ctypedef UP[ITypeField] ITypeFieldUP
ctypedef UP[ITypeConstraint] ITypeConstraintUP

cdef extern from "vsc/dm/impl/ValRef.h" namespace "vsc::dm":
    cdef cppclass ValRef:
        bool valid() const
        IDataType *type() const
        uintptr_t vp() const
        IValIterator *iterator()
        pass

cdef extern from "vsc/dm/impl/ValRefInt.h" namespace "vsc::dm":
    cdef cppclass ValRefInt(ValRef):
        ValRefInt()
        ValRefInt(const ValRef &rhs)
        bool is_signed()
        intptr_t get_val_s()
        uintptr_t get_val_u()
        void set_val(intptr_t v)

cdef extern from "vsc/dm/impl/ValRefPtr.h" namespace "vsc::dm":
    cdef cppclass ValRefPtr(ValRef):
        ValRefPtr()
        ValRefPtr(const ValRef &rhs)
        uintptr_t get_val() const
        void set_val(uintptr_t v)


cdef extern from "vsc/dm/impl/ValRefStruct.h" namespace "vsc::dm":
    cdef cppclass ValRefStruct(ValRef):
        ValRefStruct()
        ValRefStruct(const ValRef &rhs)
        int32_t getNumFields() const
        ValRef getFieldRef(int32_t i)
        pass

#********************************************************************
#* IContext
#********************************************************************
cdef extern from "vsc/dm/IContext.h" namespace "vsc::dm":
    cdef cppclass IContext:
        IModelFieldRoot *buildModelField(IDataTypeStruct *, const cpp_string &)
        IDataTypeEnum *findDataTypeEnum(const cpp_string &)
        IDataTypeEnum *mkDataTypeEnum(
            const cpp_string        &name,
            bool                    is_signed)
        bool addDataTypeEnum(IDataTypeEnum *)
        IModelConstraintBlock *mkModelConstraintBlock(const cpp_string &)
        IModelConstraintExpr *mkModelConstraintExpr(IModelExpr *expr)
        IModelConstraintIfElse *mkModelConstraintIfElse(
            IModelExpr *cond,
            IModelConstraint *true_c,
            IModelConstraint *false_c)
        IModelConstraintImplies *mkModelConstraintImplies(
            IModelExpr *cond,
            IModelConstraint *body)
        IModelConstraintScope *mkModelConstraintScope()
        IModelConstraintSoft *mkModelConstraintSoft(
            IModelConstraintExpr    *c)
        IModelConstraintUnique *mkModelConstraintUnique(
            const cpp_vector[IModelExprP]   &exprs)
        IDataTypeInt *findDataTypeInt(bool is_signed, int32_t width)
        IDataTypeInt *mkDataTypeInt(bool is_signed, int32_t width)
        bool addDataTypeInt(IDataTypeInt *)
        IDataTypeStruct *findDataTypeStruct(const cpp_string &)
        IDataTypeStruct *mkDataTypeStruct(const cpp_string &)
        bool addDataTypeStruct(IDataTypeStruct *)
        const cpp_vector[IDataTypeStructUP] &getDataTypeStructs()
        IModelExprBin *mkModelExprBin(IModelExpr *, BinOp, IModelExpr *)
        IModelExprFieldRef *mkModelExprFieldRef(IModelField *field)
        IModelExprIn *mkModelExprIn(IModelExpr *, IModelExprRangelist *)
        IModelExprPartSelect *mkModelExprPartSelect(IModelExpr *, int32_t , int32_t )
        IModelExprRange *mkModelExprRange(bool, IModelExpr *, IModelExpr *)
        IModelExprRangelist *mkModelExprRangelist()
        IModelExprUnary *mkModelExprUnary(IModelExpr *lhs, UnaryOp op)
        IModelExprVal *mkModelExprVal(IModelVal *)
        IModelField *mkModelFieldRoot(IDataType *, const cpp_string &)
        IModelFieldVec *mkModelFieldVecRoot(IDataType *, const cpp_string &)
        IModelVal *mkModelVal()
        ITypeConstraintBlock *mkTypeConstraintBlock(const cpp_string &)
        ITypeConstraintExpr *mkTypeConstraintExpr(ITypeExpr *)
        ITypeConstraintIfElse *mkTypeConstraintIfElse(
            ITypeExpr       *cond,
            ITypeConstraint *true_c,
            ITypeConstraint *false_c)
        ITypeConstraintImplies *mkTypeConstraintImplies(
            ITypeExpr       *cond,
            ITypeConstraint *body)
        ITypeConstraintScope *mkTypeConstraintScope()
        ITypeConstraintSoft *mkTypeConstraintSoft(
            ITypeConstraintExpr     *c)
        ITypeConstraintUnique *mkTypeConstraintUnique(
            const cpp_vector[ITypeExprP]    &exprs)
        ITypeExprBin *mkTypeExprBin(ITypeExpr *, BinOp, ITypeExpr *)
        ITypeExprEnumRef *mkTypeExprEnumRef(IDataTypeEnum *, int32_t)
        ITypeExprRange *mkTypeExprRange(bool, ITypeExpr *, ITypeExpr *)
        ITypeExprRangelist *mkTypeExprRangelist()
        ITypeExprVal *mkTypeExprVal(IDataType *, ValData)
        ITypeFieldPhy *mkTypeFieldPhy(
            const cpp_string &,
            IDataType *,
            bool,
            TypeFieldAttr,
            ITypeExpr *)
        ITypeFieldRef *mkTypeFieldRef(
            const cpp_string &,
            IDataType *,
            TypeFieldAttr)
        ValRefInt mkValRefInt(int64_t value, bool is_signed, int32_t width)
        ValRefStruct mkValRefStruct(IDataTypeStruct *)

cdef extern from "vsc/dm/IModelBuildContext.h" namespace "vsc::dm":
    cdef cppclass IModelBuildContext:
        IContext *ctxt()
        pass
        
#********************************************************************
#* IAccept
#********************************************************************
cdef extern from "vsc/dm/IAccept.h" namespace "vsc::dm":
    cdef cppclass IAccept:
        void accept(IVisitor *)

cdef extern from "vsc/dm/IAssociatedData.h" namespace "vsc::dm":
    cdef cppclass IAssociatedData:
        pass

cdef extern from "AssociatedDataClosure.h" namespace "vsc::dm":
    cdef cppclass AssociatedDataClosure(IAssociatedData):
        AssociatedDataClosure(cpy_ref.PyObject *)
        object getData()
    pass

#********************************************************************
#* IDataType
#********************************************************************

cdef extern from "vsc/dm/IDataType.h" namespace "vsc::dm":
    cdef cppclass IDataType(IAccept):
        IModelField *mkRootField(
            IModelBuildContext     *ctxt,
            const cpp_string       &name,
            bool                   is_ref)
        IModelField *mkTypeField(
            IModelBuildContext     *ctxt,
            ITypeField             *type,
            const ValRef           &val)

        void setAssociatedData(IAssociatedData *data)
        IAssociatedData *getAssociatedData()
    
cdef extern from "vsc/dm/IDataTypeEnum.h" namespace "vsc::dm":
    cdef cppclass IDataTypeEnum(IDataType):
        const cpp_string &name() const
        bool isSigned() const
        bool addEnumerator(
            const cpp_string    &name,
            const IModelVal     *val)
        ITypeExprRangelist *getDomain()
    
cdef extern from "vsc/dm/IDataTypeInt.h" namespace "vsc::dm":
    cdef cppclass IDataTypeInt(IDataType):
        bool is_signed() const
        int32_t width() const
        pass
    
cdef extern from "vsc/dm/IDataTypeStruct.h" namespace "vsc::dm":
    cdef cppclass IDataTypeStruct(IDataType):
        const cpp_string &name() const
        void addField(ITypeField *)
        ITypeField *getField(int32_t idx)
        const cpp_vector[ITypeFieldUP] &getFields() const
        void addConstraint(ITypeConstraint *)
        const cpp_vector[ITypeConstraintUP] &getConstraints() const
        void setCreateHook(IModelStructCreateHook *)
       
cdef extern from "vsc/dm/IDataTypeVec.h" namespace "vsc::dm":
    cdef cppclass IDataTypeVec(IDataType):
        IDataType *getElemType() const

#********************************************************************
#* IFactory
#********************************************************************
cdef extern from "vsc/dm/IFactory.h" namespace "vsc::dm":
    cdef cppclass IFactory:
        void init(dm_decl.IDebugMgr *)
        IContext *mkContext()
        dm_decl.IDebugMgr *getDebugMgr()

#********************************************************************
#* IModelConstraint
#********************************************************************
#ctypedef IModelConstraint *IModelConstraintP
cdef extern from "vsc/dm/IModelConstraint.h" namespace "vsc::dm":
    cdef cppclass IModelConstraint(IAccept):
        pass
    
cdef extern from "vsc/dm/IModelConstraintScope.h" namespace "vsc::dm":
    cdef cppclass IModelConstraintScope(IModelConstraint):
        const cpp_vector[IModelConstraintUP] &getConstraints() const
        void addConstraint(IModelConstraint *)

cdef extern from "vsc/dm/IModelConstraintSoft.h" namespace "vsc::dm":
    cdef cppclass IModelConstraintSoft(IModelConstraint):
        IModelConstraintExpr *constraint() const

cdef extern from "vsc/dm/IModelConstraintUnique.h" namespace "vsc::dm":
    cdef cppclass IModelConstraintUnique(IModelConstraint):
        const cpp_vector[IModelExprUP] &getExprs() const
    
cdef extern from "vsc/dm/IModelConstraintBlock.h" namespace "vsc::dm":
    cdef cppclass IModelConstraintBlock(IModelConstraintScope):
        const cpp_string &name()
    
cdef extern from "vsc/dm/IModelConstraintExpr.h" namespace "vsc::dm":
    cdef cppclass IModelConstraintExpr(IModelConstraint):
        IModelExpr *expr() const

cdef extern from "vsc/dm/IModelConstraintIfElse.h" namespace "vsc::dm":
    cdef cppclass IModelConstraintIfElse(IModelConstraint):
        IModelExpr *getCond() const
        IModelConstraint *getTrue() const
        IModelConstraint *getFalse() const
        void setFalse(IModelConstraint *)

cdef extern from "vsc/dm/IModelConstraintImplies.h" namespace "vsc::dm":
    cdef cppclass IModelConstraintImplies(IModelConstraint):
        IModelExpr *getCond() const
        IModelConstraint *getBody() const

#********************************************************************
#* IModelExpr
#********************************************************************
cdef extern from "vsc/dm/IModelExpr.h" namespace "vsc::dm":
    cdef cppclass IModelExpr(IAccept):
        pass
    
cdef extern from "vsc/dm/IModelExprCond.h" namespace "vsc::dm":
    cdef cppclass IModelExprCond(IModelExpr):
        IModelExpr *getCond() const
        IModelExpr *getTrue() const
        IModelExpr *getFalse() const
    
cdef extern from "vsc/dm/IModelExprFieldRef.h" namespace "vsc::dm":
    cdef cppclass IModelExprFieldRef(IModelExpr):
        IModelField *field() const
        
cdef extern from "vsc/dm/IModelExprPartSelect.h" namespace "vsc::dm":
    cdef cppclass IModelExprPartSelect(IModelExpr):
        IModelExpr *lhs() const
        int32_t lower() const
        int32_t upper() const

cdef extern from "vsc/dm/IModelExprRange.h" namespace "vsc::dm":
    cdef cppclass IModelExprRange(IModelExpr):
        bool isSingle() const
        IModelExpr *lower() const
        IModelExpr *upper() const
        
cdef extern from "vsc/dm/IModelExprRangelist.h" namespace "vsc::dm":
    cdef cppclass IModelExprRangelist(IModelExpr):
        const cpp_vector[IModelExprRangeUP] &ranges() const
        void addRange(IModelExprRange *)

cdef extern from "vsc/dm/IModelExprRef.h" namespace "vsc::dm":
    cdef cppclass IModelExprRef(IModelExpr):
        IModelExpr *expr() const

cdef extern from "vsc/dm/IModelExprUnary.h" namespace "vsc::dm":
    cdef enum UnaryOp "vsc::dm::UnaryOp":
        Un_Not     "vsc::dm::UnaryOp::Not"
        
    cdef cppclass IModelExprUnary(IModelExpr):
        IModelExpr *expr() const
        UnaryOp op() const

cdef extern from "vsc/dm/IModelExprVal.h" namespace "vsc::dm":
    cdef cppclass IModelExprVal(IModelExpr):
        int32_t width() const
        IModelVal *val()

cdef extern from "vsc/dm/IModelExprVecSubscript.h" namespace "vsc::dm":
    cdef cppclass IModelExprVecSubscript(IModelExpr):
        IModelExpr *expr() const
        IModelExpr *subscript() const
        
#********************************************************************
#* IModelExprBin
#********************************************************************
cdef extern from "vsc/dm/IModelExprBin.h" namespace "vsc::dm":
    cdef enum BinOp "vsc::dm::BinOp":
        Eq      "vsc::dm::BinOp::Eq"
        Ne      "vsc::dm::BinOp::Ne"
        Gt      "vsc::dm::BinOp::Gt"
        Ge      "vsc::dm::BinOp::Ge"
        Lt      "vsc::dm::BinOp::Lt"
        Le      "vsc::dm::BinOp::Le"
        Add     "vsc::dm::BinOp::Add"
        Sub     "vsc::dm::BinOp::Sub"
        Div     "vsc::dm::BinOp::Div"
        Mul     "vsc::dm::BinOp::Mul"
        Mod     "vsc::dm::BinOp::Mod"
        BinAnd  "vsc::dm::BinOp::BinAnd"
        BinOr   "vsc::dm::BinOp::BinOr" 
        LogAnd  "vsc::dm::BinOp::LogAnd"
        LogOr   "vsc::dm::BinOp::LogOr"
        Sll     "vsc::dm::BinOp::Sll"
        Srl     "vsc::dm::BinOp::Srl"
        BinXor  "vsc::dm::BinOp::BinXor"
        Not     "vsc::dm::BinOp::Not"
        
    cdef cppclass IModelExprBin(IModelExpr):
        pass
    
    cdef cppclass IModelExprIn(IModelExpr):
        pass

#********************************************************************
#* IModelField
#********************************************************************
#ctypedef IModelField *IModelFieldP
cdef extern from "vsc/dm/IModelField.h" namespace "vsc::dm":

    cdef enum ModelFieldFlag:
        NoFlags  "vsc::dm::ModelFieldFlag::NoFlags"
        DeclRand "vsc::dm::ModelFieldFlag::DeclRand"
        UsedRand "vsc::dm::ModelFieldFlag::UsedRand"
        Resolved "vsc::dm::ModelFieldFlag::Resolved"
        VecSize  "vsc::dm::ModelFieldFlag::VecSize"
        
    cdef cppclass IModelField(IAccept):
    
        const cpp_string &name()
        IDataType *getDataType()
        IModelField *getParent()
        void setParent(IModelField *)
        const cpp_vector[IModelConstraintUP] &getConstraints()
        void addConstraint(IModelConstraintP)
        const cpp_vector[IModelFieldUP] &getFields()
        void addField(IModelField *)
        IModelField *getField(int32_t)
        IModelValP val()
        
        void clearFlag(ModelFieldFlag flags)
        void setFlag(ModelFieldFlag flags)
        bool isFlagSet(ModelFieldFlag flags)
        
        void setFieldData(IModelFieldData *)
        IModelFieldData *getFieldData()
        
cdef extern from "vsc/dm/IModelFieldRef.h" namespace "vsc::dm":
    cdef cppclass IModelFieldRef(IModelField):
        
        void setRef(IModelField *)
        IModelField *getRef() const
        
cdef extern from "vsc/dm/IModelFieldFactory.h" namespace "vsc::dm":
    cdef cppclass IModelFieldFactory:
        IModelField *create(const cpp_string &, IModelField *)
        
cdef extern from "vsc/dm/IModelFieldVec.h" namespace "vsc::dm":
    cdef cppclass IModelFieldVec(IModelField):
        IModelField *getSizeRef() const
        uint32_t getSize() const
        void push_back(IModelField *)
        IModelField *at(uint32_t idx)
        void pop_back()
        IModelFieldFactory *getFieldFactory()
        void setFieldFactory(IModelFieldFactory *)
        
cdef extern from "vsc/dm/IModelFieldVecRoot.h" namespace "vsc::dm":

    cdef cppclass IModelFieldVecRoot(IModelFieldVec):
        void setName(const cpp_string &)
        pass

cdef extern from "vsc/dm/IModelFieldData.h" namespace "vsc::dm":
    cdef cppclass IModelFieldData:
        pass
    
cdef extern from "ModelFieldDataClosure.h" namespace "vsc::dm":
    cdef cppclass ModelFieldDataClosure(IModelFieldData):
        ModelFieldDataClosure(cpy_ref.PyObject *)
        object getData()

cdef extern from "vsc/dm/IModelFieldRoot.h" namespace "vsc::dm":

    cdef cppclass IModelFieldRoot(IModelField):
        void setName(const cpp_string &)
        pass
    
cdef extern from "vsc/dm/IModelFieldType.h" namespace "vsc::dm":
    cdef cppclass IModelFieldType(IModelField):
        pass

cdef extern from "vsc/dm/IModelFieldTypeRef.h" namespace "vsc::dm":
    cdef cppclass IModelFieldTypeRef(IModelFieldRef):
        pass
    
cdef extern from "vsc/dm/IModelStructCreateHook.h" namespace "vsc::dm":
    cdef cppclass IModelStructCreateHook:
        pass
    
cdef extern from "ModelStructCreateHookClosure.h" namespace "vsc::dm":
    cdef cppclass ModelStructCreateHookClosure(IModelStructCreateHook):
        ModelStructCreateHookClosure(cpy_ref.PyObject *)

#********************************************************************
#* IModelVal
#********************************************************************
cdef extern from "vsc/dm/IModelVal.h" namespace "vsc::dm":
    cdef union val_t "IModelVal::val_t":
        uint64_t         v
        uint64_t        *vp
    cdef cppclass IModelVal:
    
        uint32_t bits() const
        void setBits(uint32_t)
        int64_t val_i() const
        uint64_t val_u() const
        void set_val_i(int64_t, int32_t)
        void set_val_u(uint64_t, int32_t)
        val_t &val()
        
#********************************************************************
#* ITask
#********************************************************************
cdef extern from "vsc/dm/ITask.h" namespace "vsc::dm":
    cdef cppclass ITask:
        void apply(IAccept *)
        
#********************************************************************
#* ITypeConstraint
#********************************************************************
cdef extern from "vsc/dm/ITypeConstraint.h" namespace "vsc::dm":
    cdef cppclass ITypeConstraint(IAccept):
        pass
    
cdef extern from "vsc/dm/ITypeConstraintExpr.h" namespace "vsc::dm":
    cdef cppclass ITypeConstraintExpr(ITypeConstraint):
        ITypeExpr *expr() const

cdef extern from "vsc/dm/ITypeConstraintIfElse.h" namespace "vsc::dm":
    cdef cppclass ITypeConstraintIfElse(ITypeConstraint):
        ITypeExpr *getCond() const
        ITypeConstraint *getTrue() const
        ITypeConstraint *getFalse() const
        void setFalse(ITypeConstraint *)

cdef extern from "vsc/dm/ITypeConstraintImplies.h" namespace "vsc::dm":
    cdef cppclass ITypeConstraintImplies(ITypeConstraint):
        ITypeExpr *getCond() const
        ITypeConstraint *getBody() const
        
cdef extern from "vsc/dm/ITypeConstraintScope.h" namespace "vsc::dm":
    cdef cppclass ITypeConstraintScope(ITypeConstraint):
        void addConstraint(ITypeConstraint *)
        const cpp_vector[ITypeConstraintUP] &getConstraints() const

cdef extern from "vsc/dm/ITypeConstraintSoft.h" namespace "vsc::dm":
    cdef cppclass ITypeConstraintSoft(ITypeConstraint):
        ITypeConstraintExpr *constraint() const

cdef extern from "vsc/dm/ITypeConstraintUnique.h" namespace "vsc::dm":
    cdef cppclass ITypeConstraintUnique(ITypeConstraint):
        const cpp_vector[ITypeExprUP] &getExprs() const

cdef extern from "vsc/dm/ITypeConstraintBlock.h" namespace "vsc::dm":
    cdef cppclass ITypeConstraintBlock(ITypeConstraintScope):
        const cpp_string &name() const
    
#********************************************************************
#* ITypeExpr
#********************************************************************

cdef extern from "vsc/dm/ITypeExpr.h" namespace "vsc::dm":
    cdef cppclass ITypeExpr(IAccept):
        pass
    
cdef extern from "vsc/dm/ITypeExprBin.h" namespace "vsc::dm":
    cdef cppclass ITypeExprBin(ITypeExpr):
        ITypeExpr *lhs() const
        BinOp op() const
        ITypeExpr *rhs() const

cdef extern from "vsc/dm/ITypeExprEnumRef.h" namespace "vsc::dm":
    cdef cppclass ITypeExprEnumRef(ITypeExpr):
        IDataTypeEnum *getEnumType()
        int32_t getEnumeratorId()
    
cdef extern from "vsc/dm/ITypeExprFieldRef.h" namespace "vsc::dm":
        
    cdef enum TypeExprFieldRef_RootRefKind "vsc::dm::ITypeExprFieldRef::RootRefKind":
        TypeExprFieldRef_TopDownScope  "vsc::dm::ITypeExprFieldRef::RootRefKind::TopDownScope" 
        TypeExprFieldRef_BottomUpScope "vsc::dm::ITypeExprFieldRef::RootRefKind::BottomUpScope" 

    cdef cppclass ITypeExprFieldRef(ITypeExpr):
        TypeExprFieldRef_RootRefKind getRootRefKind() const
        void addPathElem(int32_t idx)
        uint32_t size() const
        int32_t at(int32_t) const
        const cpp_vector[int32_t] &getPath() const
        
cdef extern from "vsc/dm/ITypeExprRange.h" namespace "vsc::dm":
    cdef cppclass ITypeExprRange(ITypeExpr):
        bool isSingle()
        ITypeExpr *lower() const
        ITypeExpr *upper() const
        
cdef extern from "vsc/dm/ITypeExprRangelist.h" namespace "vsc::dm":
    cdef cppclass ITypeExprRangelist(ITypeExpr):
        void addRange(ITypeExprRange *)
        const cpp_vector[ITypeExprRangeUP] &getRanges() const

cdef extern from "vsc/dm/ITypeExprVal.h" namespace "vsc::dm":

    cdef cppclass ITypeExprVal(ITypeExpr):
        
        const ValData val() const

#********************************************************************
#* ITypeField
#********************************************************************
cdef extern from "vsc/dm/ITypeField.h" namespace "vsc::dm":
    cdef enum TypeFieldAttr:
        NoAttr        "vsc::dm::TypeFieldAttr::NoAttr"
        Rand          "vsc::dm::TypeFieldAttr::Rand"
    
    cdef cppclass ITypeField(IAccept):
        ITypeField *getParent()
        void setParent(ITypeField *)
        int32_t getIndex()
        void setIndex(int32_t)
        const cpp_string &name() const
        IDataType *getDataType() const
        ITypeField *getField(int32_t)
        TypeFieldAttr getAttr() const
        
cdef extern from "vsc/dm/ITypeFieldPhy.h" namespace "vsc::dm":

    cdef cppclass ITypeFieldPhy(ITypeField):
        ValData getInit() const
        bool haveInit() const
        
cdef extern from "vsc/dm/ITypeFieldRef.h" namespace "vsc::dm":
    
    cdef cppclass ITypeFieldRef(ITypeField):
        pass

cdef extern from "vsc/dm/IValIterator.h" namespace "vsc::dm":
    cdef cppclass IValIterator:
        void reset()
        IDataType *getDataType()
        const ValRef &getVal()
        int32_t numFields()
        IDataType *getFieldType(int32_t idx)
        const ValRef &getFieldVal(int32_t idx)
        const cpp_string &getFieldName(int32_t idx)
        bool push(int32_t idx)
        bool pop()

#********************************************************************
#* IVisitor
#********************************************************************
cdef extern from "vsc/dm/IVisitor.h" namespace "vsc::dm":
    cdef cppclass IVisitor:
        pass
    
#********************************************************************
# VisitorProxy
#********************************************************************
cdef extern from "VisitorProxy.h":
    cdef cppclass VisitorProxy(IVisitor):
        VisitorProxy(cpy_ref.PyObject *)
        void visitModelExprBinBase(IModelExprBin *)
        pass

cdef extern IModelBuildContext *mkModelBuildContext(IContext *ctxt)
    
#********************************************************************
#* VscTasks
#********************************************************************

cdef extern from "VscTasks.h" namespace "vsc::dm":
    cdef extern IModelField *Task_BuildModelField(
        IContext *ctxt,
        IDataType *dt, 
        const cpp_string &name)
    
