#*****************************************************************************
#* decl.pxd
#*****************************************************************************
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

ctypedef IDataTypeStruct *IDataTypeStructP
ctypedef IModelField *IModelFieldP
ctypedef IModelConstraint *IModelConstraintP
ctypedef IModelVal *IModelValP
ctypedef ITypeConstraint *ITypeConstraintP
ctypedef ITypeConstraintBlock *ITypeConstraintBlockP
ctypedef ITypeConstraintExpr *ITypeConstraintExprP
ctypedef ITypeConstraintScope *ITypeConstraintScopeP
ctypedef ITypeExprBin *ITypeExprBinP
ctypedef ITypeExprFieldRef *ITypeExprFieldRefP
ctypedef ITypeExprVal *ITypeExprValP
ctypedef ITypeField *ITypeFieldP

#********************************************************************
#* IContext
#********************************************************************
cdef extern from "vsc/IContext.h" namespace "vsc":
    cdef cppclass IContext:
        IModelFieldRoot *buildModelField(IDataTypeStruct *, const cpp_string &)
        ICompoundSolver *mkCompoundSolver()
        IModelConstraintBlock *mkModelConstraintBlock(const cpp_string &)
        IModelConstraintExpr *mkModelConstraintExpr(IModelExpr *expr)
        IDataTypeInt *findDataTypeInt(bool is_signed, int32_t width)
        IDataTypeInt *mkDataTypeInt(bool is_signed, int32_t width)
        bool addDataTypeInt(IDataTypeInt *)
        IDataTypeStruct *findDataTypeStruct(const cpp_string &)
        IDataTypeStruct *mkDataTypeStruct(const cpp_string &)
        bool addDataTypeStruct(IDataTypeStruct *)
        IModelExprBin *mkModelExprBin(IModelExpr *, BinOp, IModelExpr *)
        IModelExprFieldRef *mkModelExprFieldRef(IModelField *field)
        IModelExprVal *mkModelExprVal(IModelVal *)
        IModelField *mkModelFieldRoot(IDataType *, const cpp_string &)
        IRandState *mkRandState(uint32_t)
        IRandomizer *mkRandomizer(ISolverFactory *, IRandState *)
        ITypeConstraintBlock *mkTypeConstraintBlock(const cpp_string &)
        ITypeConstraintExpr *mkTypeConstraintExpr(ITypeExpr *)
        ITypeConstraintScope *mkTypeConstraintScope()
        ITypeExprBin *mkTypeExprBin(ITypeExpr *, BinOp, ITypeExpr *)
        ITypeExprFieldRef *mkTypeExprFieldRef()
        ITypeExprVal *mkTypeExprVal(IModelVal *)
        ITypeField *mkTypeField(
            const cpp_string &,
            IDataType *,
            TypeFieldAttr,
            IModelVal *)
        
#********************************************************************
#* ICompoundSolver
#********************************************************************
cdef extern from "vsc/ICompoundSolver.h" namespace "vsc":

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
cdef extern from "vsc/IAccept.h" namespace "vsc":
    cdef cppclass IAccept:
        void accept(IVisitor *)
    
#********************************************************************
#* IDataType
#********************************************************************
ctypedef IDataTypeInt *IDataTypeIntP

cdef extern from "vsc/IDataType.h" namespace "vsc":
    cdef cppclass IDataType(IAccept):
        pass
    
cdef extern from "vsc/IDataTypeInt.h" namespace "vsc":
    cdef cppclass IDataTypeInt(IDataType):
        pass
    
cdef extern from "vsc/IDataTypeStruct.h" namespace "vsc":
    cdef cppclass IDataTypeStruct(IDataType):
        const cpp_string &name() const
        void addField(ITypeField *)
        ITypeField *getField(int32_t idx)
        const cpp_vector[unique_ptr[ITypeField]] &getFields() const
        void addConstraint(ITypeConstraint *)
        const cpp_vector[unique_ptr[ITypeConstraint]] &getConstraints() const
        void setCreateHook(IModelStructCreateHook *)
        

#********************************************************************
#* IVsc
#********************************************************************
cdef extern from "vsc/IVsc.h" namespace "vsc":
    cdef cppclass IVsc:
        IContext *mkContext()
        pass
    
        
#********************************************************************
#* IModelConstraint
#********************************************************************
#ctypedef IModelConstraint *IModelConstraintP
cdef extern from "vsc/IModelConstraint.h" namespace "vsc":
    cdef cppclass IModelConstraint:
        pass
    
cdef extern from "vsc/IModelConstraintScope.h" namespace "vsc":
    cdef cppclass IModelConstraintScope(IModelConstraint):
        const cpp_vector[unique_ptr[IModelConstraint]] &constraints() const
        void add_constraint(IModelConstraint *)
    
cdef extern from "vsc/IModelConstraintBlock.h" namespace "vsc":
    cdef cppclass IModelConstraintBlock(IModelConstraintScope):
        const cpp_string &name()
    
cdef extern from "vsc/IModelConstraintExpr.h" namespace "vsc":
    cdef cppclass IModelConstraintExpr(IModelConstraint):
        IModelExpr *expr() const

#********************************************************************
#* IModelExpr
#********************************************************************
cdef extern from "vsc/IModelExpr.h" namespace "vsc":
    cdef cppclass IModelExpr(IAccept):
        pass
    
    
cdef extern from "vsc/IModelExprFieldRef.h" namespace "vsc":
    cdef cppclass IModelExprFieldRef(IModelExpr):
        IModelField *field() const
        
