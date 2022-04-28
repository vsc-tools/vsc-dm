#****************************************************************************
#* libvsc.core
#****************************************************************************
import os
from enum import IntFlag, IntEnum
from ctypes import CDLL
from libvsc cimport decl
cimport cpython.ref as cpy_ref
from libc.stdint cimport intptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
from libcpp.cast cimport dynamic_cast
from libcpp.cast cimport static_cast
from libcpp.cast cimport const_cast
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr

_Context_inst = None

cdef class Context(object):

    def __dealloc__(self):
        if self._owned:
            del self._hndl
        
    cpdef ModelField buildModelField(self, DataTypeStruct dt, name=""):
        return ModelField.mk(
            self._hndl.buildModelField(dt.asTypeStruct(), name.encode()), True)
    
    cpdef mkCompoundSolver(self):
        return CompoundSolver.mk(self._hndl.mkCompoundSolver())
    
    cpdef bool addDataTypeInt(self, DataTypeInt t):
        t._owned = False
        return self._hndl.addDataTypeInt(t.asTypeInt())

    cpdef DataTypeInt findDataTypeInt(self, bool is_signed, int width):
        cdef decl.IDataTypeInt *i = self._hndl.findDataTypeInt(is_signed, width)
        
        if i != NULL:
            return DataTypeInt.mk(i, False)
        else:
            return None
        
    cpdef DataTypeInt mkDataTypeInt(self, bool is_signed, int width):
        return DataTypeInt.mk(self._hndl.mkDataTypeInt(is_signed, width), True)

    cpdef bool addDataTypeStruct(self, DataTypeStruct t):
        t._owned = False
        return self._hndl.addDataTypeStruct(t.asTypeStruct())
        
    cpdef DataTypeStruct findDataTypeStruct(self, name):
        cdef decl.IDataTypeStruct *t = self._hndl.findDataTypeStruct(name.encode())
        
        if t != NULL:
            return DataTypeStruct.mk(t, False)
        else:
            return None
            
    cpdef DataTypeStruct mkDataTypeStruct(self, name):
        return DataTypeStruct.mk(self._hndl.mkDataTypeStruct(name.encode()), True)
    
    cpdef mkModelConstraintBlock(self, name):
        return ModelConstraintBlock.mk(self._hndl.mkModelConstraintBlock(name.encode()))
    
    cpdef mkModelConstraintExpr(self, ModelExpr expr):
        expr._owned = False
        return ModelConstraintExpr.mk(self._hndl.mkModelConstraintExpr(expr._hndl))
    
    cpdef mkModelExprBin(self, 
            ModelExpr           lhs,
            op,
            ModelExpr           rhs):
        cdef int op_i = int(op)
        lhs._owned = False
        rhs._owned = False
        
        if lhs._hndl == NULL:
            raise Exception("lhs is NULL")
        if rhs._hndl == NULL:
            raise Exception("rhs is NULL")
        
        return ModelExprBin.mk(
            self._hndl.mkModelExprBin(
                lhs._hndl,
                <decl.BinOp>(op_i),
                rhs._hndl))
        
    cpdef mkModelExprFieldRef(self, ModelField field):
        return ModelExprFieldRef.mk(
            self._hndl.mkModelExprFieldRef(field._hndl))
        
    cpdef mkModelExprVal(self, ModelVal v):
        if v is not None:
            return ModelExprVal.mk(self._hndl.mkModelExprVal(v._hndl))
        else:
            return ModelExprVal.mk(self._hndl.mkModelExprVal(NULL))
    
    cpdef mkModelFieldRoot(self, DataType type, name):
        cdef decl.IDataType *type_h = NULL
        
        if type is not None:
            type_h = type._hndl
            
        return ModelField.mk(self._hndl.mkModelFieldRoot(
            type_h, 
            name.encode()),
            True)
        
    cpdef mkModelVal(self):
        return ModelVal.mk(self._hndl.mkModelVal(), True)
        
    cpdef mkRandState(self, uint32_t seed):
        return RandState.mk(self._hndl.mkRandState(seed))
    
    cpdef mkRandomizer(self, SolverFactory sf, RandState rs):
        cdef decl.ISolverFactory *sf_h = NULL
        
        if sf is not None:
            sf_h = sf._hndl
        
        return Randomizer.mk(self._hndl.mkRandomizer(
            sf_h,
            rs._hndl))
        
    cpdef TypeConstraintBlock mkTypeConstraintBlock(self, name):
        return TypeConstraintBlock.mk(self._hndl.mkTypeConstraintBlock(
            name.encode()), True)
        
    cpdef TypeConstraintExpr mkTypeConstraintExpr(self, TypeExpr e):
        e._owned = False
        return TypeConstraintExpr.mk(self._hndl.mkTypeConstraintExpr(
            e._hndl))
        
    cpdef TypeConstraintScope mkTypeConstraintScope(self):
        return TypeConstraintScope.mk(self._hndl.mkTypeConstraintScope())

    cpdef TypeExprBin mkTypeExprBin(self, TypeExpr lhs, op, TypeExpr rhs):
        cdef int op_i = int(op)
        lhs._owned = False
        rhs._owned = False
        return TypeExprBin.mk(self._hndl.mkTypeExprBin(
            lhs._hndl,
            <decl.BinOp>(op_i),
            rhs._hndl))
        
    cpdef TypeExprFieldRef mkTypeExprFieldRef(self):
        return TypeExprFieldRef.mk(self._hndl.mkTypeExprFieldRef(), True)
    
    cpdef TypeExprVal mkTypeExprVal(self, ModelVal v):
        if v is None:
            return TypeExprVal.mk(self._hndl.mkTypeExprVal(NULL), True)
        else:
            return TypeExprVal.mk(self._hndl.mkTypeExprVal(v._hndl), True)
        
    cpdef TypeField mkTypeField(self, 
                                name, 
                                DataType dtype, 
                                attr,
                                ModelVal init):
        cdef decl.IModelVal *init_h = NULL
        cdef int attr_i = int(attr)
        
        if init is not None:
            init_h = init._hndl
            
        return TypeField.mk(self._hndl.mkTypeField(
            name.encode(), 
            dtype._hndl, 
            <decl.TypeFieldAttr>(attr_i),
            init_h))
        
    @staticmethod
    cdef mk(decl.IContext *hndl, bool owned=True):
        ret = Context()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
    @staticmethod
    def inst():
        global _Context_inst
        if _Context_inst is None:
            _Context_inst = Context()
        return _Context_inst
    
