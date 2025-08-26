#****************************************************************************
#* vsc_dm.core
#****************************************************************************
#
# Ownership Safety Note:
# When registering handles with the Context or transferring ownership,
# always check that the object is currently owned by Python before setting
# _owned = False. This prevents double-free or invalid ownership transfer.
# See addDataTypeStruct and similar methods for the required pattern.
#
import os
import sys
import ctypes
from enum import IntFlag, IntEnum
from ctypes import CDLL
from vsc_dm cimport decl
cimport cpython.ref as cpy_ref
cimport debug_mgr.core as dm_core
from libc.stdint cimport intptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
from libcpp.cast cimport dynamic_cast
from libcpp.cast cimport static_cast
from libcpp.cast cimport const_cast
from libcpp.utility cimport move as std_move
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr

cdef Context _Context_inst = None

cdef class Context(object):

    def __dealloc__(self):
        if self._owned and self._hndl != NULL:
            del self._hndl
        pass

    cpdef ModelBuildContext mkModelBuildContext(self, Context ctxt):
        return ModelBuildContext(ctxt)
        
    cpdef ModelField buildModelField(self, DataTypeStruct dt, name=""):
       return ModelField.mk(
           self._hndl.buildModelField(dt.asTypeStruct(), name.encode()), True)
    
    cpdef DataTypeEnum findDataTypeEnum(self, name):
        cdef decl.IDataTypeEnum *e = self._hndl.findDataTypeEnum(name.encode())
        if e != NULL:
            return DataTypeEnum.mk(e, False)
        else:
            return None
        
    cpdef DataTypeEnum mkDataTypeEnum(self,
            name,
            bool is_signed):
        return DataTypeEnum.mk(
            self._hndl.mkDataTypeEnum(name.encode(), is_signed),
            True)
    
    cpdef addDataTypeEnum(self, DataTypeEnum e):
        return self._hndl.addDataTypeEnum(e.asEnum())
    
    cpdef bool addDataTypeInt(self, DataTypeInt t):
        if not t._owned:
            raise Exception("The type handle must be owned to add it to the context")
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
        if not t._owned:
            raise Exception("The type handle (%s) must be owned to add it to the context")
        t._owned = False
        return self._hndl.addDataTypeStruct(t.asTypeStruct())
        
    cpdef DataTypeStruct findDataTypeStruct(self, name):
        cdef decl.IDataTypeStruct *t = self._hndl.findDataTypeStruct(name.encode())
        
        if t != NULL:
            return WrapperBuilder().mkObj(t, False)
        else:
            return None
            
    cpdef DataTypeStruct mkDataTypeStruct(self, name):
        return DataTypeStruct.mk(self._hndl.mkDataTypeStruct(name.encode()), True)

    cpdef getDataTypeStructs(self):
        cdef const cpp_vector[decl.IDataTypeStructUP] *structs = &self._hndl.getDataTypeStructs()
        ret = []
        for i in range(structs.size()):
            ret.append(WrapperBuilder().mkObj(structs.at(i).get(), False))

        return ret
    
    cpdef mkModelConstraintBlock(self, name):
        return ModelConstraintBlock.mk(self._hndl.mkModelConstraintBlock(name.encode()))
    
    cpdef mkModelConstraintExpr(self, ModelExpr expr):
        expr._owned = False
        return ModelConstraintExpr.mk(
            self._hndl.mkModelConstraintExpr(expr.asExpr()),
            True)

    cpdef mkModelConstraintIfElse(self, 
        ModelExpr           cond,
        ModelConstraint     true_c,
        ModelConstraint     false_c):
        cdef decl.IModelConstraint *false_p = NULL

        cond._owned = False
        true_c._owned = False
        if false_c is not None:
            false_c._owned = False
            false_p = false_c.asConstraint()

        return ModelConstraintIfElse.mk(
            self._hndl.mkModelConstraintIfElse(
                cond.asExpr(),
                true_c.asConstraint(),
                false_p
            ), True)

    cpdef mkModelConstraintImplies(self,
        ModelExpr           cond,
        ModelConstraint     body):
        cond._owned = False
        body._owned = False
        return ModelConstraintImplies.mk(self._hndl.mkModelConstraintImplies(
            cond.asExpr(),
            body.asConstraint()), True)

    cpdef mkModelConstraintScope(self):
        return ModelConstraintScope.mk(self._hndl.mkModelConstraintScope(), True)

    cpdef ModelConstraintSoft mkModelConstraintSoft(self, ModelConstraintExpr c):
        c._owned = False
        return ModelConstraintSoft.mk(
            self._hndl.mkModelConstraintSoft(c.asExpr()), True)

    cpdef ModelConstraintUnique mkModelConstraintUnique(self, exprs):
        cdef cpp_vector[decl.IModelExprP] expr_l
        cdef ModelExpr expr

        for e in exprs:
            expr = <ModelExpr>(e)
            expr._owned = False
            expr_l.push_back(expr.asExpr())

        return ModelConstraintUnique.mk(self._hndl.mkModelConstraintUnique(expr_l), True)

    cpdef mkModelExprBin(self, 
            ModelExpr           lhs,
            op,
            ModelExpr           rhs):
        cdef int op_i = int(op)
        if not lhs._owned:
            raise Exception("lhs must be free, but is owned")
        if not rhs._owned:
            raise Exception("rhs must be free, but is owned")
        
        lhs._owned = False
        rhs._owned = False
        
        if lhs._hndl == NULL:
            raise Exception("lhs is NULL")
        if rhs._hndl == NULL:
            raise Exception("rhs is NULL")
        
        return ModelExprBin.mk(
            self._hndl.mkModelExprBin(
                lhs.asExpr(),
                <decl.BinOp>(op_i),
                rhs.asExpr()))
        
    cpdef mkModelExprIn(self, ModelExpr lhs, ModelExprRangelist rhs):
        lhs._owned = False
        rhs._owned = False
        
        return ModelExprIn.mk(
            self._hndl.mkModelExprIn(
                lhs.asExpr(),
                rhs.asRangelist()))
        
    cpdef mkModelExprFieldRef(self, ModelField field):
        return ModelExprFieldRef.mk(
            self._hndl.mkModelExprFieldRef(field.asField()))
        
    cpdef mkModelExprPartSelect(self, ModelExpr lhs, int32_t lower, int32_t upper):
        return ModelExprPartSelect.mk(
            self._hndl.mkModelExprPartSelect(lhs.asExpr(), lower, upper), True)
        
    cpdef mkModelExprRange(self, bool is_single, ModelExpr lower, ModelExpr upper):
        cdef decl.IModelExpr *l = NULL
        cdef decl.IModelExpr *u = NULL
        
        if lower is not None:
            l = lower.asExpr()
            lower._owned = False
            
        if upper is not None:
            u = upper.asExpr()
            upper._owned = False
            
        return ModelExprRange.mk(
            self._hndl.mkModelExprRange(is_single, l, u), True)
        
    cpdef mkModelExprRangelist(self):
        return ModelExprRangelist.mk(
            self._hndl.mkModelExprRangelist(), True)
        
    cpdef mkModelFieldRoot(self, DataType type, name):
        cdef decl.IDataType *type_h = NULL
        
        if type is not None:
            type_h = type.asType()

