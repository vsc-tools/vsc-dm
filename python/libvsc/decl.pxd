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

#********************************************************************
#* IContext
#********************************************************************
cdef extern from "vsc/IContext.h" namespace "vsc":
    cdef cppclass IContext:
   
        IModelConstraintExpr *mkModelConstraintExpr(IModelExpr *expr)
        IDataTypeInt *mkDataTypeInt(bool is_signed, int32_t width)
        IModelExprBin *mkModelExprBin(IModelExpr *, BinOp, IModelExpr *)
        IModelExprFieldRef *mkModelExprFieldRef(IModelField *field)
        IModelField *mkModelFieldRoot(IDataType *, const cpp_string &)
        IRandState *mkRandState(uint32_t)
        IRandomizer *mkRandomizer(ISolverFactory *, IRandState *)
    
#********************************************************************
#* IDataType
#********************************************************************
cdef extern from "vsc/IDataType.h" namespace "vsc":
    cdef cppclass IDataType:
        pass
    
cdef extern from "vsc/IDataTypeInt.h" namespace "vsc":
    cdef cppclass IDataTypeInt(IDataType):
        pass
    
ctypedef IDataTypeInt *IDataTypeIntP

#********************************************************************
#* IVsc
#********************************************************************
cdef extern from "vsc/IVsc.h" namespace "vsc":
    cdef cppclass IVsc:
        IContext *mkContext()
        pass
    
#********************************************************************
#* IAccept
#********************************************************************
cdef extern from "vsc/IAccept.h" namespace "vsc":
    cdef cppclass IAccept:
        void accept(IVisitor *)
        
#********************************************************************
#* IModelConstraint
#********************************************************************
ctypedef IModelConstraint *IModelConstraintP
cdef extern from "vsc/IModelConstraint.h" namespace "vsc":
    cdef cppclass IModelConstraint:
        pass
    
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
ctypedef IModelVal *IModelValP
ctypedef IModelField *IModelFieldP
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
        IModelValP val()
        
        void clearFlag(ModelFieldFlag flags)
        void setFlag(ModelFieldFlag flags)
        bool isFlagSet(ModelFieldFlag flags)
        
        pass
    
#********************************************************************
#* IModelVal
#********************************************************************
cdef extern from "vsc/IModelVal.h" namespace "vsc":
    cdef union val_t "IModelVal::val_t":
        uint64_t         v
        uint64_t        *vp
    cdef cppclass IModelVal:
    
        uint32_t bits() const
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
#* get_vsc
#********************************************************************
cdef extern from "vsc/loader.h":
    IVsc *get_vsc(const char *path)
    