class SolveFlags(IntFlag):
    Randomize            = decl.SolveFlags.Randomize
    RandomizeDeclRand    = decl.SolveFlags.RandomizeDeclRand
    RandomizeTopFields   = decl.SolveFlags.RandomizeTopFields
    DiagnoseFailures     = decl.SolveFlags.DiagnoseFailures
    
cdef class CompoundSolver(object):

    def __dealloc__(self):
        del self._hndl
    
    cpdef solve(self, RandState rs, fields, constraints, flags):
        cdef cpp_vector[decl.IModelFieldP] fields_v;
        cdef cpp_vector[decl.IModelConstraintP] constraints_v;
        cdef int flags_i = int(flags)
        cdef ModelField field_t
        cdef ModelConstraint constraint_t
        
        for f in fields:
            field_t = <ModelField>(f)
            fields_v.push_back(field_t._hndl)
            
        for c in constraints:
            constraint_t = <ModelConstraint>(c)
            constraints_v.push_back(constraint_t._hndl)
        
        return self._hndl.solve(
            rs._hndl,
            fields_v,
            constraints_v,
            <decl.SolveFlags>(flags_i))
        
    @staticmethod
    cdef mk(decl.ICompoundSolver *hndl):
        ret = CompoundSolver()
        ret._hndl = hndl
        return ret

cdef class Accept(object):

    cdef decl.IAccept *hndl(self):
        return NULL
            
    
cdef class DataType(object):

#    cdef decl.IAccept *hndl(self):
#        return self._hndl

    def __dealloc__(self):
        if self._owned:
            del self._hndl

    @staticmethod
    cdef mk(decl.IDataType *hndl, bool owned=True):
        ret = DataType()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    