#        return WrapperBuilder().mkObj(
#            self._hndl.mkModelFieldRoot(
#                type_h, 
#                name.encode()),
#            True)
        return None
        
    cpdef mkModelFieldVecRoot(self, DataType type, name):
        cdef decl.IDataType *type_h = NULL
        
        if type is not None:
            type_h = type.asType()
        
        return ModelFieldVecRoot.mk(self._hndl.mkModelFieldVecRoot(
            type_h,
            name.encode()))
        
    cpdef TypeConstraintBlock mkTypeConstraintBlock(self, name):
        return TypeConstraintBlock.mk(self._hndl.mkTypeConstraintBlock(
            name.encode()), True)
        
    cpdef TypeConstraintExpr mkTypeConstraintExpr(self, TypeExpr e):
        e._owned = False
        return TypeConstraintExpr.mk(self._hndl.mkTypeConstraintExpr(
            e.asExpr()))

    cpdef TypeConstraintIfElse mkTypeConstraintIfElse(self, 
        TypeExpr        cond,
        TypeConstraint  true_c,
        TypeConstraint  false_c):
        cdef decl.ITypeConstraint *false_cp = NULL

        cond._owned = False
        true_c._owned = False
        if false_c is not None:
            false_c._owned = False
            false_cp = false_c.asConstraint()

        return TypeConstraintIfElse.mk(self._hndl.mkTypeConstraintIfElse(
            cond.asExpr(),
            true_c.asConstraint(),
            false_cp), True)

    cpdef TypeConstraintImplies mkTypeConstraintImplies(self, 
        TypeExpr        cond,
        TypeConstraint  body):
        cond._owed = False
        body._owned = False
        return TypeConstraintImplies.mk(self._hndl.mkTypeConstraintImplies(
            cond.asExpr(),
            body.asConstraint()), True)
        
    cpdef TypeConstraintScope mkTypeConstraintScope(self):
        return TypeConstraintScope.mk(self._hndl.mkTypeConstraintScope())

    cpdef TypeConstraintSoft mkTypeConstraintSoft(self, TypeConstraintExpr c):
        c._owned = False
        return TypeConstraintSoft.mk(
            self._hndl.mkTypeConstraintSoft(c.asExpr()), True)

    cpdef TypeConstraintUnique mkTypeConstraintUnique(self, exprs):
        cdef cpp_vector[decl.ITypeExprP] expr_l
        cdef TypeExpr expr

        for e in exprs:
            expr = <TypeExpr>e
            expr._owned = False
            expr_l.push_back(expr.asExpr())

        return TypeConstraintUnique.mk(self._hndl.mkTypeConstraintUnique(expr_l), False)

    cpdef TypeExprBin mkTypeExprBin(self, TypeExpr lhs, op, TypeExpr rhs):
        cdef int op_i = int(op)
        lhs._owned = False
        rhs._owned = False
        return TypeExprBin.mk(self._hndl.mkTypeExprBin(
            lhs.asExpr(),
            <decl.BinOp>(op_i),
            rhs.asExpr()))

    cpdef TypeExprEnumRef mkTypeExprEnumRef(self, DataTypeEnum enum_t, int32_t enum_id):
        return TypeExprEnumRef.mk(
            self._hndl.mkTypeExprEnumRef(
                enum_t.asEnum(),
                enum_id))

    cpdef TypeExprArrayLiteral mkTypeExprArrayLiteral(self, DataTypeArray arr_t, bint arr_t_owned, vals):
        """
        arr_t: DataTypeArray
        arr_t_owned: bool
        vals: list of TypeExpr
        """
        cdef cpp_vector[decl.ITypeExprP] vals_vec
        raise Exception("Handle vals")
        # for v in vals:
        #     v._owned = False
        #     vals_vec.push_back(v.asExpr())
        return TypeExprArrayLiteral.mk(
            self._hndl.mkTypeExprArrayLiteral(arr_t.asArray(), arr_t_owned, vals_vec),
            True)

    cpdef TypeExprArrIndex mkTypeExprArrIndex(self, TypeExpr root, bint root_owned, TypeExpr index, bint index_owned):
        root._owned = False
        index._owned = False
        return TypeExprArrIndex.mk(
            self._hndl.mkTypeExprArrIndex(root.asExpr(), root_owned, index.asExpr(), index_owned),
            True)

    cpdef TypeExprRefBottomUp mkTypeExprRefBottomUp(self, int32_t scope_offset, int32_t field_index):
        return TypeExprRefBottomUp.mk(
            self._hndl.mkTypeExprRefBottomUp(scope_offset, field_index),
            True)

    cpdef TypeExprRefInline mkTypeExprRefInline(self):
        return TypeExprRefInline.mk(
            self._hndl.mkTypeExprRefInline(),
            True)

    cpdef TypeExprRefPath mkTypeExprRefPath(self, TypeExpr root, bint owned, path):
        """
        root: TypeExpr
        owned: bool
        path: list of int32_t
        """
        cdef cpp_vector[int32_t] path_vec
        for idx in path:
            path_vec.push_back(idx)
        root._owned = False
        return TypeExprRefPath.mk(
            self._hndl.mkTypeExprRefPath(root.asExpr(), owned, path_vec),
            True)

    cpdef TypeExprRefTopDown mkTypeExprRefTopDown(self):
        return TypeExprRefTopDown.mk(
            self._hndl.mkTypeExprRefTopDown(),
            True)

    cpdef TypeExprStructLiteral mkTypeExprStructLiteral(self, DataTypeStruct type, bint type_owned, field_values):
        """
        type: DataTypeStruct
        type_owned: bool
        field_values: list of TypeExpr
        """
        cdef cpp_vector[decl.ITypeExprP] vals_vec
        raise Exception("TODO")
        # for v in field_values:
        #     v._owned = False
        #     vals_vec.push_back(v.asExpr())
        type._owned = False
        return TypeExprStructLiteral.mk(
            self._hndl.mkTypeExprStructLiteral(type.asTypeStruct(), type_owned, vals_vec),
            True)

    cpdef TypeExprSubField mkTypeExprSubField(self, TypeExpr root, bint owned, int32_t field_idx):
        root._owned = False
        return TypeExprSubField.mk(
            self._hndl.mkTypeExprSubField(root.asExpr(), owned, field_idx),
            True)

    cpdef TypeExprUnary mkTypeExprUnary(self, op, TypeExpr expr, bint owned):
        """
        op: UnaryOp (int)
        expr: TypeExpr
        owned: bool
        """
        cdef int op_i = int(op)
        expr._owned = False
        return TypeExprUnary.mk(
            self._hndl.mkTypeExprUnary(
                expr.asExpr(), 
                owned,
                <decl.UnaryOp>(op_i)),
            True)

    cpdef TypeExprRef mkTypeExprRef(self, TypeExpr target, bint owned):
        target._owned = False
        return TypeExprRef.mk(
            self._hndl.mkTypeExprRef(target.asExpr(), owned),
            True)
        
    # cpdef TypeExprFieldRef mkTypeExprFieldRef(self, root_kind, int32_t root_idx):
    #     cdef int root_kind_i = int(root_kind)
    #     return TypeExprFieldRef.mk(
    #         self._hndl.mkTypeExprFieldRef(
    #             <decl.TypeExprFieldRef_RootRefKind>(root_kind_i),
    #             root_idx), True)
    
    cpdef TypeExprRange mkTypeExprRange(self,
                                        bool is_single,
                                        TypeExpr lower,
                                        TypeExpr upper):
        cdef decl.ITypeExpr *l = NULL
        cdef decl.ITypeExpr *u = NULL
        if lower is not None:
            l = lower.asExpr()
        if upper is not None:
            u = upper.asExpr()
            
        return TypeExprRange.mk(self._hndl.mkTypeExprRange(
            is_single,
            l,
            u), True)
        
    cpdef TypeExprRangelist mkTypeExprRangelist(self):
        return TypeExprRangelist.mk(
            self._hndl.mkTypeExprRangelist(),
            True)
    
    cpdef TypeExprVal mkTypeExprVal(self, ValRef v):
        """
        v: ValRef
        """
        raise Exception("TODO")
        # if v is None:
        #     return TypeExprVal.mk(self._hndl.mkTypeExprVal(decl.ValRef()), True)
        # else:
        #     return TypeExprVal.mk(self._hndl.mkTypeExprVal(v.val), True)
        
    cpdef TypeFieldPhy mkTypeFieldPhy(self, 
                                name, 
                                DataType dtype, 
                                bool own_dtype,
                                attr,
                                TypeExpr init):
        cdef decl.ValRef init_v
        cdef bool have_init = False
        cdef int attr_i = int(attr)
        cdef decl.ITypeExpr *init_h = NULL

        print("TODO: mkTypeFieldPhy -- init value") 
        if init is not None:
            init._owned = False
            init_h = init.asExpr()
            
        return TypeFieldPhy.mk(self._hndl.mkTypeFieldPhy(
            name.encode(), 
            dtype.asType(), 
            own_dtype,
            <decl.TypeFieldAttr>(attr_i),
            init_h))
        
    cpdef TypeFieldRef mkTypeFieldRef(self, 
                                name, 
                                DataType dtype,
                                attr):
        cdef int attr_i = int(attr)
#        attr_i = int(attr)
        
        return TypeFieldRef.mk(self._hndl.mkTypeFieldRef(
            name.encode(), 
            dtype.asType(), 
            <decl.TypeFieldAttr>(attr_i)))

    cpdef ValRefInt mkValRefInt(self, int value, bool is_signed, int width):
        ret = ValRefInt()
        ret.val = self._hndl.mkValRefInt(value, is_signed, width)

        return ret

    cpdef ValRefStruct mkValRefStruct(self, DataTypeStruct t):
        ret = ValRefStruct()
        ret.val = self._hndl.mkValRefStruct(t.asTypeStruct())
        return ret

    @staticmethod
    cdef mk(decl.IContext *hndl, bool owned=True):
        ret = Context()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class ModelBuildContext(object):

    def __init__(self, Context ctxt):
        self._hndl = decl.mkModelBuildContext(ctxt._hndl)

    cpdef Context ctxt(self):
        return Context.mk(self._hndl.ctxt(), False)

    def __dal__(self):
#        del self._hndl
        pass

#    @staticmethod
#    cpdef ModelBuildContext mk(Context ctxt):
#        ret = ModelBuildContext()
#        ret._hndl = decl.mkModelBuildContext(ctxt._hndl)
#        return ret
    
cdef class Accept(object):


    cdef decl.IAccept *hndl(self):
        return NULL

cdef class ObjBase(object):

    def __dealloc__(self):
        if self._owned:
            del self._hndl
        pass

    def __hash__(self):
        return <intptr_t>(self._hndl)
    
    def __eq__(self, ObjBase other):
        return self._hndl == other._hndl
        
