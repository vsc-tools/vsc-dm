
from libvsc cimport decl
from libc.stdint cimport intptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
from libcpp.vector cimport vector as cpp_vector
from enum import IntFlag
cimport cpython.ref as cpy_ref

cdef class Vsc(object):
    cdef decl.IVsc              *_hndl
    
    cdef decl.IContext *mkContext(self)
   
cdef class Context(object):
    cdef decl.IContext               *_hndl

    cpdef mkModelConstraintExpr(self, ModelExpr)
    cpdef mkDataTypeInt(self, bool is_signed, int width)
    cpdef mkModelExprBin(self, ModelExpr, op, ModelExpr)
    cpdef mkModelExprFieldRef(self, ModelField field)
    cpdef mkModelFieldRoot(self, DataType type, name)
    cpdef mkRandState(self, uint32_t seed)
    cpdef mkRandomizer(self, SolverFactory, RandState)
    
cdef class DataType(object):
    cdef decl.IDataType         *_hndl
    
    @staticmethod
    cdef mk(decl.IDataType *, owned=*)

cdef class DataTypeInt(DataType):

    @staticmethod
    cdef mk(decl.IDataTypeInt *, owned=*)
    
    cdef decl.IDataTypeInt *asTypeInt(self)
    
cdef class ModelConstraint(object):
    cdef decl.IModelConstraint   *_hndl
    cdef bool                    _owned
    
    @staticmethod
    cdef mk(decl.IModelConstraint *hndl, bool owned=*)
   
cdef class ModelConstraintExpr(ModelConstraint):

    cpdef expr(self)

    cdef decl.IModelConstraintExpr *asModelConstraintExpr(self)
    @staticmethod
    cdef mk(decl.IModelConstraintExpr *, bool owned=*)
    
cdef class ModelExpr(object):
    cdef decl.IModelExpr         *_hndl
    cdef bool                    _owned
    
    cpdef accept(self, VisitorBase v)
    
    @staticmethod
    cdef mk(decl.IModelExpr *e, bool owned=*)

cdef class ModelExprBin(ModelExpr):

    @staticmethod
    cdef mkWrapper(decl.IModelExprBin *e)
    cdef decl.IModelExprBin *asExprBin(self)
    
cdef class ModelExprFieldRef(ModelExpr):

    cpdef field(self)

    cdef decl.IModelExprFieldRef *asExprFieldRef(self)
    
    @staticmethod
    cdef mk(decl.IModelExprFieldRef *, bool owned=*)

cdef class ModelField(object):
    cdef decl.IModelField       *_hndl
    cdef bool                   _owned
    
    cpdef name(self)
    cpdef getDataType(self)
    cpdef getParent(self)
    cpdef setParent(self, ModelField)
    cpdef constraints(self)
    cpdef addConstraint(self, ModelConstraint)
    cpdef fields(self)
    cpdef addField(self, ModelField)
    cpdef val(self)
    
    cpdef clearFlag(self, flags)
    cpdef setFlag(self, flags)
    cpdef isFlagSet(self, flags)

    @staticmethod
    cdef mk(decl.IModelField *, owned=*)

cdef class ModelVal(object):
    cdef decl.IModelVal         *_hndl
    cdef bool                   _owned

    cpdef bits(self)
    cpdef val_u(self)
    cpdef val_i(self)
    cpdef set_val_i(self, int64_t v, int32_t bits=*)
    cpdef set_val_u(self, uint64_t, int32_t bits=*)
    
    @staticmethod 
    cdef mk(decl.IModelVal *, owned=*)
    
cdef class Randomizer(object):
    cdef decl.IRandomizer      *_hndl
    
    cpdef randomize(self, list fields, list, bool)
    
    @staticmethod
    cdef mk(decl.IRandomizer *hndl)
    
cdef class RandState(object):
    cdef decl.IRandState       *_hndl
    
    cpdef randint32(self, int32_t, int32_t)
    cpdef randbits(self, ModelVal)
    
    @staticmethod
    cdef mk(decl.IRandState *)
    
cdef class SolverFactory(object):
    cdef decl.ISolverFactory    *_hndl
    
    
cdef class VisitorBase(object):
    cdef decl.VisitorProxy      *_proxy
    
    cpdef visitModelExprBin(self, ModelExprBin e)