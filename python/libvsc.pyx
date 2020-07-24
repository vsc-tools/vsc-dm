#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#  http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

# distutils: language = c++

# Import the map and vector templates from the STL
from libcpp.string cimport string as cpp_string
from libcpp.map cimport map as cpp_map
from libcpp.vector cimport vector as cpp_vector
from libcpp.utility cimport pair as cpp_pair
from libcpp cimport bool as bool

ctypedef unsigned long long   uint64_t
ctypedef long long            int64_t
ctypedef unsigned int         uint32_t


#********************************************************************
#* constraints
#********************************************************************

cdef extern from "vsc.h" namespace "vsc":

    cdef cppclass ConstraintStmt:
        ConstraintStmt()
    pass

    cdef cppclass ConstraintStmtSP:
        ConstraintStmtSP()
        ConstraintStmtSP(ConstraintStmt *)
        ConstraintStmt *get()
        
    cdef cppclass ConstraintScope(ConstraintStmt):
        ConstraintScope()
        void addConstraint(ConstraintStmtSP)
        
    cdef cppclass ConstraintBlock(ConstraintScope):
        ConstraintBlock(cpp_string)
        
cdef class ConstraintStmtModel(object):
    cdef ConstraintStmtSP       hndl;

    def __init__(self):
        pass
    
cdef class ConstraintScopeModel(ConstraintStmtModel):
    def __init__(self):
        self.hndl = ConstraintStmtSP(new ConstraintScope())
    
cdef class ConstraintBlockModel(ConstraintScopeModel):
    def __init__(self, name):
        self.hndl = ConstraintStmtSP(new ConstraintBlock(name.encode()))

    


#********************************************************************
#* datamodel
#********************************************************************
cdef extern from "vsc.h" namespace "vsc":
    cdef cppclass Field:
        Field()
        const cpp_string &name()
        void set_name(const cpp_string &)
        const cpp_string &fullname()
        bool decl_rand()
        void decl_rand(bool)
        ExprValSP val() const
        void val(ExprValSP)
        
    cdef cppclass FieldSP:
        FieldSP()
        FieldSP(Field *)
        Field *get()
        
    cdef cppclass FieldComposite(Field):
        FieldComposite(
            const cpp_string        &name,
            bool                    is_rand)
        void add_field(FieldSP field)
        
    cdef cppclass FieldScalar(Field):
        FieldScalar(
            const cpp_string        &name,
            int                     width,
            bool                    is_signed,
            bool                    is_rand)
        ExprValSP val() const
        
cdef class FieldModel(object):
    cdef FieldSP        hndl;
    def __init__(self):
        pass
    
    @property
    def name(self):
        return self.hndl.get().name().decode()
    
    @name.setter
    def name(self, v):
        self.hndl.get().set_name(v.encode())
        
    @property
    def decl_rand(self):
        return self.hndl.get().decl_rand()
    
    @decl_rand.setter
    def decl_rand(self, r):
        self.hndl.get().decl_rand(r)
    
    def fullname(self):
        return self.hndl.get().fullname().decode()
    
    @property
    def val(self):
        raise NotImplementedError("FieldModel.val not implemented")

    @val.setter
    def val(self, v):
        raise NotImplementedError("FieldModel.val not implemented")
    

cdef class FieldCompositeModel(FieldModel):
    def __init__(
            self,
            str          name,
            bool         is_rand):
        self.hndl = FieldSP(new FieldComposite(name.encode(), is_rand))
        
    def add_field(self, FieldModel f):
        cdef FieldComposite *c = (<FieldComposite *>self.hndl.get())
        c.add_field(f.hndl)


cdef class FieldScalarModel(FieldModel):

    def __init__(
            self,
            str          name,
            int          width,
            bool         is_signed,
            bool         is_rand):
        self.hndl = FieldSP(new FieldScalar(name.encode(), width, is_signed, is_rand))
        
    @property
    def val(self):
        ret = ExprValNumericModel()
        ret.hndl = self.hndl.get().val()
        return ret

    @val.setter
    def val(self, v):
        raise NotImplementedError("FieldModel.val not implemented")
    