cdef class DataType(ObjBase):

    cpdef ModelField mkRootField(
        self,
        ModelBuildContext   ctxt,
        str                 name,
        bool                is_ref):
        cdef decl.IModelField *ret = self.asType().mkRootField(
            ctxt._hndl,
            name.encode(),
            is_ref)
        return ModelField.mk(ret, True)

    cpdef ModelField mkTypeField(
        self,
        ModelBuildContext    ctxt,
        TypeField            type,
        ValRef               val):
        cdef decl.IModelField *ret = self.asType().mkTypeField(
            ctxt._hndl,
            type.asField(),
            val.val)
        return ModelField.mk(ret, True)

    cdef decl.IDataType *asType(self):
        return dynamic_cast[decl.IDataTypeP](self._hndl)

    cpdef void setAssociatedData(self, obj):
        cdef decl.AssociatedDataClosure *closure = new decl.AssociatedDataClosure(<cpy_ref.PyObject *>(obj))
        self.asType().setAssociatedData(closure)

    cpdef object getAssociatedData(self):
        cdef decl.AssociatedDataClosure *closure = dynamic_cast[decl.AssociatedDataClosureP](self.asType().getAssociatedData()) 

        if closure != NULL:
            return closure.getData()
        else:
            return None

    @staticmethod
    cdef mk(decl.IDataType *hndl, bool owned=True):
        return WrapperBuilder().mkObj(hndl, owned)
    
cdef class DataTypeEnum(DataType):
    cpdef name(self):
        return self.asEnum().name().decode()
    
    cpdef isSigned(self):
        return self.asEnum().isSigned()
    
#    cpdef addEnumerator(self, name, ModelVal val):
#        return self.asEnum().addEnumerator(
#            name.encode(),
#            val._hndl)
    
    
    cpdef getDomain(self):
        return TypeExprRangelist.mk(
            self.asEnum().getDomain(),
            False)
    
    cdef decl.IDataTypeEnum *asEnum(self):
        return dynamic_cast[decl.IDataTypeEnumP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IDataTypeEnum *hndl, bool owned=True):
        ret = DataTypeEnum()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypeArray(DataType):

    cpdef DataType getElemType(self):
        cdef decl.IDataType *elem = self.asTypeArray().getElemType()
        if elem != NULL:
            return DataType.mk(elem, False)
        else:
            return None

    cpdef uint32_t getSize(self):
        return self.asTypeArray().getSize()

    @staticmethod
    cdef mk(decl.IDataTypeArray *hndl, bool owned=True):
        ret = DataTypeArray()
        ret._hndl = hndl
        ret._owned = owned
        return ret

    cdef decl.IDataTypeArray *asTypeArray(self):
        return dynamic_cast[decl.IDataTypeArrayP](self._hndl)

cdef class DataTypeInt(DataType):

    cpdef bool is_signed(self):
        return self.asTypeInt().is_signed()

    cpdef int width(self):
        return self.asTypeInt().width()
    
    @staticmethod
    cdef mk(decl.IDataTypeInt *hndl, bool owned=True):
        ret = DataTypeInt()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
    cdef decl.IDataTypeInt *asTypeInt(self):
        return dynamic_cast[decl.IDataTypeIntP](self._hndl)
    
cdef class DataTypeStruct(DataType):

    def __dealloc__(self):
        if self._owned:
            self.setCreateHook(None)

    cpdef name(self):
        return self.asTypeStruct().name().decode()

    cpdef addField(self, TypeField f):
        if f is None:
            raise Exception("Cannot add field==None")
        if not f._owned:
            raise Exception("The field handle must be owned to add it to the context")
        f._owned = False
        self.asTypeStruct().addField(f.asField())
        
    cpdef getFields(self):
        ret = []
        for i in range(self.asTypeStruct().getFields().size()):
            ret.append(WrapperBuilder().mkObj(self.asTypeStruct().getField(i), False))
        return ret
    
    cpdef TypeField getField(self, int32_t idx):
        cdef decl.ITypeField *ret_h = self.asTypeStruct().getField(idx)
        
        if ret_h != NULL:
            return WrapperBuilder().mkObj(ret_h, False)
        else:
            return None
    
    cpdef addConstraint(self, TypeConstraint c):
        if not c._owned:
            raise Exception("The constraint handle must be owned to add it to the context")
        c._owned = False
        self.asTypeStruct().addConstraint(c.asConstraint())
        pass
    
    cpdef getConstraints(self):
        ret = []
        for i in range(self.asTypeStruct().getConstraints().size()):
            ret.append(TypeConstraint.mk(
                self.asTypeStruct().getConstraints().at(i).get(), False))
        return ret
    
    cpdef setCreateHook(self, hook_f):
        cdef decl.ModelStructCreateHookClosure *closure = NULL
        if hook_f is not None:
            closure = new decl.ModelStructCreateHookClosure(<cpy_ref.PyObject *>(hook_f))
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
    
cdef class ModelConstraint(ObjBase):

    cdef decl.IModelConstraint *asConstraint(self):
        return dynamic_cast[decl.IModelConstraintP](self._hndl)
            
    @staticmethod
    cdef mk(decl.IModelConstraint *hndl, bool owned=True):
        return WrapperBuilder().mkObj(hndl, owned)

cdef class ModelConstraintScope(ModelConstraint):
    
    cpdef getConstraints(self):
        cdef const cpp_vector[decl.IModelConstraintUP] *cl = &self.asScope().getConstraints()
        ret = []
        
        for i in range(cl.size()):
            ret.append(ModelConstraint.mk(cl.at(i).get(), False))
        
        return ret
    
    cpdef addConstraint(self, ModelConstraint c):
        if not c._owned:
            raise Exception("The constraint handle must be owned to add it to the context")
        c._owned = False
        self.asScope().addConstraint(c.asConstraint())
    
    cdef decl.IModelConstraintScope *asScope(self):
        return dynamic_cast[decl.IModelConstraintScopeP](self._hndl)

    @staticmethod
    cdef mk(decl.IModelConstraintScope *hndl, bool owned=True):
        ret = ModelConstraintScope()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelConstraintSoft(ModelConstraint):

    cpdef ModelConstraintExpr constraint(self):
        return ModelConstraintExpr.mk(self.asSoft().constraint(), False)

    cdef decl.IModelConstraintSoft *asSoft(self):
        return dynamic_cast[decl.IModelConstraintSoftP](self._hndl)

    @staticmethod
    cdef mk(decl.IModelConstraintSoft *hndl, bool owned=True):
        ret = ModelConstraintSoft()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelConstraintUnique(ModelConstraint):
    cpdef getExprs(self):
        ret = []
        for i in range(self.asUnique().getExprs().size()):
            ret.append(ModelExpr.mk(
                self.asUnique().getExprs().at(i).get(),
                False))
        return ret
    
    cdef decl.IModelConstraintUnique *asUnique(self):
        return dynamic_cast[decl.IModelConstraintUniqueP](self._hndl)

    @staticmethod
    cdef mk(decl.IModelConstraintUnique *hndl, bool owned=True):
        ret = ModelConstraintUnique()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelConstraintBlock(ModelConstraintScope):

    cpdef name(self):
        return self.asModelConstraintBlock().name().decode()

    cdef decl.IModelConstraintBlock *asModelConstraintBlock(self):
        return dynamic_cast[decl.IModelConstraintBlockP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelConstraintBlock *hndl, bool owned=True):
        ret = ModelConstraintBlock()
        ret._hndl = hndl
        ret._owned = owned
        return ret


cdef class ModelConstraintExpr(ModelConstraint):

    cpdef expr(self):
        return ModelExpr.mk(self.asExpr().expr(), False)
    
    @staticmethod
    cdef mk(decl.IModelConstraintExpr *hndl, bool owned=True):
        ret = ModelConstraintExpr()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
    cdef decl.IModelConstraintExpr *asExpr(self):
        return dynamic_cast[decl.IModelConstraintExprP](self._hndl)

cdef class ModelConstraintIfElse(ModelConstraint):
    cpdef getCond(self):
        return ModelExpr.mk(self.asIfElse().getCond(), False)

    cpdef getTrue(self):
        return ModelConstraint.mk(self.asIfElse().getTrue(), False)

    cpdef getFalse(self):
        if self.asIfElse().getFalse() != NULL:
            return ModelConstraint.mk(self.asIfElse().getFalse(), False)
        else:
            return None

    cpdef setFalse(self, ModelConstraint c):
        cdef decl.IModelConstraint *cp = NULL

        if c is not None:
            c._owned = False
            cp = c.asConstraint()
        self.asIfElse().setFalse(cp)

    cdef decl.IModelConstraintIfElse *asIfElse(self):
        return dynamic_cast[decl.IModelConstraintIfElseP](self._hndl)

    @staticmethod
    cdef mk(decl.IModelConstraintIfElse *hndl, bool owned=True):
        ret = ModelConstraintIfElse()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    

