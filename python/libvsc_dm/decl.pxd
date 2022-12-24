#*****************************************************************************
#* decl.pxd
#*****************************************************************************
from debug_mgr cimport decl as dm_decl
from libcpp.pair cimport pair as cpp_pair
from libcpp.set cimport set as cpp_set
from libcpp.string cimport string as cpp_string
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr
from libc.stdint cimport intptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
cimport cpython.ref as cpy_ref

ctypedef IAccept *IAcceptP
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
ctypedef unique_ptr[IModelExpr] IModelExprUP
ctypedef IModelExprCond *IModelExprCondP
ctypedef IModelExprIn *IModelExprInP
ctypedef IModelExprPartSelect *IModelExprPartSelectP
ctypedef IModelExprRange *IModelExprRangeP
ctypedef unique_ptr[IModelExprRange] IModelExprRangeUP
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
ctypedef unique_ptr[ITypeExpr] ITypeExprUP
ctypedef ITypeExprBin *ITypeExprBinP
ctypedef ITypeExprFieldRef *ITypeExprFieldRefP
ctypedef ITypeExprRange *ITypeExprRangeP
ctypedef unique_ptr[ITypeExprRange] ITypeExprRangeUP
ctypedef ITypeExprRangelist *ITypeExprRangelistP
ctypedef ITypeExprVal *ITypeExprValP
ctypedef ITypeField *ITypeFieldP
ctypedef ITypeFieldPhy *ITypeFieldPhyP
ctypedef ITypeFieldRef *ITypeFieldRefP
ctypedef IVisitor *IVisitorP

#********************************************************************
#* IContext
#********************************************************************
cdef extern from "vsc/dm/IContext.h" namespace "vsc::dm":
    cdef cppclass IContext:
        IModelFieldRoot *buildModelField(IDataTypeStruct *, const cpp_string &)
        ICompoundSolver *mkCompoundSolver()
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
        IRandState *mkRandState(const cpp_string &)
        IRandomizer *mkRandomizer(ISolverFactory *, IRandState *)
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
        ITypeExprFieldRef *mkTypeExprFieldRef()
        ITypeExprRange *mkTypeExprRange(bool, ITypeExpr *, ITypeExpr *)
        ITypeExprRangelist *mkTypeExprRangelist()
        ITypeExprVal *mkTypeExprVal(IModelVal *)
        ITypeFieldPhy *mkTypeFieldPhy(
            const cpp_string &,
            IDataType *,
            bool,
            TypeFieldAttr,
            IModelVal *)
        ITypeFieldRef *mkTypeFieldRef(
            const cpp_string &,
            IDataType *,
            TypeFieldAttr)

cdef extern from "vsc/dm/IModelBuildContext.h" namespace "vsc::dm":
    cdef cppclass IModelBuildContext:
        IContext *ctxt()
        pass
        
#********************************************************************
#* ICompoundSolver
#********************************************************************
cdef extern from "vsc/dm/ICompoundSolver.h" namespace "vsc::dm":

    cdef enum SolveFlags:
        Randomize          "vsc::SolveFlags::Randomize"
        RandomizeDeclRand  "vsc::SolveFlags::RandomizeDeclRand"
        RandomizeTopFields "vsc::SolveFlags::RandomizeTopFields"
        DiagnoseFailures   "vsc::SolveFlags::DiagnoseFailures"
    
    cdef cppclass ICompoundSolver:
        
        bool solve(
            IRandState                          *randstate,
            const cpp_vector[IModelFieldP]      &fields,
            const cpp_vector[IModelConstraintP] &constraints,
            SolveFlags                          flags)
        
        
#********************************************************************
#* IAccept
#********************************************************************
cdef extern from "vsc/dm/IAccept.h" namespace "vsc::dm":
    cdef cppclass IAccept:
        void accept(IVisitor *)
    
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
            ITypeField             *type)
    
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
        pass
    
cdef extern from "vsc/dm/IDataTypeStruct.h" namespace "vsc::dm":
    cdef cppclass IDataTypeStruct(IDataType):
        const cpp_string &name() const
        void addField(ITypeField *)
        ITypeField *getField(int32_t idx)
        const cpp_vector[unique_ptr[ITypeField]] &getFields() const
        void addConstraint(ITypeConstraint *)
        const cpp_vector[unique_ptr[ITypeConstraint]] &getConstraints() const
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
#* IVsc
#********************************************************************
#cdef extern from "vsc/dm/IVsc.h" namespace "vsc::dm":
#    cdef cppclass IVsc:
#        IContext *mkContext()
#        IDebugMgr *getDebugMgr()
    
        
#********************************************************************
#* IModelConstraint
#********************************************************************
#ctypedef IModelConstraint *IModelConstraintP
cdef extern from "vsc/dm/IModelConstraint.h" namespace "vsc::dm":
    cdef cppclass IModelConstraint(IAccept):
        pass
    