cdef class DataTypeInt(DataType):
    
    @staticmethod
    cdef mk(decl.IDataTypeInt *hndl, bool owned=True):
        ret = DataTypeInt()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
    cdef decl.IDataTypeInt *asTypeInt(self):
        return dynamic_cast[decl.IDataTypeIntP](self._hndl)
    
cdef class DataTypeStruct(DataType):

    cpdef name(self):
        return self.asTypeStruct().name().decode()

    cpdef addField(self, TypeField f):
        f._owned = False
        self.asTypeStruct().addField(f._hndl)
        
    cpdef getFields(self):
        ret = []
        for i in range(self.asTypeStruct().getFields().size()):
            ret.append(TypeField.mk(
                self.asTypeStruct().getFields().at(i).get(), False))
        return ret
    
    cpdef TypeField getField(self, int32_t idx):
        cdef decl.ITypeField *ret_h = self.asTypeStruct().getField(idx)
        
        if ret_h != NULL:
            return TypeField.mk(ret_h, False)
        else:
            return None
    
    cpdef addConstraint(self, TypeConstraint c):
        self.asTypeStruct().addConstraint(c._hndl)
        pass
    
    cpdef getConstraints(self):
        ret = []
        for i in range(self.asTypeStruct().getConstraints().size()):
            ret.append(TypeConstraint.mk(
                self.asTypeStruct().getConstraints().at(i).get(), False))
        return ret
    
    cpdef setCreateHook(self, hook_f):
        cdef decl.ModelStructCreateHookClosure *closure = new decl.ModelStructCreateHookClosure(<cpy_ref.PyObject *>(hook_f))
        self.asTypeStruct().setCreateHook(closure)
    
    @staticmethod
    cdef mk(decl.IDataTypeStruct *hndl, bool owned=True):
        ret = DataTypeStruct()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
    cdef decl.IDataTypeStruct *asTypeStruct(self):
        return dynamic_cast[decl.IDataTypeStructP](self._hndl)
    
cdef public void model_struct_create_hook_closure_invoke(
    hook_f,
    decl.IModelField  *field_h) with gil:
    cdef ModelField field = ModelField.mk(field_h, False)
    hook_f(field)
    
cdef class ModelConstraint(object):

    def __dealloc__(self):
        if self._owned:
            del self._hndl
            
    @staticmethod
    cdef mk(decl.IModelConstraint *hndl, bool owned=True):
        ret = ModelConstraint()
        ret._hndl = hndl
        ret._owned = owned
        return ret

    pass

cdef class ModelConstraintScope(ModelConstraint):
    
    cpdef constraints(self):
        cdef const cpp_vector[unique_ptr[decl.IModelConstraint]] *cl = &self.asModelConstraintScope().constraints()
        ret = []
        
        for i in range(cl.size()):
            ret.append(ModelConstraint.mk(cl.at(i).get(), False))
        
        return ret
    
    cpdef addConstraint(self, ModelConstraint c):
        c._owned = False
        self.asModelConstraintScope().add_constraint(c._hndl)
    
    cdef decl.IModelConstraintScope *asModelConstraintScope(self):
        return <decl.IModelConstraintScope *>(self._hndl)
    

cdef class ModelConstraintBlock(ModelConstraintScope):

    cpdef name(self):
        return self.asModelConstraintBlock().name().decode()

    cdef decl.IModelConstraintBlock *asModelConstraintBlock(self):
        return <decl.IModelConstraintBlock *>(self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelConstraintBlock *hndl, bool owned=True):
        ret = ModelConstraintBlock()
        ret._hndl = hndl
        ret._owned = owned
        return ret


cdef class ModelConstraintExpr(ModelConstraint):

    cpdef expr(self):
        return ModelExpr.mk(self.asModelConstraintExpr().expr(), False)
    
    @staticmethod
    cdef mk(decl.IModelConstraintExpr *hndl, bool owned=True):
        ret = ModelConstraintExpr()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
    cdef decl.IModelConstraintExpr *asModelConstraintExpr(self):
        return <decl.IModelConstraintExpr *>(self._hndl)

cdef class ModelExpr(object):
    
    def __init__(self):
        pass
    
    cpdef accept(self, VisitorBase v):
        self._hndl.accept(v._proxy)
        pass

    @staticmethod
    cdef mk(decl.IModelExpr *e, bool owned=True):
        ret = ModelExpr()
        ret._owned = owned
        ret._hndl = e
        return ret
    