cdef class ModelConstraintImplies(ModelConstraint):
    cpdef getCond(self):
        return ModelExpr.mk(self.asImplies().getCond(), False)

    cpdef getBody(self):
        return ModelConstraint.mk(self.asImplies().getBody(), False)

    cdef decl.IModelConstraintImplies *asImplies(self):
        return dynamic_cast[decl.IModelConstraintImpliesP](self._hndl)

    @staticmethod
    cdef mk(decl.IModelConstraintImplies *hndl, bool owned=True):
        ret = ModelConstraintImplies()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelExpr(ObjBase):
    
    cdef decl.IModelExpr *asExpr(self):
        return dynamic_cast[decl.IModelExprP](self._hndl)

    @staticmethod
    cdef mk(decl.IModelExpr *hndl, bool owned=True):
        if hndl == NULL:
            return None
        else:
            return WrapperBuilder().mkObj(hndl, owned)
    
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
    BinXor  = decl.BinOp.BinXor
    Not     = decl.BinOp.Not
    
cdef class ModelExprBin(ModelExpr):
    
    @staticmethod
    cdef mk(decl.IModelExprBin *hndl, bool owned=True):
        ret = ModelExprBin()
        ret._owned = owned
        ret._hndl = hndl
        return ret
    
    cdef decl.IModelExprBin *asExprBin(self):
        return <decl.IModelExprBin *>(self._hndl)

cdef class ModelExprCond(ModelExpr):

    cpdef getCond(self):
        return ModelExpr.mk(self.asCond().getCond(), False)

    cpdef getTrue(self):
        return ModelExpr.mk(self.asCond().getTrue(), False)

    cpdef getFalse(self):
        return ModelExpr.mk(self.asCond().getFalse(), False)

    cdef decl.IModelExprCond *asCond(self):
        return dynamic_cast[decl.IModelExprCondP](self._hndl)

    @staticmethod
    cdef mk(decl.IModelExprCond *hndl, bool owned=True):
        ret = ModelExprCond()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class ModelExprIn(ModelExpr):

    @staticmethod
    cdef mk(decl.IModelExprIn *hndl, bool owned=True):
        ret = ModelExprIn()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
    cdef decl.IModelExprIn *asExprIn(self):
        return dynamic_cast[decl.IModelExprInP](self._hndl)
    
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
    
cdef class ModelExprPartSelect(ModelExpr):

    cpdef lhs(self):
        return ModelExpr.mk(self.asPartSelect().lhs(), False)
    
    cpdef int32_t lower(self):
        return self.asPartSelect().lower()
    
    cpdef int32_t upper(self):
        return self.asPartSelect().upper()
    
    cdef decl.IModelExprPartSelect *asPartSelect(self):
        return dynamic_cast[decl.IModelExprPartSelectP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelExprPartSelect *hndl, bool owned=True):
        ret = ModelExprPartSelect()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class ModelExprRange(ModelExpr):
    cpdef isSingle(self):
        return self.asRange().isSingle()
    
    cpdef ModelExpr lower(self):
        return ModelExpr.mk(self.asRange().lower(), False)
    
    cpdef ModelExpr upper(self):
        return ModelExpr.mk(self.asRange().upper(), False)
    
    cdef decl.IModelExprRange *asRange(self):
        return dynamic_cast[decl.IModelExprRangeP](self._hndl)
    
    @staticmethod 
    cdef mk(decl.IModelExprRange *hndl, bool owned=True):
        ret = ModelExprRange()
        ret._hndl = hndl
        ret._owned = owned
        return ret
        
cdef class ModelExprRangelist(ModelExpr):

    cpdef ranges(self):
        ret = []
        for i in range(self.asRangelist().ranges().size()):
            ret.append(ModelExprRange.mk(
                self.asRangelist().ranges().at(i).get(), False))
        return ret
    
    cpdef addRange(self, ModelExprRange r):
        self.asRangelist().addRange(r.asRange())
    
    cdef decl.IModelExprRangelist *asRangelist(self):
        return dynamic_cast[decl.IModelExprRangelistP](self._hndl)
    
    @staticmethod 
    cdef mk(decl.IModelExprRangelist *hndl, bool owned=True):
        ret = ModelExprRangelist()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelExprRef(ModelExpr): 

    cpdef expr(self):
        return ModelExpr.mk(self.asRef().expr(), False)

    cdef decl.IModelExprRef *asRef(self):
        return dynamic_cast[decl.IModelExprRefP](self._hndl)

    @staticmethod
    cdef mk(decl.IModelExprRef *hndl, bool owned=True):
        ret = ModelExprRef()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
class UnaryOp(IntEnum):
    Not = decl.UnaryOp.Un_Not
    
    
cdef class ModelExprUnary(ModelExpr):

    cpdef ModelExpr expr(self):
        return ModelExpr.mk(self.asUnary().expr(), False)
        
    cpdef op(self):
        op_i = int(self.asUnary().op())
        return UnaryOp(op_i)
    
    cdef decl.IModelExprUnary *asUnary(self):
        return dynamic_cast[decl.IModelExprUnaryP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelExprUnary *hndl, bool owned=True): 
        ret = ModelExprUnary()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class ModelExprVecSubscript(ModelExpr):

    cpdef expr(self):
        return ModelExpr.mk(self.asVecSubscript().expr(), False)

    cpdef subscript(self):
        return ModelExpr.mk(self.asVecSubscript().subscript(), False)
    
    cdef decl.IModelExprVecSubscript *asVecSubscript(self):
        return dynamic_cast[decl.IModelExprVecSubscriptP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelExprVecSubscript *hndl, bool owned=True):
        ret = ModelExprVecSubscript()
        ret._hndl = hndl
        ret._owned = owned
        return ret

class ModelFieldFlag(IntFlag):
    NoFlags  = decl.ModelFieldFlag.NoFlags
    DeclRand = decl.ModelFieldFlag.DeclRand
    UsedRand = decl.ModelFieldFlag.UsedRand
    Resolved = decl.ModelFieldFlag.Resolved
    VecSize  = decl.ModelFieldFlag.VecSize

cdef class ModelField(ObjBase):

    def __dealloc__(self):
        if self._owned:
            self.setFieldData(None)


    cpdef name(self):
        return self.asField().name().decode()
    
    cpdef getDataType(self):
        return DataType.mk(self.asField().getDataType(), False)
    
    cpdef getParent(self):
        return ModelField.mk(self.asField().getParent(), False)
    
    cpdef setParent(self, ModelField parent):
        self.asField().setParent(parent.asField())
        
    cpdef getConstraints(self):
        cdef const cpp_vector[decl.IModelConstraintUP] *constraints_l = &self.asField().getConstraints()
        ret = []
        
        for i in range(constraints_l.size()):
            ret.append(ModelConstraint.mk(constraints_l.at(i).get(), False))
            
        return ret
        
    cpdef addConstraint(self, ModelConstraint c):
        if not c._owned:
            raise Exception("The constraint handle must be owned to add it to the context")
        c._owned = False
        self.asField().addConstraint(c.asConstraint())

    cpdef getFields(self):
        cdef const cpp_vector[decl.IModelFieldUP] *fields_l = &self.asField().getFields()
        ret = []
        for i in range(fields_l.size()):
            ret.append(ModelField.mk(fields_l.at(i).get()))
        return ret
        
    cpdef addField(self, ModelField f):
        if not f._owned:
            raise Exception("Cannot add a field already owned by another composite")
        # We're taking ownership of the field
        f._owned = False
        self.asField().addField(f.asField())
        
    cpdef ModelField getField(self, int32_t idx):
        cdef decl.IModelField *field = self.asField().getField(idx)
        
        if field != NULL:
            return ModelField.mk(field, False)
        else:
            return None
        
    cpdef val(self):
        # TODO:
#        return ModelVal.mk(self.asField().val(), False)
        pass
    
    cpdef clearFlag(self, flags):
        cdef int flags_i = flags
        self.asField().clearFlag(<decl.ModelFieldFlag>(flags_i))
    
    cpdef setFlag(self, flags):
        cdef int flags_i = flags
        self.asField().setFlag(<decl.ModelFieldFlag>(flags_i))
    
    cpdef isFlagSet(self, flags):
        cdef int flags_i = flags
        return self.asField().isFlagSet(<decl.ModelFieldFlag>(flags_i))
    
    cpdef setFieldData(self, data):
        cdef decl.ModelFieldDataClosure *c = NULL
        if data is not None:
            c = new decl.ModelFieldDataClosure(<cpy_ref.PyObject *>(data))
        self.asField().setFieldData(c)
        
    cpdef getFieldData(self):
        cdef decl.IModelFieldData *d = self.asField().getFieldData()
        cdef decl.ModelFieldDataClosure *c
        
        if d != NULL:
            c = dynamic_cast[decl.ModelFieldDataClosureP](d)
            return c.getData()
        else:
            return None

    cdef decl.IModelField *asField(self):
        return dynamic_cast[decl.IModelFieldP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelField *hndl, bool owned=True):
        return WrapperBuilder().mkObj(hndl, owned)
    
