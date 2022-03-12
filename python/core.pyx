#****************************************************************************
#* libvsc.core
#****************************************************************************
from libvsc cimport decl
import os
from ctypes import CDLL
cimport cpython.ref as cpy_ref
from libcpp cimport bool
import os
from ctypes import CDLL


cdef class Vsc(object):
    
    def __init__(self):
        print("Initialize Vsc")
        dir = os.path.dirname(os.path.abspath(__file__))
        # TODO: query other loaded libraries to see if vsc already loaded
        
        print("dir=%s" % dir)
        vsc = CDLL(os.path.join(dir, "libvsc.so"))
        print("vsc=%s" % str(vsc))

        pass
    
    cdef decl.IContext *mkContext(self):
        return self._hndl.mkContext()
        print("TODO: mkContext")
        return NULL
    
cdef Vsc _Vsc_inst = None
cdef Vsc Vsc_inst():
    global _Vsc_inst
    if _Vsc_inst is None:
        _Vsc_inst = Vsc()
    return _Vsc_inst


_Context_inst = None

cdef class Context(object):
#    cdef decl.IContext               *_hndl

    def __cinit__(self):
        Vsc_inst()
#        self._hndl = vsc.mkContext()

    def __init__(self):
        pass
    
    def __dealloc__(self):
        del self._hndl
    
    @staticmethod
    def inst():
        global _Context_inst
        if _Context_inst is None:
            _Context_inst = Context()
        return _Context_inst

cdef class ModelExpr(object):
    cdef decl.IModelExpr         *_hndl
    cdef bool                    _owned
    
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

cdef class ModelVal(object):
    pass

#********************************************************************
#* VisitorBase
#********************************************************************
cdef class VisitorBase(object):
    cdef decl.VisitorProxy      *_proxy

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
    cdef decl.IVsc              *_hndl
    
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
        
    