class BinOp(IntEnum):
    Eq      = decl.BinOp.Eq
    Ne      = decl.BinOp.Ne
    Gt      = decl.BinOp.Gt
    Ge      = decl.BinOp.Ge
    Lt      = decl.BinOp.Lt
    Le      = decl.BinOp.Le
    Add     = decl.BinOp.Add
    Sub     = decl.BinOp.Sub 
    Div     = decl.BinOp.Div
    Mul     = decl.BinOp.Mul
    Mod     = decl.BinOp.Mod
    BinAnd  = decl.BinOp.BinAnd
    BinOr   = decl.BinOp.BinOr
    LogAnd  = decl.BinOp.LogAnd
    LogOr   = decl.BinOp.LogOr
    Sll     = decl.BinOp.Sll
    Srl     = decl.BinOp.Srl
    Xor     = decl.BinOp.Xor
    Not     = decl.BinOp.Not
    
cdef class ModelExprBin(ModelExpr):
    
    @staticmethod
    cdef mkWrapper(decl.IModelExprBin *e):
        ret = ModelExprBin()
        ret._owned = False
        ret._hndl = e
        return ret
    
    cdef decl.IModelExprBin *asExprBin(self):
        return <decl.IModelExprBin *>(self._hndl)
    
cdef class ModelExprFieldRef(ModelExpr):

    cpdef field(self):
        return ModelField.mk(self.asExprFieldRef().field(), False)
    
    cdef decl.IModelExprFieldRef *asExprFieldRef(self):
        return <decl.IModelExprFieldRef *>(self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelExprFieldRef *hndl, bool owned=True):
        ret = ModelExprFieldRef()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class ModelExprVal(ModelExpr):
    
    cpdef width(self):
        return self.asModelExprVal().width()
        
    cpdef val(self):
        return ModelVal.mk(self.asModelExprVal().val(), False)
    
    cdef decl.IModelExprVal *asModelExprVal(self):
        return <decl.IModelExprVal *>(self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelExprVal *hndl, bool owned=True):
        ret = ModelExprVal()
        ret._hndl = hndl
        ret._owned = owned
        return ret

class ModelFieldFlag(IntFlag):
    NoFlags  = decl.ModelFieldFlag.NoFlags
    DeclRand = decl.ModelFieldFlag.DeclRand
    UsedRand = decl.ModelFieldFlag.UsedRand
    Resolved = decl.ModelFieldFlag.Resolved
    VecSize  = decl.ModelFieldFlag.VecSize
    
