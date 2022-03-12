#*****************************************************************************
#* decl.pxd
#*****************************************************************************
from libcpp.pair cimport pair as cpp_pair
from libcpp.set cimport set as cpp_set
from libcpp.string cimport string as cpp_string
from libcpp.vector cimport vector as cpp_vector
from libc.stdint cimport intptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
cimport cpython.ref as cpy_ref

#********************************************************************
#* IAccept
#********************************************************************
cdef extern from "vsc/IAccept.h" namespace "vsc":
    cdef cppclass IAccept:
        void accept(IVisitor *)

#********************************************************************
#* IModelExpr
#********************************************************************
cdef extern from "vsc/IModelExpr.h" namespace "vsc":
    cdef cppclass IModelExpr(IAccept):
        pass
    
cdef extern from "vsc/IModelExprBin.h" namespace "vsc":
    cdef cppclass IModelExprBin(IModelExpr):
        pass


#********************************************************************
#* IModelVal
#********************************************************************
cdef extern from "vsc/IModelVal.h" namespace "vsc":
    cdef cppclass IModelVal:
    
        uint32_t bits() const
        int64_t val_i() const
    
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
    