cdef class ModelFieldRef(ModelField):
    cpdef setRef(self, ModelField r):
        self.asRef().setRef(r.asField())

    cpdef ModelField getRef(self):
        return ModelField.mk(self.asRef().getRef(), False)

    cdef decl.IModelFieldRef *asRef(self):
        return dynamic_cast[decl.IModelFieldRefP](self._hndl)

    @staticmethod
    cdef mk(decl.IModelFieldRef *hndl, bool owned=True):
        ret = ModelFieldRef()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class ModelFieldRoot(ModelField):

    cpdef setName(self, name):
        self.asRoot().setName(name.encode())

    cdef decl.IModelFieldRoot *asRoot(self):
        return dynamic_cast[decl.IModelFieldRootP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelFieldRoot *hndl, bool owned=True):
        ret = ModelFieldRoot()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class ModelFieldType(ModelField):

    cdef decl.IModelFieldType *asType(self):
        return dynamic_cast[decl.IModelFieldTypeP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelFieldType *hndl, bool owned=True):
        ret = ModelFieldType()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelFieldTypeRef(ModelFieldRef):

    cdef decl.IModelFieldTypeRef *asType(self):
        return dynamic_cast[decl.IModelFieldTypeRefP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelFieldTypeRef *hndl, bool owned=True):
        ret = ModelFieldTypeRef()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class ModelFieldVec(ModelField):

    cpdef getSizeRef(self):
        return ModelField.mk(self.asVec().getSizeRef(), False)
    
    cpdef getSize(self):
        return self.asVec().getSize()

    cdef decl.IModelFieldVec *asVec(self):
        return dynamic_cast[decl.IModelFieldVecP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelFieldVec *hndl, bool owned=True):
        ret = ModelFieldVec()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class ModelFieldVecRoot(ModelFieldVec):

    cpdef void setName(self, name):
        self.asVecRoot().setName(name.encode())

    cdef decl.IModelFieldVecRoot *asVecRoot(self):
        return dynamic_cast[decl.IModelFieldVecRootP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IModelFieldVecRoot *hndl, bool owned=True):
        ret = ModelFieldVecRoot()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelFieldDataClosure(object):

    cpdef getData(self):
        return dynamic_cast[decl.ModelFieldDataClosureP](self._hndl).getData()
    
    @staticmethod
    cdef mk(decl.IModelFieldData *hndl):
        ret = ModelFieldDataClosure()
        ret._hndl = hndl
        return ret

cdef class TypeConstraint(ObjBase):

    cdef decl.ITypeConstraint *asConstraint(self):
        return dynamic_cast[decl.ITypeConstraintP](self._hndl)

    @staticmethod
    cdef TypeConstraint mk(decl.ITypeConstraint *hndl, bool owned=True):
        return WrapperBuilder().mkObj(hndl, owned)

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

cdef class TypeConstraintIfElse(TypeConstraint):
    cpdef getCond(self):
        return TypeExpr.mk(self.asIfElse().getCond(), False)

    cpdef getTrue(self):
        return TypeConstraint.mk(self.asIfElse().getTrue(), False)

    cpdef getFalse(self):
        if self.asIfElse().getFalse() != NULL:
            return TypeConstraint.mk(self.asIfElse().getFalse(), False)
        else:
            return None

    cpdef setFalse(self, TypeConstraint c):
        cdef decl.ITypeConstraint *cp = NULL
        
        if c is not None:
            c._owned = False
            cp = c.asConstraint()
        
        self.asIfElse().setFalse(cp)

    cdef decl.ITypeConstraintIfElse *asIfElse(self):
        return dynamic_cast[decl.ITypeConstraintIfElseP](self._hndl)

    @staticmethod
    cdef TypeConstraintIfElse mk(decl.ITypeConstraintIfElse *hndl, bool owned=True):
        ret = TypeConstraintIfElse()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeConstraintImplies(TypeConstraint):
    cpdef getCond(self):
        return TypeExpr.mk(self.asImplies().getCond(), False)

    cpdef getBody(self):
        return TypeConstraint.mk(self.asImplies().getBody(), False)

    cdef decl.ITypeConstraintImplies *asImplies(self):
        return dynamic_cast[decl.ITypeConstraintImpliesP](self._hndl)

    @staticmethod
    cdef TypeConstraintImplies mk(decl.ITypeConstraintImplies *hndl, bool owned=True):
        ret = TypeConstraintImplies()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class TypeConstraintScope(TypeConstraint):
    
    cpdef addConstraint(self, TypeConstraint c):
        c._owned = False
        self.asScope().addConstraint(c.asConstraint())
    
    cdef decl.ITypeConstraintScope *asScope(self):
        return dynamic_cast[decl.ITypeConstraintScopeP](self._hndl)
    
    @staticmethod
    cdef TypeConstraintScope mk(decl.ITypeConstraintScope *hndl, bool owned=True):
        ret = TypeConstraintScope()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeConstraintSoft(TypeConstraint):
    
    cpdef TypeConstraintExpr constraint(self):
        return TypeConstraintExpr.mk(self.asSoft().constraint(), False)
    
    cdef decl.ITypeConstraintSoft *asSoft(self):
        return dynamic_cast[decl.ITypeConstraintSoftP](self._hndl)
    
    @staticmethod
    cdef TypeConstraintSoft mk(decl.ITypeConstraintSoft *hndl, bool owned=True):
        ret = TypeConstraintSoft()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeConstraintUnique(TypeConstraint):
    
    cpdef getExprs(self):
        ret = []
        for i in range(self.asUnique().getExprs().size()):
            ret.append(TypeExpr.mk(
                self.asUnique().getExprs().at(i).get(),
                False))
        return ret
    
    cdef decl.ITypeConstraintUnique *asUnique(self):
        return dynamic_cast[decl.ITypeConstraintUniqueP](self._hndl)
    
    @staticmethod
    cdef TypeConstraintUnique mk(decl.ITypeConstraintUnique *hndl, bool owned=True):
        ret = TypeConstraintUnique()
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

cdef class TypeExprArrayLiteral(TypeExpr):
    cdef decl.ITypeExprArrayLiteral *asArrayLiteral(self):
        return dynamic_cast[decl.ITypeExprArrayLiteralP](self._hndl)
    @staticmethod
    cdef TypeExprArrayLiteral mk(decl.ITypeExprArrayLiteral *hndl, bool owned=True):
        ret = TypeExprArrayLiteral()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExprArrIndex(TypeExpr):
    cdef decl.ITypeExprArrIndex *asArrIndex(self):
        return dynamic_cast[decl.ITypeExprArrIndexP](self._hndl)
    @staticmethod
    cdef TypeExprArrIndex mk(decl.ITypeExprArrIndex *hndl, bool owned=True):
        ret = TypeExprArrIndex()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExprRefBottomUp(TypeExpr):
    cdef decl.ITypeExprRefBottomUp *asRefBottomUp(self):
        return dynamic_cast[decl.ITypeExprRefBottomUpP](self._hndl)
    @staticmethod
    cdef TypeExprRefBottomUp mk(decl.ITypeExprRefBottomUp *hndl, bool owned=True):
        ret = TypeExprRefBottomUp()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExprRefInline(TypeExpr):
    cdef decl.ITypeExprRefInline *asRefInline(self):
        return dynamic_cast[decl.ITypeExprRefInlineP](self._hndl)
    @staticmethod
    cdef TypeExprRefInline mk(decl.ITypeExprRefInline *hndl, bool owned=True):
        ret = TypeExprRefInline()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExprRefPath(TypeExpr):
    cdef decl.ITypeExprRefPath *asRefPath(self):
        return dynamic_cast[decl.ITypeExprRefPathP](self._hndl)
    @staticmethod
    cdef TypeExprRefPath mk(decl.ITypeExprRefPath *hndl, bool owned=True):
        ret = TypeExprRefPath()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExprRefTopDown(TypeExpr):
    cdef decl.ITypeExprRefTopDown *asRefTopDown(self):
        return dynamic_cast[decl.ITypeExprRefTopDownP](self._hndl)
    @staticmethod
    cdef TypeExprRefTopDown mk(decl.ITypeExprRefTopDown *hndl, bool owned=True):
        ret = TypeExprRefTopDown()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExprStructLiteral(TypeExpr):
    cdef decl.ITypeExprStructLiteral *asStructLiteral(self):
        return dynamic_cast[decl.ITypeExprStructLiteralP](self._hndl)
    @staticmethod
    cdef TypeExprStructLiteral mk(decl.ITypeExprStructLiteral *hndl, bool owned=True):
        ret = TypeExprStructLiteral()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExprSubField(TypeExpr):
    cdef decl.ITypeExprSubField *asSubField(self):
        return dynamic_cast[decl.ITypeExprSubFieldP](self._hndl)
    @staticmethod
    cdef TypeExprSubField mk(decl.ITypeExprSubField *hndl, bool owned=True):
        ret = TypeExprSubField()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExprUnary(TypeExpr):
    cdef decl.ITypeExprUnary *asUnary(self):
        return dynamic_cast[decl.ITypeExprUnaryP](self._hndl)
    @staticmethod
    cdef TypeExprUnary mk(decl.ITypeExprUnary *hndl, bool owned=True):
        ret = TypeExprUnary()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExprRef(TypeExpr):
    cpdef TypeExpr getTarget(self):
        cdef decl.ITypeExpr *t = self.asRef().getTarget()
        if t != NULL:
            return TypeExpr.mk(t, False)
        else:
            return None

    # cpdef bint owned(self):
    #     return self.asRef().owned()

    cdef decl.ITypeExprRef *asRef(self):
        return dynamic_cast[decl.ITypeExprRefP](self._hndl)

    @staticmethod
    cdef TypeExprRef mk(decl.ITypeExprRef *hndl, bool owned=True):
        ret = TypeExprRef()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExpr(ObjBase):
    
    cdef decl.ITypeExpr *asExpr(self):
        return dynamic_cast[decl.ITypeExprP](self._hndl)
            
    @staticmethod
    cdef TypeExpr mk(decl.ITypeExpr *hndl, bool owned=True):
        return WrapperBuilder().mkObj(hndl, owned)
    