cdef class ModelField(object):

    def __dealloc__(self):
        if self._owned:
            print("Delete field %s" % self.name())
            del self._hndl

    cpdef name(self):
        return self._hndl.name().decode()
    
    cpdef getDataType(self):
        return DataType.mk(self._hndl.getDataType(), False)
    
    cpdef getParent(self):
        return ModelField.mk(self._hndl.getParent(), False)
    
    cpdef setParent(self, ModelField parent):
        self._hndl.setParent(parent._hndl)
        
    cpdef constraints(self):
        cdef const cpp_vector[unique_ptr[decl.IModelConstraint]] *constraints_l = &self._hndl.constraints()
        ret = []
        
        for i in range(constraints_l.size()):
            ret.append(ModelConstraint.mk(constraints_l.at(i).get(), False))
            
        return ret
        
    cpdef addConstraint(self, ModelConstraint c):
        c._owned = False
        self._hndl.addConstraint(c._hndl)

    cpdef fields(self):
        cdef const cpp_vector[decl.IModelFieldUP] *fields_l = &self._hndl.fields()
        ret = []
        for i in range(fields_l.size()):
            ret.append(ModelField.mk(fields_l.at(i).get()))
        return ret
        
    cpdef addField(self, ModelField f):
        if not f._owned:
            raise Exception("Cannot add a field already owned by another composite")
        
        # We're taking ownership of the field
        f._owned = False
        self._hndl.addField(f._hndl)
        
    cpdef ModelField getField(self, int32_t idx):
        cdef decl.IModelField *field = self._hndl.getField(idx)
        
        if field != NULL:
            return ModelField.mk(field, False)
        else:
            return None
        
    cpdef val(self):
        return ModelVal.mk(self._hndl.val(), False)
    
    cpdef clearFlag(self, flags):
        cdef int flags_i = flags
        self._hndl.clearFlag(<decl.ModelFieldFlag>(flags_i))
    
    cpdef setFlag(self, flags):
        cdef int flags_i = flags
        self._hndl.setFlag(<decl.ModelFieldFlag>(flags_i))
    
    cpdef isFlagSet(self, flags):
        cdef int flags_i = flags
        return self._hndl.isFlagSet(<decl.ModelFieldFlag>(flags_i))
        
    
    @staticmethod
    cdef mk(decl.IModelField *hndl, owned=True):
        ret = ModelField()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelVal(object):

    def __dealloc__(self):
        if self._owned and self._hndl != NULL:
            del self._hndl

    cpdef bits(self):
        return self._hndl.bits()
    
    cpdef setBits(self, b):
        self._hndl.setBits(b)
    
    cpdef val_u(self):
        if self._hndl.bits() <= 64:
            return self._hndl.val_u()
        else:
            raise Exception("TODO: handle >64 size")
    
    cpdef val_i(self):
        if self._hndl.bits() <= 64:
            return self._hndl.val_i()
        else:
            raise Exception("TODO: handle >64 size")
        
    cpdef set_val_i(self, int64_t v, int32_t bits=-1):
        self._hndl.set_val_i(v, bits)
        
    cpdef set_val_u(self, uint64_t v, int32_t bits=-1):
        self._hndl.set_val_u(v, bits)
    
    @staticmethod
    cdef mk(decl.IModelVal *hndl, owned=False):
        ret = ModelVal()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class Randomizer(object):

    def __dealloc__(self):
        del self._hndl
        
    cpdef randomize(
        self,
        list        fields,
        list        constraints,
        bool        diagnose_failures):
        cdef ModelField fcd
        cdef ModelConstraint ccd
        cdef cpp_vector[decl.IModelFieldP]      fields_v;
        cdef cpp_vector[decl.IModelConstraintP] constraints_v;
        
        for f in fields:
            fcd = <ModelField>(f)
            fields_v.push_back(fcd._hndl)
            
        for c in constraints:
            ccd = <ModelConstraint>(c)
            constraints_v.push_back(ccd._hndl)
            
        self._hndl.randomize(
            fields_v,
            constraints_v,
            diagnose_failures)
            
        pass
    
    @staticmethod
    cdef mk(decl.IRandomizer *hndl): 
        ret = Randomizer()
        ret._hndl = hndl
        return ret
    
cdef class RandState(object):

    def __dealloc__(self):
        del self._hndl
        
    cpdef randint32(self, int32_t low, int32_t high):
        return self._hndl.randint32(low, high)
    
    cpdef randbits(self, ModelVal v):
        return self._hndl.randbits(v._hndl)
    
    @staticmethod
    cdef mk(decl.IRandState *hndl):
        ret = RandState()
        ret._hndl = hndl 
        return ret
    
#********************************************************************
#* SolverFactory
#********************************************************************
cdef class SolverFactory(object):

    def __dealloc__(self):
        del self._hndl
        
cdef class TypeConstraint(object):

    @staticmethod
    cdef TypeConstraint mk(decl.ITypeConstraint *hndl, bool owned=True):
        ret = TypeConstraint()
        ret._hndl = hndl
        ret._owned = owned
        return ret
        
    pass