cdef extern from "vsc/dm/IModelConstraintScope.h" namespace "vsc::dm":
    cdef cppclass IModelConstraintScope(IModelConstraint):
        const cpp_vector[unique_ptr[IModelConstraint]] &constraints() const
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
    cdef enum UnaryOp "vsc::UnaryOp":
        Un_Not     "vsc::UnaryOp::Not"
        
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
    cdef enum BinOp "vsc::BinOp":
        Eq      "vsc::BinOp::Eq"
        Ne      "vsc::BinOp::Ne"
        Gt      "vsc::BinOp::Gt"
        Ge      "vsc::BinOp::Ge"
        Lt      "vsc::BinOp::Lt"
        Le      "vsc::BinOp::Le"
        Add     "vsc::BinOp::Add"
        Sub     "vsc::BinOp::Sub"
        Div     "vsc::BinOp::Div"
        Mul     "vsc::BinOp::Mul"
        Mod     "vsc::BinOp::Mod"
        BinAnd  "vsc::BinOp::BinAnd"
        BinOr   "vsc::BinOp::BinOr" 
        LogAnd  "vsc::BinOp::LogAnd"
        LogOr   "vsc::BinOp::LogOr"
        Sll     "vsc::BinOp::Sll"
        Srl     "vsc::BinOp::Srl"
        Xor     "vsc::BinOp::Xor"
        Not     "vsc::BinOp::Not"
        
    cdef cppclass IModelExprBin(IModelExpr):
        pass
    
    cdef cppclass IModelExprIn(IModelExpr):
        pass

#********************************************************************
#* IModelField
#********************************************************************
#ctypedef IModelField *IModelFieldP
ctypedef unique_ptr[IModelField] IModelFieldUP
cdef extern from "vsc/dm/IModelField.h" namespace "vsc::dm":

    cdef enum ModelFieldFlag:
        NoFlags  "vsc::ModelFieldFlag::NoFlags"
        DeclRand "vsc::ModelFieldFlag::DeclRand"
        UsedRand "vsc::ModelFieldFlag::UsedRand"
        Resolved "vsc::ModelFieldFlag::Resolved"
        VecSize  "vsc::ModelFieldFlag::VecSize"
        
    cdef cppclass IModelField(IAccept):
    
        const cpp_string &name()
        IDataType *getDataType()
        IModelField *getParent()
        void setParent(IModelField *)
        const cpp_vector[unique_ptr[IModelConstraint]] &constraints()
        void addConstraint(IModelConstraintP)
        const cpp_vector[IModelFieldUP] &fields()
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
#* IRandomizer
#********************************************************************
cdef extern from "vsc/dm/IRandomizer.h" namespace "vsc::dm":
    cdef cppclass IRandomizer:
        bool randomize(
            const cpp_vector[IModelFieldP]       &fields,
            const cpp_vector[IModelConstraintP]  &constraints,
            bool                                 diagnose_failures)
    
#********************************************************************
#* IRandState
#********************************************************************
cdef extern from "vsc/dm/IRandState.h" namespace "vsc::dm":
    cdef cppclass IRandState:
        const cpp_string &seed() const
        int32_t randint32(int32_t, int32_t)
        uint64_t rand_ui64()
        int64_t rand_i64()
        void randbits(IModelVal *)
        void setState(IRandState *)
        IRandState *clone() const
        IRandState *next()
        
#********************************************************************
#* ISolverFactory
#********************************************************************
cdef extern from "vsc/dm/ISolverFactory.h" namespace "vsc::dm":
    cdef cppclass ISolverFactory:
        pass
        
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
        const cpp_vector[unique_ptr[ITypeConstraint]] &constraints() const

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
    
cdef extern from "vsc/dm/ITypeExprFieldRef.h" namespace "vsc::dm":
    cdef enum TypeExprFieldRefElemKind:
        Root "vsc::TypeExprFieldRefElemKind::Root" 
        ActiveScope "vsc::TypeExprFieldRefElemKind::ActiveScope" 
        IdxOffset "vsc::TypeExprFieldRefElemKind::IdxOffset" 
        
    cdef cppclass TypeExprFieldRefElem:
        TypeExprFieldRefElemKind        kind
        int32_t                         idx

    cdef cppclass ITypeExprFieldRef(ITypeExpr):
        void addIdxRef(int32_t)
        void addActiveScopeRef(int32_t)
        void addRootRef()
        uint32_t size() const
        const TypeExprFieldRefElem &at(int32_t) const
        
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
        
        const IModelVal *val() const

#********************************************************************
#* ITypeField
#********************************************************************
cdef extern from "vsc/dm/ITypeField.h" namespace "vsc::dm":
    cdef enum TypeFieldAttr:
        NoAttr        "vsc::TypeFieldAttr::NoAttr"
        Rand          "vsc::TypeFieldAttr::Rand"
    
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
        IModelVal *getInit() const
        
cdef extern from "vsc/dm/ITypeFieldRef.h" namespace "vsc::dm":
    
    cdef cppclass ITypeFieldRef(ITypeField):
        pass

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
    
#********************************************************************
#* IVsc
#********************************************************************
cdef extern from "vsc/dm/IVsc.h" namespace "vsc::dm":
    cdef cppclass IVsc:
        pass

#********************************************************************
#* py_get_vsc
#********************************************************************
cdef extern IVsc *py_get_vsc(const char *path)
#cdef extern from "py_get_vsc.h":

cdef extern IModelBuildContext *mkModelBuildContext(IContext *ctxt)
    
#********************************************************************
#* VscTasks
#********************************************************************

cdef extern from "VscTasks.h" namespace "vsc::dm":
    cdef extern IModelField *Task_BuildModelField(
        IContext *ctxt,
        IDataType *dt, 
        const cpp_string &name)
    
