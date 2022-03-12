
from libvsc cimport decl

cdef class Vsc(object):
    cdef decl.IVsc              *_hndl
    
    cdef decl.IContext *mkContext(self)
   
cdef class Context(object):
    cdef decl.IContext               *_hndl    