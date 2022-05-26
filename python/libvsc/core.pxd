
from libvsc cimport decl
from libc.stdint cimport intptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
from libcpp.vector cimport vector as cpp_vector
from enum import IntFlag, IntEnum
cimport cpython.ref as cpy_ref

cdef class Vsc(object):
    cdef decl.IVsc              *_hndl
    
    cpdef Context mkContext(self)
   
cdef class Context(object):
    cdef decl.IContext               *_hndl
    cdef bool                        _owned

    cpdef ModelField buildModelField(self, DataTypeStruct, name=*)
    cpdef mkCompoundSolver(self)
    cpdef mkModelConstraintBlock(self, name)
    cpdef mkModelConstraintExpr(self, ModelExpr)
    cpdef bool addDataTypeInt(self, DataTypeInt)
    cpdef DataTypeInt findDataTypeInt(self, bool is_signed, int width)
    cpdef DataTypeInt mkDataTypeInt(self, bool is_signed, int width)
    cpdef bool addDataTypeStruct(self, DataTypeStruct)
    cpdef DataTypeStruct findDataTypeStruct(self, name)
    cpdef DataTypeStruct mkDataTypeStruct(self, name)
    cpdef mkModelExprBin(self, ModelExpr, op, ModelExpr)
    cpdef mkModelExprFieldRef(self, ModelField field)
    cpdef mkModelExprVal(self, ModelVal)
    cpdef mkModelFieldRoot(self, DataType type, name)
    cpdef mkModelVal(self)
    cpdef mkRandState(self, uint32_t seed)
    cpdef mkRandomizer(self, SolverFactory, RandState)
    cpdef TypeConstraintBlock mkTypeConstraintBlock(self, name)
    cpdef TypeConstraintExpr mkTypeConstraintExpr(self, TypeExpr)
    cpdef TypeConstraintScope mkTypeConstraintScope(self)
    cpdef TypeExprBin mkTypeExprBin(self, TypeExpr, op, TypeExpr)
    cpdef TypeExprFieldRef mkTypeExprFieldRef(self)
    cpdef TypeExprVal mkTypeExprVal(self, ModelVal)
    cpdef TypeFieldPhy mkTypeFieldPhy(self, name, DataType, attr, ModelVal)
    cpdef TypeFieldRef mkTypeFieldRef(self, name, DataType, attr)

    @staticmethod    
    cdef mk(decl.IContext *hndl, bool owned=*)

    
cdef class CompoundSolver(object):
    cdef decl.ICompoundSolver   *_hndl
    
    cpdef solve(self, RandState, fields, constraints, flags)
    
    @staticmethod
    cdef mk(decl.ICompoundSolver *)
    
cdef class Accept(object):
    cdef decl.IAccept *hndl(self)
    
cdef class DataType(object):
    cdef decl.IDataType         *_hndl
    cdef bool                   _owned
    
#    cdef decl.IAccept *hndl(self)
    
    @staticmethod
    cdef mk(decl.IDataType *, bool owned=*)

cdef class DataTypeInt(DataType):

    @staticmethod
    cdef mk(decl.IDataTypeInt *, bool owned=*)
    
    cdef decl.IDataTypeInt *asTypeInt(self)
    
cdef class DataTypeStruct(DataType):

    cpdef name(self)
    cpdef addField(self, TypeField f)
    cpdef getFields(self)
    cpdef TypeField getField(self, int32_t idx)
    cpdef addConstraint(self, TypeConstraint c)
    cpdef getConstraints(self)
    cpdef setCreateHook(self, hook_f)

    @staticmethod
    cdef mk(decl.IDataTypeStruct *, bool owned=*)

    cdef decl.IDataTypeStruct *asTypeStruct(self)
    
cdef class ModelConstraint(object):
    cdef decl.IModelConstraint   *_hndl
    cdef bool                    _owned
    
    @staticmethod
    cdef mk(decl.IModelConstraint *hndl, bool owned=*)
    
cdef class ModelConstraintScope(ModelConstraint):
    cpdef constraints(self)
    cpdef addConstraint(self, ModelConstraint)
    
    cdef decl.IModelConstraintScope *asModelConstraintScope(self)
    
cdef class ModelConstraintBlock(ModelConstraintScope):
    cpdef name(self)
    
    cdef decl.IModelConstraintBlock *asModelConstraintBlock(self)
    
    @staticmethod
    cdef mk(decl.IModelConstraintBlock *hndl, bool owned=*)
    
   
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
    