cdef class TypeExprRange(TypeExpr):

    cpdef isSingle(self):
        return self.asRange().isSingle()

    cpdef TypeExpr lower(self):
        cdef decl.ITypeExpr *e = self.asRange().lower()
        
        if e != NULL:
            return TypeExpr.mk(e, False)
        else:
            return None
    
    cpdef TypeExpr upper(self):
        cdef decl.ITypeExpr *e = self.asRange().upper()
        
        if e != NULL:
            return TypeExpr.mk(e, False)
        else:
            return None
        
    cdef decl.ITypeExprRange *asRange(self):
        return dynamic_cast[decl.ITypeExprRangeP](self._hndl)
      
    @staticmethod
    cdef TypeExprRange mk(decl.ITypeExprRange *hndl, bool owned=True):
        ret = TypeExprRange()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeExprRangelist(TypeExpr):
    
    cpdef addRange(self, TypeExprRange r):
        if not r._owned:
            raise Exception("Range must own its data")
        r._owned = False
        self.asRangelist().addRange(r.asRange())
    
    cpdef getRanges(self):
        cdef decl.ITypeExprRangelist *rl = self.asRangelist()
        ret = []
        for i in range(self.asRangelist().getRanges().size()):
            ret.append(TypeExprRange.mk(
                self.asRangelist().getRanges().at(i).get(),
                False))
        return ret
    
    cdef decl.ITypeExprRangelist *asRangelist(self):
        return dynamic_cast[decl.ITypeExprRangelistP](self._hndl)

    @staticmethod
    cdef TypeExprRangelist mk(decl.ITypeExprRangelist *hndl, bool owned=True):
        ret = TypeExprRangelist()
        if hndl == NULL:
            raise Exception("Attempting to create null TypeExprRangelist")
        ret._hndl = hndl
        ret._owned = owned
        return ret


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

cdef class TypeExprEnumRef(TypeExpr):

    cpdef DataTypeEnum getEnumType(self):
        return DataTypeEnum.mk(self.asEnumRef().getEnumType(), False)

    cpdef int32_t getEnumeratorId(self):
        return self.asEnumRef().getEnumeratorId()

    cdef decl.ITypeExprEnumRef *asEnumRef(self):
        return dynamic_cast[decl.ITypeExprEnumRefP](self._hndl)

    @staticmethod
    cdef TypeExprEnumRef mk(decl.ITypeExprEnumRef *hndl, bool owned=True):
        ret = TypeExprEnumRef()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
class TypeExprFieldRef_RootRefKind(IntEnum):
    TopDownScope  = decl.TypeExprFieldRef_RootRefKind.TypeExprFieldRef_TopDownScope
    BottomUpScope = decl.TypeExprFieldRef_RootRefKind.TypeExprFieldRef_BottomUpScope

cdef class TypeExprFieldRef(TypeExpr):

    # cpdef getRootRefKind(self):
    #     pass

    # cpdef addPathElem(self, int32_t idx):
    #     self.asFieldRef().addPathElem(idx)
        
    # cpdef uint32_t size(self):
    #     return self.asFieldRef().size()
    
    # cpdef int32_t at(self, idx):
    #     return self.asFieldRef().getPath().at(idx)

    # cpdef getPath(self):
    #     pass
    
    @staticmethod
    cdef TypeExprFieldRef mk(decl.ITypeExprFieldRef *hndl, bool owned=True):
        ret = TypeExprFieldRef()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
    cdef decl.ITypeExprFieldRef *asFieldRef(self):
        return dynamic_cast[decl.ITypeExprFieldRefP](self._hndl)

cdef class TypeExprVal(TypeExpr):
    cpdef ValRef val(self):
        print("TODO: TypeExprVal.val")
        return None
#        return ModelVal.mk(
#            const_cast[decl.IModelValP](self.asVal().val()), 
#            False)
    
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
    
cdef class TypeField(ObjBase):

    cpdef TypeField getParent(self):
        cdef decl.ITypeField *p = self.asField().getParent()
        if p != NULL:
            return WrapperBuilder().mkObj(p, False)
        else:
            return None

    cpdef setParent(self, TypeField p):
        self.asField().setParent(p.asField())
        
    cpdef getIndex(self):
        return self.asField().getIndex()
    
    cpdef setIndex(self, idx):
        self.asField().setIndex(idx)
        
    cpdef name(self):
        return self.asField().name().decode()
    
    cpdef DataType getDataType(self):
        cdef decl.IDataType *t = self.asField().getDataType()
        if t != NULL:
            return DataType.mk(t, False)
        else:
            return None
        
    cpdef TypeField getField(self, idx):
        return WrapperBuilder().mkObj(self.asField().getField(idx), False)
        
    cpdef getAttr(self):
        return 0

    cdef decl.ITypeField *asField(self):
        return dynamic_cast[decl.ITypeFieldP](self._hndl)
    
    @staticmethod
    cdef mk(decl.ITypeField *hndl, bool owned=True):
        ret = TypeField()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class TypeFieldPhy(TypeField):

    cpdef ValRef getInit(self):
        print("TODO: TypeFieldPhy.getInit")
#        cdef decl.IModelVal *i = self.asPhy().getInit()
#        
#        if i != NULL:
#            return ModelVal.mk(i, False)
#        else:
#            return None
        
    cdef decl.ITypeFieldPhy *asPhy(self):
        return dynamic_cast[decl.ITypeFieldPhyP](self._hndl)

    @staticmethod
    cdef mk(decl.ITypeFieldPhy *hndl, bool owned=True):
        ret = TypeFieldPhy()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeFieldRef(TypeField):

    @staticmethod
    cdef mk(decl.ITypeFieldRef *hndl, bool owned=True):
        ret = TypeFieldRef()
        ret._hndl = hndl
        ret._owned = owned
        return ret    
    
#********************************************************************
#* Task
#********************************************************************
cdef class Task(object):
    cpdef apply(self, Accept it):
        pass

cdef class ValRef(object):
    cpdef bool valid(self):
        return self.val.valid()
    
    cpdef DataType type(self):
        cdef decl.IDataType *t = self.val.type()

        if t == NULL:
            return None
        else:
            return DataType.mk(t, False)

    cpdef int vp(self):
        return self.val.vp()

    cpdef ValIterator iterator(self):
        return ValIterator.mk(self.val.iterator(), True)

    @staticmethod
    cdef mk(const decl.ValRef &v, bool owned=False):
        ret = ValRef()
        ret.val = v
        return ret

cdef class ValRefInt(ValRef):

    cpdef bool is_signed(self):
        cdef decl.ValRefInt vi = decl.ValRefInt(self.val)
        return vi.is_signed()

    cpdef int get_val_s(self):
        cdef decl.ValRefInt vi = decl.ValRefInt(self.val)
        return vi.get_val_s()

    cpdef int get_val_u(self):
        cdef decl.ValRefInt vi = decl.ValRefInt(self.val)
        return vi.get_val_u()

    cpdef set_val(self, int v):
        cdef decl.ValRefInt vi = decl.ValRefInt(self.val)
        vi.set_val(v)

    @staticmethod
    def fromValRef(ValRef v):
        cdef ValRefInt ret = ValRefInt()
        ret.val = v.val
        return ret

cdef class ValRefPtr(ValRef):
    cpdef uintptr_t get_val(self):
        cdef decl.ValRefPtr vp = decl.ValRefPtr(self.val)
        return vp.get_val()

    cpdef void set_val(self, uintptr_t v):
        cdef decl.ValRefPtr vp = decl.ValRefPtr(self.val)
        vp.set_val(v)

    @staticmethod
    def fromValRef(ValRef v):
        cdef ValRefPtr ret = ValRefPtr()
        ret.val = v.val
        return ret

cdef class ValRefStruct(ValRef):

    cpdef int getNumFields(self):
        cdef decl.ValRefStruct vs = decl.ValRefStruct(self.val)
        return vs.getNumFields()

    cpdef ValRef getFieldRef(self, int i):
        cdef decl.ValRefStruct vs = decl.ValRefStruct(self.val)
        return ValRef.mk(vs.getFieldRef(i))

    @staticmethod
    def fromValRef(ValRef v):
        cdef ValRefStruct ret = ValRefStruct()
        ret.val = v.val
        return ret

