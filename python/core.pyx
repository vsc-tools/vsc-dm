#****************************************************************************
#* libvsc.core
#****************************************************************************
from libvsc cimport decl
import os
from ctypes import CDLL
cimport cpython.ref as cpy_ref
from libc.stdint cimport intptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
from libcpp.cast cimport dynamic_cast
from libcpp.cast cimport static_cast
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr
from enum import IntFlag, IntEnum


_Context_inst = None

cdef class Context(object):
#    cdef decl.IContext               *_hndl

    def __cinit__(self):
        vsc = Vsc_inst()
        self._hndl = vsc.mkContext()

    def __init__(self):
        pass
    
    def __dealloc__(self):
        del self._hndl

    cpdef mkDataTypeInt(self, bool is_signed, int width):
        return DataTypeInt.mk(self._hndl.mkDataTypeInt(is_signed, width))
    
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
        return ModelExprBin.mk(
            self._hndl.mkModelExprBin(
                lhs._hndl,
                <decl.BinOp>(op_i),
                rhs._hndl))
        
    cpdef mkModelExprFieldRef(self, ModelField field):
        return ModelExprFieldRef.mk(
            self._hndl.mkModelExprFieldRef(field._hndl))
    
    cpdef mkModelFieldRoot(self, DataType type, name):
        cdef decl.IDataType *type_h = NULL
        
        if type is not None:
            type_h = type._hndl
            
        return ModelField.mk(self._hndl.mkModelFieldRoot(
            type_h, 
            name.encode()),
            True)
        
    cpdef mkRandState(self, uint32_t seed):
        return RandState.mk(self._hndl.mkRandState(seed))
    
    cpdef mkRandomizer(self, SolverFactory sf, RandState rs):
        cdef decl.ISolverFactory *sf_h = NULL
        
        if sf is not None:
            sf_h = sf._hndl
        
        return Randomizer.mk(self._hndl.mkRandomizer(
            sf_h,
            rs._hndl))
    
    
    @staticmethod
    def inst():
        global _Context_inst
        if _Context_inst is None:
            _Context_inst = Context()
        return _Context_inst
    
cdef class DataType(object):

    @staticmethod
    cdef mk(decl.IDataType *hndl, owned=True):
        ret = DataType()
        ret._hndl = hndl
        return ret
    

cdef class DataTypeInt(object):
    
    @staticmethod
    cdef mk(decl.IDataTypeInt *hndl, owned=True):
        ret = DataTypeInt()
        ret._hndl = hndl
        return ret
    
    cdef decl.IDataTypeInt *asTypeInt(self):
        return dynamic_cast[decl.IDataTypeIntP](self._hndl)
    
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
    
class ModelFieldFlag(IntFlag):
    NoFlags  = decl.ModelFieldFlag.NoFlags
    DeclRand = decl.ModelFieldFlag.DeclRand
    UsedRand = decl.ModelFieldFlag.UsedRand
    Resolved = decl.ModelFieldFlag.Resolved
    VecSize  = decl.ModelFieldFlag.VecSize
    
cdef class ModelField(object):

    def __dealloc__(self):
        if not self._owned:
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
        self._hndl = decl.get_vsc(lib_path.encode())
        
        if self._hndl == NULL:
            raise Exception("Failed to load libvsc core library")
        
    cdef decl.IContext *mkContext(self):
        return self._hndl.mkContext()
        
cdef Vsc _Vsc_inst = None
cdef Vsc Vsc_inst():
    global _Vsc_inst
    if _Vsc_inst is None:
        _Vsc_inst = Vsc()
    return _Vsc_inst
    
