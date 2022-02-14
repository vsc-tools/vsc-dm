#****************************************************************************
#* libvsc.core
#****************************************************************************
from libvsc cimport decl
cimport cpython.ref as cpy_ref
from libcpp cimport bool

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
        