cdef extern from "vsc/IModelExprVal.h" namespace "vsc":
    cdef cppclass IModelExprVal(IModelExpr):
        int32_t width() const
        IModelVal *val()
        
#********************************************************************
#* IModelExprBin
#********************************************************************
cdef extern from "vsc/IModelExprBin.h" namespace "vsc":
    cdef enum BinOp:
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

#********************************************************************
#* IModelField
#********************************************************************
#ctypedef IModelField *IModelFieldP
ctypedef unique_ptr[IModelField] IModelFieldUP
cdef extern from "vsc/IModelField.h" namespace "vsc":

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

cdef extern from "vsc/IModelFieldRoot.h" namespace "vsc":

    cdef cppclass IModelFieldRoot(IModelField):
        pass
    
cdef extern from "vsc/IModelFieldType.h" namespace "vsc":
    cdef cppclass IModelFieldType(IModelField):
        pass
    
cdef extern from "vsc/IModelStructCreateHook.h" namespace "vsc":
    cdef cppclass IModelStructCreateHook:
        pass
    
cdef extern from "ModelStructCreateHookClosure.h" namespace "vsc":
    cdef cppclass ModelStructCreateHookClosure(IModelStructCreateHook):
        ModelStructCreateHookClosure(cpy_ref.PyObject *)

#********************************************************************
#* IModelVal
#********************************************************************
cdef extern from "vsc/IModelVal.h" namespace "vsc":
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
cdef extern from "vsc/IRandomizer.h" namespace "vsc":
    cdef cppclass IRandomizer:
        bool randomize(
            const cpp_vector[IModelFieldP]       &fields,
            const cpp_vector[IModelConstraintP]  &constraints,
            bool                                 diagnose_failures)
    
#********************************************************************
#* IRandState
#********************************************************************
cdef extern from "vsc/IRandState.h" namespace "vsc":
    cdef cppclass IRandState:
        int32_t randint32(int32_t, int32_t)
        void randbits(IModelVal *)
        
#********************************************************************
#* ISolverFactory
#********************************************************************
cdef extern from "vsc/ISolverFactory.h" namespace "vsc":
    cdef cppclass ISolverFactory:
        pass
        
#********************************************************************
#* ITask
#********************************************************************
cdef extern from "vsc/ITask.h" namespace "vsc":
    cdef cppclass ITask:
        void apply(IAccept *)
        
#********************************************************************
#* ITypeConstraint
#********************************************************************
cdef extern from "vsc/ITypeConstraint.h" namespace "vsc":
    cdef cppclass ITypeConstraint:
        pass
    
cdef extern from "vsc/ITypeConstraintExpr.h" namespace "vsc":
    cdef cppclass ITypeConstraintExpr(ITypeConstraint):
        ITypeExpr *expr() const
        
cdef extern from "vsc/ITypeConstraintScope.h" namespace "vsc":
    cdef cppclass ITypeConstraintScope(ITypeConstraint):
        void addConstraint(ITypeConstraint *)
        const cpp_vector[unique_ptr[ITypeConstraint]] &constraints() const
        
cdef extern from "vsc/ITypeConstraintBlock.h" namespace "vsc":
    cdef cppclass ITypeConstraintBlock(ITypeConstraintScope):
        const cpp_string &name() const
    
#********************************************************************
#* ITypeExpr
#********************************************************************

cdef extern from "vsc/ITypeExpr.h" namespace "vsc":
    cdef cppclass ITypeExpr:
        pass
    
cdef extern from "vsc/ITypeExprBin.h" namespace "vsc":
    cdef cppclass ITypeExprBin(ITypeExpr):
        ITypeExpr *lhs() const
        BinOp op() const
        ITypeExpr *rhs() const
    
cdef extern from "vsc/ITypeExprFieldRef.h" namespace "vsc":
    cdef enum TypeExprFieldRefElemKind:
        Root "vsc::TypeExprFieldRefElemKind::Root" 
        IdxOffset "vsc::TypeExprFieldRefElemKind::IdxOffset" 
        
    cdef cppclass TypeExprFieldRefElem:
        TypeExprFieldRefElemKind        kind
        int32_t                         idx

    cdef cppclass ITypeExprFieldRef(ITypeExpr):
        void addIdxRef(int32_t)
        void addRootRef()
        uint32_t size() const
        const TypeExprFieldRefElem &at(int32_t) const

cdef extern from "vsc/ITypeExprVal.h" namespace "vsc":

    cdef cppclass ITypeExprVal(ITypeExpr):
        
        const IModelVal *val() const

#********************************************************************
#* ITypeField
#********************************************************************
cdef extern from "vsc/ITypeField.h" namespace "vsc":
    cdef enum TypeFieldAttr:
        NoAttr        "vsc::TypeFieldAttr::NoAttr"
        Rand          "vsc::TypeFieldAttr::Rand"
    
    cdef cppclass ITypeField:
        IDataTypeStruct *getParent()
        void setParent(IDataTypeStruct *)
        const cpp_string &name() const
        IDataType *getDataType() const
        TypeFieldAttr getAttr() const
        IModelVal *getInit() const

#********************************************************************
#* IVisitor
#********************************************************************
cdef extern from "vsc/IVisitor.h" namespace "vsc":
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
cdef extern from "vsc/IVsc.h" namespace "vsc":
    cdef cppclass IVsc:
        pass

#********************************************************************
#* py_get_vsc
#********************************************************************
cdef extern IVsc *py_get_vsc(const char *path)
#cdef extern from "py_get_vsc.h":
    
