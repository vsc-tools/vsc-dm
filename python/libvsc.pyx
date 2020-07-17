
cdef extern from "Expr.h" namespace "vsc":
    cdef cppclass Expr:
        Expr()
        
cdef ExprModel:
    
    def __init__(self):

cdef extern from "ExprBin.h" namespace "vsc":
    cdef cppclass ExprBin(Expr):
        ExprBin(Expr, Expr)
        
cdef class ExprBinModel:

    def __init__(self, ExprModel lhs, ExprModel rhs):    
        

        