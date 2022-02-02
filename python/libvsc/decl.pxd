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
#* IModelVal
#********************************************************************
cdef extern from "vsc/IModelVal.h" namespace "vsc":
    cdef cppclass IModelVal:
    
        uint32_t bits() const
        int64_t val_i() const
    
    