cdef class TypeConstraintExpr(TypeConstraint):

    cpdef TypeExpr expr(self):
        return TypeExpr.mk(self.asExpr().expr())

    cdef decl.ITypeConstraintExpr *asExpr(self):
        return dynamic_cast[decl.ITypeConstraintExprP](self._hndl)

    @staticmethod
    cdef TypeConstraintExpr mk(decl.ITypeConstraintExpr *hndl, bool owned=True):
        ret = TypeConstraintExpr()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class TypeConstraintScope(TypeConstraint):
    
    cpdef addConstraint(self, TypeConstraint c):
        c._owned = False
        self.asScope().addConstraint(c._hndl)
    
    cdef decl.ITypeConstraintScope *asScope(self):
        return dynamic_cast[decl.ITypeConstraintScopeP](self._hndl)
    
    @staticmethod
    cdef TypeConstraintScope mk(decl.ITypeConstraintScope *hndl, bool owned=True):
        ret = TypeConstraintScope()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeConstraintBlock(TypeConstraintScope):
    
    cpdef name(self):
        return self.asBlock().name().decode()
    
    cdef decl.ITypeConstraintBlock *asBlock(self):
        return dynamic_cast[decl.ITypeConstraintBlockP](self._hndl)
    
    @staticmethod
    cdef TypeConstraintBlock mk(decl.ITypeConstraintBlock *hndl, bool owned=True):
        ret = TypeConstraintBlock()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
#********************************************************************
#* TypeExpr
#********************************************************************

cdef class TypeExpr(object):
    
    def __dealloc__(self):
        if self._owned:
            del self._hndl
            
    @staticmethod
    cdef TypeExpr mk(decl.ITypeExpr *hndl, bool owned=True):
        ret = TypeExpr()
        ret._hndl = hndl
        ret._owned = owned
        return ret
            
class TypeExprFieldRefElemKind(IntEnum):
    Root = decl.TypeExprFieldRefElemKind.Root
    IdxOffset = decl.TypeExprFieldRefElemKind.IdxOffset

cdef class TypeExprFieldRefElem(object):

    cpdef getKind(self):
        cdef int kind_i = int(self._hndl.kind)
        return TypeExprFieldRefElemKind(kind_i)

    cpdef int32_t getIdx(self):
        return self._hndl.idx
    
cdef class TypeExprBin(TypeExpr):
    
    cpdef TypeExpr lhs(self):
        return TypeExpr.mk(self.asBin().lhs(), False)
    
    cpdef op(self):
        cdef int op_i = <int>(self.asBin().op())
        return BinOp(op_i)
    
    cpdef TypeExpr rhs(self):
        return TypeExpr.mk(self.asBin().rhs(), False)

    cdef decl.ITypeExprBin *asBin(self):
        return dynamic_cast[decl.ITypeExprBinP](self._hndl)
        
    @staticmethod
    cdef TypeExprBin mk(decl.ITypeExprBin *hndl, bool owned=True):
        ret = TypeExprBin()
        ret._hndl = hndl
        ret._owned = owned
        return ret    
    
cdef class TypeExprFieldRef(TypeExpr):

    cpdef addIdxRef(self, int32_t idx):
        self.asFieldRef().addIdxRef(idx)
        
    cpdef addRootRef(self):
        self.asFieldRef().addRootRef()
        
    cpdef uint32_t size(self):
        return self.asFieldRef().size()
    
    cpdef TypeExprFieldRefElem at(self, idx):
        cdef const decl.TypeExprFieldRefElem *elem = &self.asFieldRef().at(idx)
        ret = TypeExprFieldRefElem()
        ret._hndl = elem
        return ret
    
    @staticmethod
    cdef TypeExprFieldRef mk(decl.ITypeExprFieldRef *hndl, bool owned=True):
        ret = TypeExprFieldRef()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
    cdef decl.ITypeExprFieldRef *asFieldRef(self):
        return dynamic_cast[decl.ITypeExprFieldRefP](self._hndl)

cdef class TypeExprVal(TypeExpr):
    cpdef ModelVal val(self):
        return ModelVal.mk(
            const_cast[decl.IModelValP](self.asVal().val()), 
            False)
    
    cdef decl.ITypeExprVal *asVal(self):
        return dynamic_cast[decl.ITypeExprValP](self._hndl)
    
    @staticmethod
    cdef TypeExprVal mk(decl.ITypeExprVal *hndl, bool owned=True):
        ret = TypeExprVal()
        ret._hndl = hndl
        ret._owned = owned
        return ret

#********************************************************************
#* TypeField
#********************************************************************

class TypeFieldAttr(IntFlag):
    NoAttr = decl.TypeFieldAttr.NoAttr
    Rand = decl.TypeFieldAttr.Rand
    
