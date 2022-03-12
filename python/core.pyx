#****************************************************************************
#* libvsc.core
#****************************************************************************
from libvsc cimport decl
import os
from ctypes import CDLL
cimport cpython.ref as cpy_ref
from libcpp cimport bool


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

    @staticmethod
    cdef mkWrapper(decl.IModelExpr *e):
        ret = ModelExpr()
        ret._owned = False
        ret._hndl = e
        return ret
    
cdef class ModelExprBin(ModelExpr):
    
    def __init__(self):
        pass

    @staticmethod
    cdef mkWrapper(decl.IModelExprBin *e):
        ret = ModelExprBin()
        ret._owned = False
        ret._hndl = e
        return ret

cdef class ModelVal(object):
    pass

#********************************************************************
#* VisitorBase
#********************************************************************
cdef class VisitorBase(object):
    cdef decl.VisitorProxy      *_proxy

    def __init__(self):
        _proxy = new decl.VisitorProxy(<cpy_ref.PyObject *>(self))
        
    def visitModelExprBin(self, e):
        pass
        
cdef public void VisitorProxy_visitModelExprBin(obj, decl.IModelExprBin *e) with gil:
    obj.visitModelExprBin(ModelExprBin.mkWrapper(e))
        