cdef class ValIterator(object):
    cpdef void reset(self):
        self._hndl.reset()

    cpdef DataType getDataType(self):
        cdef decl.IDataType *t = self._hndl.getDataType()
        return DataType.mk(t, False)

    cpdef ValRef getVal(self):
        pass

    cpdef int32_t numFields(self):
        return self._hndl.numFields()

    cpdef DataType getFieldType(self, int32_t idx):
        cdef decl.IDataType *t = self._hndl.getFieldType(idx)
        return DataType.mk(t, False)

    cpdef str getFieldName(self, int32_t idx):
        return self._hndl.getFieldName(idx).decode()

    cpdef bool push(self, int32_t idx):
        return self._hndl.push(idx)

    cpdef bool pop(self):
        return self._hndl.pop()

    @staticmethod
    cdef ValIterator mk(decl.IValIterator *hndl, bool owned=True):
        ret = ValIterator()
        ret._hndl = hndl
        ret._owned = owned
        return ret

#********************************************************************
#* VisitorBase
#********************************************************************
cdef class VisitorBase(object):

    def __init__(self):
        self.proxy_l.push_back(new decl.VisitorProxy(<cpy_ref.PyObject *>(self)))
        
    def __dealloc__(self):
        cdef decl.IVisitorP v
        for i in range(self.proxy_l.size()):
            v = self.proxy_l.at(i)
            del v
            pass
        
    cpdef visit(self, ObjBase obj):
        self._visit_s.push_back(False)
        for i in range(self.proxy_l.size()):
            obj._hndl.accept(self.proxy_l.at(i))
            if self._visit_s.back():
                break
        self._visit_s.pop_back()

    cdef visitAccept(self, decl.IAccept *obj):
        self._visit_s.push_back(False)
        for i in range(self.proxy_l.size()):
            obj.accept(self.proxy_l.at(i))
            if self._visit_s.back():
                break
        self._visit_s.pop_back()

    cpdef enter(self):
        self._visit_s[self._visit_s.size()-1] = True
        self._visit_s.push_back(False)

    cpdef leave(self):
        self._visit_s.pop_back()

    cpdef visitDataType(self, DataType t):
        pass
        
    cpdef visitDataTypeEnum(self, DataTypeEnum t):
        self.visitDataType(t)
    
    cpdef visitDataTypeInt(self, DataTypeInt t):
        self.visitDataType(t)
    
    cpdef visitDataTypeStruct(self, DataTypeStruct t):
        self.visitDataType(t)

    cpdef visitModelConstraintBlock(self, ModelConstraintBlock c):
        pass

    cpdef visitModelConstraintExpr(self, ModelConstraintExpr c):
        pass

    cpdef visitModelConstraintIfElse(self, ModelConstraintIfElse c):
        pass

    cpdef visitModelConstraintImplies(self, ModelConstraintImplies c):
        pass
        
    cpdef visitModelExprBin(self, ModelExprBin e):
        pass

    cpdef visitModelExprCond(self, ModelExprCond e):
        pass

    cpdef visitModelExprFieldRef(self, ModelExprFieldRef e):
        pass

    cpdef visitModelExprIn(self, ModelExprIn e):
        pass

    cpdef visitModelExprPartSelect(self, ModelExprPartSelect e):
        pass

    cpdef visitModelExprRange(self, ModelExprRange e):
        pass

    cpdef visitModelExprRangelist(self, ModelExprRangelist e):
        pass

    cpdef visitModelExprRef(self, ModelExprRef e):
        pass

    cpdef visitModelExprUnary(self, ModelExprUnary e):
        pass

    cpdef visitModelExprVecSubscript(self, ModelExprVecSubscript e):
        pass
        
    cpdef void visitModelFieldRef(self, ModelFieldRef f):
        pass

    cpdef void visitModelFieldRefRoot(self, ModelFieldRef f):
        pass

    cpdef void visitModelFieldRefType(self, ModelFieldTypeRef f):
        pass

    cpdef void visitModelFieldRoot(self, ModelFieldRoot f):
        pass

    cpdef void visitModelFieldType(self, ModelFieldType f):
        pass

    cpdef void visitTypeConstraintBlock(self, TypeConstraintBlock c):
        pass

    cpdef void visitTypeConstraintExpr(self, TypeConstraintExpr c):
        pass

    cpdef void visitTypeConstraintIfElse(self, TypeConstraintIfElse c):
        pass

    cpdef void visitTypeConstraintImplies(self, TypeConstraintImplies c):
        pass

    cpdef void visitTypeConstraintScope(self, TypeConstraintScope c):
        pass

    cpdef void visitTypeExprBin(self, TypeExprBin e):
        pass

    cpdef void visitTypeExprEnumRef(self, TypeExprEnumRef e):
        pass

#    cpdef void visitTypeExprFieldRef(self, TypeExprFieldRef e):
#        pass

    cpdef void visitTypeExprRange(self, TypeExprRange e):
        pass

    cpdef void visitTypeExprRangelist(self, TypeExprRangelist e):
        pass

    cpdef void visitTypeExprVal(self, TypeExprVal e):
        pass
        