cdef class ModelExprVal(ModelExpr):

    cpdef width(self)
    cpdef val(self)
    
    cdef decl.IModelExprVal *asModelExprVal(self)
    
    @staticmethod
    cdef mk(decl.IModelExprVal *, bool owned=*)

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
    cpdef ModelField getField(self, int32_t idx)
    cpdef val(self)
    
    cpdef clearFlag(self, flags)
    cpdef setFlag(self, flags)
    cpdef isFlagSet(self, flags)
    cpdef setFieldData(self, data)
    cpdef getFieldData(self)

    @staticmethod
    cdef mk(decl.IModelField *, bool owned=*)
    
cdef class ModelFieldRoot(ModelField):

    cpdef setName(self, name)

    cdef decl.IModelFieldRoot *asRoot(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldRoot *, bool owned=*)
    
cdef class ModelFieldDataClosure(object):
    cdef decl.IModelFieldData       *_hndl
    
    cpdef getData(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldData *)

cdef class ModelVal(object):
    cdef decl.IModelVal         *_hndl
    cdef bool                   _owned

    cpdef bits(self)
    cpdef setBits(self, b)
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
    
cdef class Task(object):
    cdef decl.ITask             *_hndl
    
    cpdef apply(self, Accept it)
    
cdef class TypeConstraint(object):
    cdef decl.ITypeConstraint   *_hndl
    cdef bool                   _owned
    
    @staticmethod
    cdef TypeConstraint mk(decl.ITypeConstraint *, bool owned=*)

cdef class TypeConstraintExpr(TypeConstraint):

    cpdef TypeExpr expr(self)

    cdef decl.ITypeConstraintExpr *asExpr(self)

    @staticmethod
    cdef TypeConstraintExpr mk(decl.ITypeConstraint *, bool owned=*)
   
cdef class TypeConstraintScope(TypeConstraint):
    
    cpdef addConstraint(self, TypeConstraint)
    
    cdef decl.ITypeConstraintScope *asScope(self)
    
    @staticmethod
    cdef TypeConstraintScope mk(decl.ITypeConstraintScope *, bool owned=*)
    
cdef class TypeConstraintBlock(TypeConstraintScope):
    
    cpdef name(self)
    
    cdef decl.ITypeConstraintBlock *asBlock(self)
    
    @staticmethod
    cdef TypeConstraintBlock mk(decl.ITypeConstraintBlock *, bool owned=*)

cdef class TypeExpr(object):
    cdef decl.ITypeExpr         *_hndl
    cdef bool                   _owned
    
    @staticmethod
    cdef TypeExpr mk(decl.ITypeExpr *hndl, bool owned=*)
    
cdef class TypeExprFieldRefElem(object):
    cdef const decl.TypeExprFieldRefElem   *_hndl

    cpdef getKind(self)
    cpdef int32_t getIdx(self)

cdef class TypeExprBin(TypeExpr):

    cpdef TypeExpr lhs(self)
    cpdef op(self)
    cpdef TypeExpr rhs(self)

    cdef decl.ITypeExprBin *asBin(self)
        
    @staticmethod
    cdef TypeExprBin mk(decl.ITypeExprBin *hndl, bool owned=*)    

cdef class TypeExprFieldRef(TypeExpr):

    cpdef addIdxRef(self, int32_t idx)
    cpdef addRootRef(self)
    cpdef uint32_t size(self)
    cpdef TypeExprFieldRefElem at(self, idx)
    
    cdef decl.ITypeExprFieldRef *asFieldRef(self)
    
    @staticmethod
    cdef TypeExprFieldRef mk(decl.ITypeExprFieldRef *hndl, bool owned=*)
    
cdef class TypeExprVal(TypeExpr):
    cpdef ModelVal val(self)
    
    cdef decl.ITypeExprVal *asVal(self)
    
    @staticmethod
    cdef TypeExprVal mk(decl.ITypeExprVal *hndl, bool owned=*)
    
cdef class TypeField(object):
    cdef decl.ITypeField        *_hndl
    cdef bool                   _owned
    
    cpdef DataTypeStruct getParent(self)
    cpdef setParent(self, DataTypeStruct)
    cpdef name(self)
    cpdef DataType getDataType(self)
    cpdef getAttr(self)

    @staticmethod
    cdef mk(decl.ITypeField *, bool owned=*)

cdef class TypeFieldPhy(TypeField):

    cpdef ModelVal getInit(self)
    
    cdef decl.ITypeFieldPhy *asPhy(self)
    
    @staticmethod
    cdef mk(decl.ITypeFieldPhy *, bool owned=*)

cdef class TypeFieldRef(TypeField):

    @staticmethod
    cdef mk(decl.ITypeFieldRef *, bool owned=*)    
    
cdef class VisitorBase(object):
    cdef decl.VisitorProxy      *_proxy
    
    cpdef visitModelExprBin(self, ModelExprBin e)