cdef class TypeField(object):

    def __dealloc__(self):
        if self._owned:
            del self._hndl
            
    cpdef DataTypeStruct getParent(self):
        cdef decl.IDataTypeStruct *p = self._hndl.getParent()
        if p != NULL:
            return DataTypeStruct.mk(p, False)
        else:
            return None

    cpdef setParent(self, DataTypeStruct p):
        self._hndl.setParent(p.asTypeStruct())
        
    cpdef name(self):
        return self._hndl.name().decode()
    
    cpdef DataType getDataType(self):
        cdef decl.IDataType *t = self._hndl.getDataType()
        if t != NULL:
            return DataType.mk(t, False)
        else:
            return None
        
    cpdef getAttr(self):
        return 0
    
    cpdef ModelVal getInit(self):
        cdef decl.IModelVal *i = self._hndl.getInit()
        
        if i != NULL:
            return ModelVal.mk(i, False)
        else:
            return None

    @staticmethod
    cdef mk(decl.ITypeField *hndl, owned=True):
        ret = TypeField()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
    
#********************************************************************
#* Task
#********************************************************************
cdef class Task(object):
    cpdef apply(self, Accept it):
        pass
    

#********************************************************************
#* VisitorBase
#********************************************************************
cdef class VisitorBase(object):

    def __init__(self):
        _proxy = new decl.VisitorProxy(<cpy_ref.PyObject *>(self))
        
    cpdef visitModelExprBin(self, ModelExprBin e):
        self._proxy.visitModelExprBinBase(e.asExprBin())
        
cdef public void VisitorProxy_visitModelExprBin(obj, decl.IModelExprBin *e) with gil:
    obj.visitModelExprBin(ModelExprBin.mkWrapper(e))
        
#********************************************************************
#* Vsc
#********************************************************************
cdef Vsc _Vsc_inst = None
cdef class Vsc(object):
    
    def __init__(self):
        path = "abc"
        print("core file: %s" % str(os.path.abspath(__file__)))
        paths = []
        paths_s = set()
        # These are libraries that we know are pointless to search
        excludes = ['libgcc', 'libstdc++', 'libc', 'libdl', 'libz', 'libm', 'libutil', 'libpthread', 'ld-', 'libpython']
        with open("/proc/%d/maps" % os.getpid(), "r") as fp:
            while True:
                line = fp.readline()
                
                if not line:
                    break
               
                line = line.strip()

                idx = line.find('/')
                if idx != -1:                
                    path = line[idx:]
                    
                    if not os.path.isfile(path):
                        # File doesn't exist, which probably means that
                        # the path wraps around to the next line
                        line = fp.readline().strip()
                        
                        path += line
                        
                    if path.rfind('.so') != -1:
                        if path not in paths_s:
                            exclude = False
                            for e in excludes:
                                if path.find(e) != -1:
                                    exclude = True
                                    break

                            paths_s.add(path)
                            if not exclude:                                
                                paths.append(path)

        print("Paths: %s" % str(paths))
        
        lib_path = None
        
        for p in filter(lambda x : x.find('vsc') != -1, paths):
            lib = CDLL(p)
            try:
                getattr(lib, 'ivsc')
                lib_path = p
                print("Found ivsc")
                break
            except Exception as e:
                pass
            
        if lib_path is None:
            for p in filter(lambda x : x.find('vsc') == -1, paths):
                lib = CDLL(p)
                try:
                    getattr(lib, 'ivsc')
                    lib_path = p
                    print("Found ivsc")
                    break
                except Exception as e:
                    pass

        # Nothing already loaded provides tblink, so load the core library
        if lib_path is None:
            lib_dir = os.path.dirname(os.path.abspath(__file__))
            lib_path = os.path.join(lib_dir, "libvsc.so")
            
        print("lib_path: %s" % lib_path)
        self._hndl = decl.py_get_vsc(lib_path.encode())
        
        if self._hndl == NULL:
            raise Exception("Failed to load libvsc core library")
        
    cpdef Context mkContext(self):
        return Context.mk(self._hndl.mkContext(), True)
    
    @staticmethod
    def inst():
        global _Vsc_inst
        
        if _Vsc_inst is None:
            _Vsc_inst = Vsc()
        return _Vsc_inst
        