cdef public void VisitorProxy_visitDataTypeEnum(obj, decl.IDataTypeEnum *t) with gil:
    obj.enter()
    obj.visitDataTypeEnum(DataTypeEnum.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeInt(obj, decl.IDataTypeInt *t) with gil:
    obj.enter()
    obj.visitDataTypeInt(DataTypeInt.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeStruct(obj, decl.IDataTypeStruct *t) with gil:
    obj.enter()
    obj.visitDataTypeStruct(DataTypeStruct.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitModelConstraintBlock(obj, decl.IModelConstraintBlock *c) with gil:
    obj.visitModelConstraintBlock(ModelConstraintBlock.mk(c, False))

cdef public void VisitorProxy_visitModelConstraintExpr(obj, decl.IModelConstraintExpr *c) with gil:
    obj.visitModelConstraintExpr(ModelConstraintExpr.mk(c, False))

cdef public void VisitorProxy_visitModelConstraintIfElse(obj, decl.IModelConstraintIfElse *c) with gil:
    obj.visitModelConstraintIfElse(ModelConstraintIfElse.mk(c, False))

cdef public void VisitorProxy_visitModelConstraintImplies(obj, decl.IModelConstraintImplies *c) with gil:
    obj.visitModelConstraintImplies(ModelConstraintImplies.mk(c, False))

cdef public void VisitorProxy_visitModelConstraintScope(obj, decl.IModelConstraintScope *c) with gil:
    obj.visitModelConstraintScope(ModelConstraintScope.mk(c, False))
        
cdef public void VisitorProxy_visitModelExprBin(obj, decl.IModelExprBin *e) with gil:
    obj.visitModelExprBin(ModelExprBin.mk(e, False))

cdef public void VisitorProxy_visitModelExprCond(obj, decl.IModelExprCond *e) with gil:
    obj.visitModelExprCond(ModelExprCond.mk(e, False))

cdef public void VisitorProxy_visitModelExprFieldRef(obj, decl.IModelExprFieldRef *e) with gil:
    obj.visitModelExprFieldRef(ModelExprFieldRef.mk(e, False))

cdef public void VisitorProxy_visitModelExprIn(obj, decl.IModelExprIn *e) with gil:
    obj.visitModelExprIn(ModelExprIn.mk(e, False))

cdef public void VisitorProxy_visitModelExprPartSelect(obj, decl.IModelExprPartSelect *e) with gil:
    obj.visitModelExprPartSelect(ModelExprPartSelect.mk(e, False))

cdef public void VisitorProxy_visitModelExprRange(obj, decl.IModelExprRange *e) with gil:
    obj.visitModelExprRange(ModelExprRange.mk(e, False))

cdef public void VisitorProxy_visitModelExprRangelist(obj, decl.IModelExprRangelist *e) with gil:
    obj.visitModelExprRangelist(ModelExprRangelist.mk(e, False))

cdef public void VisitorProxy_visitModelExprRef(obj, decl.IModelExprRef *e) with gil:
    obj.visitModelExprRef(ModelExprRef.mk(e, False))

cdef public void VisitorProxy_visitModelExprUnary(obj, decl.IModelExprUnary *e) with gil:
    obj.visitModelExprUnary(ModelExprUnary.mk(e, False))

cdef public void VisitorProxy_visitModelExprVecSubscript(obj, decl.IModelExprVecSubscript *e) with gil:
    obj.visitModelExprVecSubscript(ModelExprVecSubscript.mk(e, False))
    
cdef public void VisitorProxy_visitModelFieldRef(obj, decl.IModelFieldRef *f) with gil:
    obj.visitModelFieldRef(ModelFieldRef.mk(f, False))

cdef public void VisitorProxy_visitModelFieldRefRoot(obj, decl.IModelFieldRef *f) with gil:
    obj.visitModelFieldRefRoot(ModelFieldRef.mk(f, False))

cdef public void VisitorProxy_visitModelFieldRefType(obj, decl.IModelFieldTypeRef *f) with gil:
    obj.visitModelFieldRefType(ModelFieldTypeRef.mk(f, False))

cdef public void VisitorProxy_visitModelFieldRoot(obj, decl.IModelFieldRoot *f) with gil:
    obj.visitModelFieldRoot(ModelFieldRoot.mk(f, False))

cdef public void VisitorProxy_visitModelFieldType(obj, decl.IModelFieldType *f) with gil:
    obj.visitModelFieldType(ModelFieldType.mk(f, False))
    
cdef public void VisitorProxy_visitTypeConstraintBlock(obj, decl.ITypeConstraintBlock *c) with gil:
    obj.visitTypeConstraintBlock(TypeConstraintBlock.mk(c, False))

cdef public void VisitorProxy_visitTypeConstraintExpr(obj, decl.ITypeConstraintExpr *c) with gil:
    obj.visitTypeConstraintExpr(TypeConstraintExpr.mk(c, False))

cdef public void VisitorProxy_visitTypeConstraintIfElse(obj, decl.ITypeConstraintIfElse *c) with gil:
    obj.visitTypeConstraintIfElse(TypeConstraintIfElse.mk(c, False))

cdef public void VisitorProxy_visitTypeConstraintImplies(obj, decl.ITypeConstraintImplies *c) with gil:
    obj.visitTypeConstraintImplies(TypeConstraintImplies.mk(c, False))

cdef public void VisitorProxy_visitTypeConstraintScope(obj, decl.ITypeConstraintScope *c) with gil:
    obj.visitTypeConstraintScope(TypeConstraintScope.mk(c, False))

cdef public void VisitorProxy_visitTypeExprBin(obj, decl.ITypeExprBin *c) with gil:
    obj.visitTypeExprBin(TypeExprBin.mk(c, False))

cdef public void VisitorProxy_visitTypeExprEnumRef(obj, decl.ITypeExprEnumRef *c) with gil:
    obj.visitTypeExprEnumRef(TypeExprEnumRef.mk(c, False))

cdef public void VisitorProxy_visitTypeExprFieldRef(obj, decl.ITypeExprFieldRef *c) with gil:
#    obj.visitTypeExprFieldRef(TypeExprFieldRef.mk(c, False))
    pass

cdef public void VisitorProxy_visitTypeExprRange(obj, decl.ITypeExprRange *c) with gil:
    obj.visitTypeExprRange(TypeExprRange.mk(c, False))

cdef public void VisitorProxy_visitTypeExprRangelist(obj, decl.ITypeExprRangelist *c) with gil:
    obj.visitTypeExprRangelist(TypeExprRangelist.mk(c, False))

cdef public void VisitorProxy_visitTypeExprVal(obj, decl.ITypeExprVal *c) with gil:
    obj.visitTypeExprVal(TypeExprVal.mk(c, False))
        
#********************************************************************
#* Factory
#********************************************************************
cdef Factory _inst = None
cdef class Factory(object):
    
    def __init__(self):
        pass

    cdef init(self, dm_core.Factory f):
        self._hndl.init(f._hndl.getDebugMgr())

    @staticmethod
    def inst():
        cdef decl.IFactory *hndl = NULL
        cdef Factory factory
        global _inst
        if _inst is None:
            ext_dir = os.path.dirname(os.path.abspath(__file__))

            build_dir = os.path.abspath(os.path.join(ext_dir, "../../build"))

            core_lib = None
            libname = "libvsc-dm.so"
            for libdir in ("lib", "lib64"):
                if os.path.isfile(os.path.join(build_dir, libdir, libname)):
                    core_lib = os.path.join(build_dir, libdir, libname)
                    break

            if core_lib is None:
                core_lib = os.path.join(ext_dir, libname)

            if not os.path.isfile(core_lib):
                raise Exception("Extension library core \"%s\" doesn't exist" % core_lib)
            
            so = ctypes.cdll.LoadLibrary(core_lib)
            func = so.vsc_dm_getFactory
            func.restype = ctypes.c_void_p

            hndl = <decl.IFactoryP>(<intptr_t>(func()))
            factory = Factory()
            factory._hndl = hndl
            factory.init(dm_core.Factory.inst())
            _inst = factory

        return _inst

    cpdef dm_core.DebugMgr getDebugMgr(self):
        return dm_core.DebugMgr.mk(self._hndl.getDebugMgr(), False)
        
    cpdef Context mkContext(self):
        return Context.mk(self._hndl.mkContext(), True)
    
#********************************************************************    
#* WrapperBuilder
#********************************************************************
cdef class WrapperBuilder(VisitorBase):
    
    def __init__(self):
        super().__init__()
        self._obj = []

    cdef ObjBase mkObj(self, decl.IAccept *obj, bool owned):
        global _WrapperBuilderList
        cdef ObjBase ret = None
        cdef WrapperBuilder builder

        if obj == NULL:
            return None

        self._obj.append(None)
        self.visitAccept(obj)
        ret = self._obj.pop()

        if ret is None:
            for i,b in enumerate(_WrapperBuilderList):
                builder = <WrapperBuilder>b
                ret = builder.mkObj(obj, owned)
                if ret is not None:
                    break
        else:
            ret._owned = owned

        if ret is None and obj != NULL:
            print("mkObj: Failed")
            raise Exception("Failed to wrap object")

        return ret

    cdef _set_obj(self, ObjBase obj):
        self._obj[-1] = obj

    cpdef visitDataTypeEnum(self, DataTypeEnum t):
        self._set_obj(t)
    
    cpdef visitDataTypeInt(self, DataTypeInt t):
        self._set_obj(t)
    
    cpdef visitDataTypeStruct(self, DataTypeStruct t):
        self._set_obj(t)

    cpdef visitModelConstraintBlock(self, ModelConstraintBlock c):
        self._set_obj(c)

    cpdef visitModelConstraintExpr(self, ModelConstraintExpr c):
        self._set_obj(c)

    cpdef visitModelConstraintIfElse(self, ModelConstraintIfElse c):
        self._set_obj(c)

    cpdef visitModelConstraintImplies(self, ModelConstraintImplies c):
        self._set_obj(c)

    cpdef visitModelExprBin(self, ModelExprBin e):
        self._set_obj(e)

    cpdef visitModelExprCond(self, ModelExprCond e):
        self._set_obj(e)

    cpdef visitModelExprFieldRef(self, ModelExprFieldRef e):
        self._set_obj(e)

    cpdef visitModelExprIn(self, ModelExprIn e):
        self._set_obj(e)

    cpdef visitModelExprPartSelect(self, ModelExprPartSelect e):
        self._set_obj(e)

    cpdef visitModelExprRange(self, ModelExprRange e):
        self._set_obj(e)

    cpdef visitModelExprRangelist(self, ModelExprRangelist e):
        self._set_obj(e)

    cpdef visitModelExprRef(self, ModelExprRef e):
        self._set_obj(e)

    cpdef visitModelExprUnary(self, ModelExprUnary e):
        self._set_obj(e)

    cpdef visitModelExprVecSubscript(self, ModelExprVecSubscript e):
        self._set_obj(e)
        
    cpdef void visitModelFieldRef(self, ModelFieldRef f):
        self._set_obj(f)

    cpdef void visitModelFieldRefRoot(self, ModelFieldRef f):
        self._set_obj(f)

    cpdef void visitModelFieldRefType(self, ModelFieldTypeRef f):
        self._set_obj(f)

    cpdef void visitModelFieldRoot(self, ModelFieldRoot f):
        self._set_obj(f)

    cpdef void visitModelFieldType(self, ModelFieldType f):
        self._set_obj(f)

    cpdef void visitTypeConstraintBlock(self, TypeConstraintBlock c):
        self._type_constraint = c

    cpdef void visitTypeConstraintExpr(self, TypeConstraintExpr c):
        self._type_constraint = c

    cpdef void visitTypeConstraintIfElse(self, TypeConstraintIfElse c):
        self._type_constraint = c

    cpdef void visitTypeConstraintImplies(self, TypeConstraintImplies c):
        self._type_constraint = c

    cpdef void visitTypeConstraintScope(self, TypeConstraintScope c):
        self._type_constraint = c

    cpdef void visitTypeExprBin(self, TypeExprBin e):
        self._type_expr = e

    cpdef void visitTypeExprEnumRef(self, TypeExprEnumRef e):
        self._type_expr = e

#    cpdef void visitTypeExprFieldRef(self, TypeExprFieldRef e):
#        self._type_expr = e

    cpdef void visitTypeExprRange(self, TypeExprRange e):
        self._type_expr = e

    cpdef void visitTypeExprRangelist(self, TypeExprRangelist e):
        self._type_expr = e

    cpdef void visitTypeExprVal(self, TypeExprVal e):
        self._type_expr = e

cdef list _WrapperBuilderList = []
cdef _WrapperBuilderInst = None

cpdef addWrapperBuilder(WrapperBuilder builder):
    global _WrapperBuilderList
    _WrapperBuilderList.append(builder)

        
#********************************************************************    
#* VscTasks
#********************************************************************
cpdef ModelField Task_ModelBuildField(Context ctxt, DataType dt, name):
    return ModelField.mk(decl.Task_BuildModelField(
        ctxt._hndl,
        dt.asType(),
        name.encode()),
        True)

cpdef enableDebug(bool en):
    factory = Factory.inst()
    factory.getDebugMgr().enable(en)
