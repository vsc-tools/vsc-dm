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
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr


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
    
    cpdef mkModelFieldRoot(self, DataType type, name):
        return ModelField.mk(self._hndl.mkModelFieldRoot(
            type._hndl, 
            name.encode()))
    
    
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

cdef class ModelExpr(object):
    
    def __init__(self):
        pass
    
    cpdef accept(self, VisitorBase v):
        self._hndl.accept(v._proxy)
        pass

    @staticmethod
    cdef mkWrapper(decl.IModelExpr *e):
        ret = ModelExpr()
        ret._owned = False
        ret._hndl = e
        return ret
    
cdef class ModelExprBin(ModelExpr):
    
    @staticmethod
    cdef mkWrapper(decl.IModelExprBin *e):
        ret = ModelExprBin()
        ret._owned = False
        ret._hndl = e
        return ret
    
    cdef decl.IModelExprBin *asExprBin(self):
        return <decl.IModelExprBin *>(self._hndl)
    
cdef class ModelField(object):

    cpdef name(self):
        return self._hndl.name().decode()
    
    cpdef getDataType(self):
        return DataType.mk(self._hndl.getDataType(), False)
    
    cpdef getParent(self):
        return ModelField.mk(self._hndl.getParent(), False)
    
    cpdef setParent(self, ModelField parent):
        self._hndl.setParent(parent._hndl)
        
    cpdef fields(self):
        cdef const cpp_vector[decl.IModelFieldUP] *fields_l = &self._hndl.fields()
        ret = []
        for i in range(fields_l.size()):
            ret.append(ModelField.mk(fields_l.at(i).get()))
        return ret
        
    cpdef addField(self, ModelField f):
        self._hndl.addField(f._hndl)
        
    cpdef val(self):
        return ModelVal.mk(self._hndl.val(), False)
        
    
    @staticmethod
    cdef mk(decl.IModelField *hndl, owned=True):
        ret = ModelField()
        ret._hndl = hndl
        return ret

cdef class ModelVal(object):

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
    
