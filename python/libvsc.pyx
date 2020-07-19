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

#********************************************************************
#* datamodel
#********************************************************************
cdef extern from "vsc.h" namespace "vsc":
    cdef cppclass Field:
        Field()
        const cpp_string &fullname()
        
    cdef cppclass FieldSP:
        FieldSP()
        FieldSP(Field *)
        Field *get()
        
    cdef cppclass FieldScalar(Field):
        FieldScalar(
            const cpp_string        &name,
            int                     width,
            bool                    is_signed,
            bool                    is_rand)
        
cdef class FieldModel(object):
    cdef FieldSP        hndl;
    def __init__(self):
        pass
    
    def fullname(self):
        return self.hndl.get().fullname().decode()

cdef class FieldScalarModel(FieldModel):

    def __init__(
            self,
            str          name,
            int          width,
            bool         is_signed,
            bool         is_rand):
        self.hndl = FieldSP(new FieldScalar(name.encode(), width, is_signed, is_rand))
        
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
        

    cdef enum ExprBinOp "vsc::ExprBinOp":
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

f = ExprBinModel(ExprModel(), ExprBinOp.Ne, ExprModel())        

cdef cpp_vector[Expr *] a
#a.push_back(new Expr())

cdef extern from "IRandomizer.h" namespace "vsc":
    cdef cppclass IRandomizer:
        bool randomize(
            const cpp_vector[FieldSP] &,
            const cpp_vector[FieldSP] &)
        