#********************************************************************
#* expr
#********************************************************************
cdef extern from "vsc.h" namespace "vsc":
    cdef cppclass Expr:
        Expr()
        
    cdef cppclass ExprSP:
        ExprSP()
        ExprSP(Expr *)
        Expr *get()
        

    cpdef enum ExprBinOp "vsc::ExprBinOp":
        Eq "vsc::BinOp_Eq"
        Ne "vsc::BinOp_Ne"
        Gt "vsc::BinOp_Gt"
        Ge "vsc::BinOp_Ge"
        Lt "vsc::BinOp_Lt"
        Le "vsc::BinOp_Le"
        Add "vsc::BinOp_Add"
        Sub "vsc::BinOp_Sub"
        Div "vsc::BinOp_Div"
        Mul "vsc::BinOp_Mul"
        Mod "vsc::BinOp_Mod"
        And "vsc::BinOp_And"
        Or "vsc::BinOp_Or"
        Sll "vsc::BinOp_Sll"
        Srl "vsc::BinOp_Srl"
        Xor "vsc::BinOp_Xor"
        Not "vsc::BinOp_Not"
    
    cdef cppclass ExprBin(Expr):
        ExprBin(ExprSP, ExprBinOp, ExprSP)
        
    cdef cppclass ExprCond(Expr):
        ExprCond(ExprSP cond, ExprSP true_e, ExprSP false_e)
        
    cdef cppclass ExprFieldRef(Expr):
        ExprFieldRef(FieldSP)
        
    cdef cppclass ExprRange(Expr):
        ExprRange(ExprSP, ExprSP)
    cdef ExprRangeSP toRange "vsc::ExprRange::toRange"(ExprSP)
    
    cdef cppclass ExprRangeSP:
        ExprRangeSP()
        ExprRangeSP(ExprRange *)
        ExprRange *get() const
        
    cdef cppclass ExprRangelist(Expr):
        ExprRangelist()
        void addRange(ExprRangeSP)

    cdef enum ExprUnaryOp "vsc::ExprUnaryOp":
        LogNot "vsc::UnaryOp_LogNot"
        
    cdef cppclass ExprUnary(Expr):
        ExprUnary(ExprUnaryOp op, ExprSP rhs)
        
    cdef enum ExprValType "vsc::ExprValType":
        Numeric "vsc::ValType_Numeric"
        
    cdef cppclass ExprVal:
        ExprValType type()
        
    cdef cppclass ExprValSP:
        ExprValSP()
        ExprValSP(ExprVal *)
        ExprVal *get()

    cdef cppclass ExprValNumeric:
        ExprValNumeric(
            uint64_t    val,
            uint32_t    width,
            bool        is_signed)
        uint64_t val_u()
        int64_t val_s()
        uint32_t width()
        bool is_signed()
        
cdef class ExprModel(object):
    cdef ExprSP  hndl
    
    def __init__(self):
        pass
cdef class ExprBinModel(ExprModel):
    cdef ExprModel       lhs
    cdef ExprModel       rhs
    
    def __init__(self, ExprModel lhs, ExprBinOp op, ExprModel rhs):
        self.hndl = ExprSP(new ExprBin(lhs.hndl, op, rhs.hndl))
        self.lhs = lhs
        self.rhs = rhs
        pass
    
cdef class ExprCondModel(ExprModel):
    cdef ExprModel      cond
    cdef ExprModel      true_e
    cdef ExprModel      false_e
    
    def __init__(self, ExprModel cond, ExprModel true_e, ExprModel false_e):
        self.hndl = ExprSP(new ExprCond(cond.hndl, true_e.hndl, false_e.hndl))
        self.cond = cond
        self.true_e = true_e
        self.false_e = false_e
        
cdef class ExprFieldRefModel(ExprModel):
    cdef FieldModel     field
    
    def __init__(self, FieldModel field):
        self.hndl = ExprSP(new ExprFieldRef(field.hndl))
        self.field = field
        
cdef class ExprRangeModel(ExprModel): 
    cdef ExprModel      lhs
    cdef ExprModel      rhs
    
    def __init__(self, ExprModel lhs, ExprModel rhs):
        self.hndl = ExprSP(new ExprRange(lhs.hndl, rhs.hndl)) 
        self.lhs = lhs
        self.rhs = rhs
        
cdef class ExprRangelistModel(ExprModel):
    cdef list       range_l 
    
    def __init__(self, list[object] ranges=None):
        self.hndl = ExprSP(new ExprRangelist())
        
    def append(self, ExprRangeModel rng):
        cdef ExprRangelist *rl = (<ExprRangelist *>self.hndl.get())
        rl.addRange(toRange(rng.hndl))
        
cdef class ExprUnaryModel(ExprModel):
    cdef ExprUnaryOp    op
    cdef ExprModel      rhs
    
    def __init__(self, ExprUnaryOp op, ExprModel rhs):
        self.hndl = ExprSP(new ExprUnary(op, rhs.hndl)) 
        self.op = op

cdef class ExprValModel():
    cdef ExprValSP       hndl
    
    def __init__(self):
        pass
        
cdef class ExprValNumericModel(ExprValModel):
    def __init__(self):
        ExprValModel.__init__(self)
        
    def __int__(self):
        cdef ExprValNumeric *v = (<ExprValNumeric *>self.hndl.get())
        return v.val_s()
        

cdef extern from "vsc.h" namespace "vsc":
    cdef cppclass IRandomizer:
        bool randomize(
            const cpp_vector[FieldSP] &,
            const cpp_vector[ConstraintStmtSP] &)

    cdef cppclass RandomizerFactory:
        @staticmethod        
        IRandomizer *inst()
        
cdef class Randomizer(object):

    @staticmethod
    def do_randomize(fields, constraints=None):
        cdef cpp_vector[FieldSP] fields_v;
        cdef cpp_vector[ConstraintStmtSP] constraints_v;
        cdef FieldModel fm
        cdef IRandomizer *rand = RandomizerFactory.inst()
#        cdef cpp_vector[ConstraintStmtSP] constraints_v;

        for f in fields:
            fm = f
            fields_v.push_back(fm.hndl)
            
        if not rand.randomize(fields_v, constraints_v):
            raise Exception("solve failure")
    