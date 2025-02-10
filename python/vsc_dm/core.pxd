
cimport debug_mgr.core as dm_core
from vsc_dm cimport decl
from libc.stdint cimport intptr_t
from libc.stdint cimport uintptr_t
from libc.stdint cimport int32_t
from libc.stdint cimport uint32_t
from libc.stdint cimport uint64_t
from libc.stdint cimport int64_t
from libcpp cimport bool
from libcpp.vector cimport vector as cpp_vector
from enum import IntFlag, IntEnum
cimport cpython.ref as cpy_ref

   
cdef class Context(object):
    cdef decl.IContext               *_hndl
    cdef bool                        _owned

    cpdef ModelBuildContext mkModelBuildContext(self, Context ctxt)
    cpdef ModelField buildModelField(self, DataTypeStruct, name=*)
    cpdef DataTypeEnum findDataTypeEnum(self, name)
    cpdef DataTypeEnum mkDataTypeEnum(self,
        name,
        bool is_signed)
    cpdef addDataTypeEnum(self, DataTypeEnum)
    cpdef mkModelConstraintBlock(self, name)
    cpdef mkModelConstraintExpr(self, ModelExpr)
    cpdef mkModelConstraintIfElse(self, 
        ModelExpr           cond,
        ModelConstraint     true_c,
        ModelConstraint     false_c)
    cpdef mkModelConstraintImplies(self, 
        ModelExpr           cond,
        ModelConstraint     body)
    cpdef mkModelConstraintScope(self)
    cpdef ModelConstraintSoft mkModelConstraintSoft(self, ModelConstraintExpr c)
    cpdef ModelConstraintUnique mkModelConstraintUnique(self, exprs)
    cpdef bool addDataTypeInt(self, DataTypeInt)
    cpdef DataTypeInt findDataTypeInt(self, bool is_signed, int width)
    cpdef DataTypeInt mkDataTypeInt(self, bool is_signed, int width)
    cpdef bool addDataTypeStruct(self, DataTypeStruct)
    cpdef getDataTypeStructs(self)
    cpdef DataTypeStruct findDataTypeStruct(self, name)
    cpdef DataTypeStruct mkDataTypeStruct(self, name)
    cpdef mkModelExprBin(self, ModelExpr, op, ModelExpr)
    cpdef mkModelExprIn(self, ModelExpr, ModelExprRangelist)
    cpdef mkModelExprFieldRef(self, ModelField field)
    cpdef mkModelExprPartSelect(self, ModelExpr lhs, int32_t lower, int32_t upper)
    cpdef mkModelExprRange(self, bool, ModelExpr, ModelExpr)
    cpdef mkModelExprRangelist(self)
    cpdef mkModelFieldRoot(self, DataType type, name)
    cpdef mkModelFieldVecRoot(self, DataType type, name)
    cpdef TypeConstraintBlock mkTypeConstraintBlock(self, name)
    cpdef TypeConstraintExpr mkTypeConstraintExpr(self, TypeExpr)
    cpdef TypeConstraintIfElse mkTypeConstraintIfElse(self, 
        TypeExpr        cond,
        TypeConstraint  true_c,
        TypeConstraint  false_c)
    cpdef TypeConstraintImplies mkTypeConstraintImplies(self, 
        TypeExpr        cond,
        TypeConstraint  body)
    cpdef TypeConstraintScope mkTypeConstraintScope(self)
    cpdef TypeConstraintSoft mkTypeConstraintSoft(self, TypeConstraintExpr c)
    cpdef TypeConstraintUnique mkTypeConstraintUnique(self, exprs)
    cpdef TypeExprBin mkTypeExprBin(self, TypeExpr, op, TypeExpr)
    cpdef TypeExprEnumRef mkTypeExprEnumRef(self, DataTypeEnum, int32_t)
#    cpdef TypeExprFieldRef mkTypeExprFieldRef(self, root_kind, int32_t root_idx)
    cpdef TypeExprRange mkTypeExprRange(self, bool, TypeExpr, TypeExpr)
    cpdef TypeExprRangelist mkTypeExprRangelist(self)
    cpdef TypeExprVal mkTypeExprVal(self, ValRef v)
    cpdef TypeFieldPhy mkTypeFieldPhy(self, name, DataType, bool, attr, TypeExpr)
    cpdef TypeFieldRef mkTypeFieldRef(self, name, DataType, attr)
    cpdef ValRefInt mkValRefInt(self, int value, bool is_signed, int width)
    cpdef ValRefStruct mkValRefStruct(self, DataTypeStruct t)

    @staticmethod    
    cdef mk(decl.IContext *hndl, bool owned=*)

cdef class ModelBuildContext(object):
    cdef decl.IModelBuildContext    *_hndl

    cpdef Context ctxt(self)


#    @staticmethod
#    cpdef ModelBuildContext mk(Context ctxt)

cdef class Accept(object):
    cdef decl.IAccept *hndl(self)

cdef class ObjBase(object):
    cdef decl.IAccept           *_hndl
    cdef bool                   _owned

cdef class DataType(ObjBase):

    cpdef ModelField mkRootField(
        self,
        ModelBuildContext   ctxt,
        str                 name,
        bool                is_ref)

    cpdef ModelField mkTypeField(
        self,
        ModelBuildContext   ctxt,
        TypeField           type,
        ValRef              val)

    cdef decl.IDataType *asType(self)

    cpdef void setAssociatedData(self, obj)

    cpdef object getAssociatedData(self)

    @staticmethod
    cdef mk(decl.IDataType *, bool owned=*)
    
cdef class DataTypeEnum(DataType):

    cpdef name(self)
    
    cpdef isSigned(self)
    
#    cpdef addEnumerator(self, name, ModelVal val)
    
    cpdef getDomain(self)
    
    cdef decl.IDataTypeEnum *asEnum(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeEnum *, bool owned=*)

cdef class DataTypeInt(DataType):

    cpdef bool is_signed(self)

    cpdef int width(self)

    @staticmethod
    cdef mk(decl.IDataTypeInt *, bool owned=*)
    
    cdef decl.IDataTypeInt *asTypeInt(self)
    
cdef class DataTypeStruct(DataType):

    cpdef name(self)
    cpdef addField(self, TypeField f)
    cpdef getFields(self)
    cpdef TypeField getField(self, int32_t idx)
    cpdef addConstraint(self, TypeConstraint c)
    cpdef getConstraints(self)
    cpdef setCreateHook(self, hook_f)

    @staticmethod
    cdef mk(decl.IDataTypeStruct *, bool owned=*)

    cdef decl.IDataTypeStruct *asTypeStruct(self)

cdef class Factory(object):
    cdef decl.IFactory              *_hndl

    cdef init(self, dm_core.Factory)
    cpdef Context mkContext(self)
    cpdef dm_core.DebugMgr getDebugMgr(self)

cdef class ModelConstraint(ObjBase):

    cdef decl.IModelConstraint *asConstraint(self)
    
    @staticmethod
    cdef mk(decl.IModelConstraint *hndl, bool owned=*)
    
cdef class ModelConstraintScope(ModelConstraint):
    cpdef getConstraints(self)
    cpdef addConstraint(self, ModelConstraint)
    
    cdef decl.IModelConstraintScope *asScope(self)

    @staticmethod
    cdef mk(decl.IModelConstraintScope *hndl, bool owned=*)

cdef class ModelConstraintSoft(ModelConstraint):
    cpdef ModelConstraintExpr constraint(self)
    
    cdef decl.IModelConstraintSoft *asSoft(self)

    @staticmethod
    cdef mk(decl.IModelConstraintSoft *hndl, bool owned=*)

cdef class ModelConstraintUnique(ModelConstraint):
    cpdef getExprs(self)
    
    cdef decl.IModelConstraintUnique *asUnique(self)

    @staticmethod
    cdef mk(decl.IModelConstraintUnique *hndl, bool owned=*)
    
    
cdef class ModelConstraintBlock(ModelConstraintScope):
    cpdef name(self)
    
    cdef decl.IModelConstraintBlock *asModelConstraintBlock(self)
    
    @staticmethod
    cdef mk(decl.IModelConstraintBlock *hndl, bool owned=*)
    
   
cdef class ModelConstraintExpr(ModelConstraint):

    cpdef expr(self)

    cdef decl.IModelConstraintExpr *asExpr(self)
    @staticmethod
    cdef mk(decl.IModelConstraintExpr *, bool owned=*)

cdef class ModelConstraintIfElse(ModelConstraint):
    cpdef getCond(self)
    cpdef getTrue(self)
    cpdef getFalse(self)
    cpdef setFalse(self, ModelConstraint c)

    cdef decl.IModelConstraintIfElse *asIfElse(self)
    @staticmethod
    cdef mk(decl.IModelConstraintIfElse *, bool owned=*)

cdef class ModelConstraintImplies(ModelConstraint):
    cpdef getCond(self)
    cpdef getBody(self)

    cdef decl.IModelConstraintImplies *asImplies(self)

    @staticmethod
    cdef mk(decl.IModelConstraintImplies *hndl, bool owned=*)
    
cdef class ModelExpr(ObjBase):
    
    cdef decl.IModelExpr *asExpr(self)
    
    @staticmethod
    cdef mk(decl.IModelExpr *e, bool owned=*)


cdef class ModelExprBin(ModelExpr):

    @staticmethod
    cdef mk(decl.IModelExprBin *hndl, bool owned=*)

    cdef decl.IModelExprBin *asExprBin(self)

cdef class ModelExprCond(ModelExpr):

    cpdef getCond(self)
    cpdef getTrue(self)
    cpdef getFalse(self)

    cdef decl.IModelExprCond *asCond(self)

    @staticmethod
    cdef mk(decl.IModelExprCond *hndl, bool owned=*)
    
cdef class ModelExprIn(ModelExpr):

    @staticmethod
    cdef mk(decl.IModelExprIn *e, bool owned=*)
    
    cdef decl.IModelExprIn *asExprIn(self)

    
cdef class ModelExprFieldRef(ModelExpr):

    cpdef field(self)

    cdef decl.IModelExprFieldRef *asExprFieldRef(self)
    
    @staticmethod
    cdef mk(decl.IModelExprFieldRef *, bool owned=*)
    
cdef class ModelExprPartSelect(ModelExpr):

    cpdef lhs(self)
    
    cpdef int32_t lower(self)
    
    cpdef int32_t upper(self)
    
    cdef decl.IModelExprPartSelect *asPartSelect(self)
    
    @staticmethod
    cdef mk(decl.IModelExprPartSelect *, bool owned=*)
    
cdef class ModelExprRange(ModelExpr):
    cpdef isSingle(self)
    
    cpdef ModelExpr lower(self)
    
    cpdef ModelExpr upper(self)
    
    cdef decl.IModelExprRange *asRange(self)
    
    @staticmethod 
    cdef mk(decl.IModelExprRange *, bool owned=*)
    
cdef class ModelExprRangelist(ModelExpr): 
    
    cpdef ranges(self)
    
    cpdef addRange(self, ModelExprRange)
    
    cdef decl.IModelExprRangelist *asRangelist(self)
    
    @staticmethod 
    cdef mk(decl.IModelExprRangelist *, bool owned=*)

cdef class ModelExprRef(ModelExpr): 
    cpdef expr(self)

    cdef decl.IModelExprRef *asRef(self)

    @staticmethod
    cdef mk(decl.IModelExprRef *hndl, bool owned=*)
    
cdef class ModelExprUnary(ModelExpr):

    cpdef ModelExpr expr(self)
    cpdef op(self)
    
    cdef decl.IModelExprUnary *asUnary(self)
    
    @staticmethod
    cdef mk(decl.IModelExprUnary *, bool owned=*)
        
cdef class ModelExprVecSubscript(ModelExpr):

    cpdef expr(self)
    cpdef subscript(self)
    
    cdef decl.IModelExprVecSubscript *asVecSubscript(self)
    
    @staticmethod
    cdef mk(decl.IModelExprVecSubscript *, bool owned=*)

cdef class ModelField(ObjBase):

    cpdef name(self)
    cpdef getDataType(self)
    cpdef getParent(self)
    cpdef setParent(self, ModelField)
    cpdef getConstraints(self)
    cpdef addConstraint(self, ModelConstraint)
    cpdef getFields(self)
    cpdef addField(self, ModelField)
    cpdef ModelField getField(self, int32_t idx)
    cpdef val(self)
    
    cpdef clearFlag(self, flags)
    cpdef setFlag(self, flags)
    cpdef isFlagSet(self, flags)
    cpdef setFieldData(self, data)
    cpdef getFieldData(self)

    cdef decl.IModelField *asField(self)

    @staticmethod
    cdef mk(decl.IModelField *, bool owned=*)
    
cdef class ModelFieldRef(ModelField):
    cpdef setRef(self, ModelField r)
    cpdef ModelField getRef(self)

    cdef decl.IModelFieldRef *asRef(self)

    @staticmethod
    cdef mk(decl.IModelFieldRef *hndl, bool owned=*)
    
cdef class ModelFieldRoot(ModelField):

    cpdef setName(self, name)

    cdef decl.IModelFieldRoot *asRoot(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldRoot *, bool owned=*)
    
cdef class ModelFieldType(ModelField):

    cdef decl.IModelFieldType *asType(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldType *, bool owned=*)

cdef class ModelFieldTypeRef(ModelFieldRef):

    cdef decl.IModelFieldTypeRef *asType(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldTypeRef *, bool owned=*)
    
cdef class ModelFieldVec(ModelField):

    cpdef getSizeRef(self)
    
    cpdef getSize(self)
    
    cdef decl.IModelFieldVec *asVec(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldVec *, bool owned=*)
    
cdef class ModelFieldVecRoot(ModelFieldVec):

    cpdef void setName(self, name)

    cdef decl.IModelFieldVecRoot *asVecRoot(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldVecRoot *, bool owned=*)
    
cdef class ModelFieldDataClosure(object):
    cdef decl.IModelFieldData       *_hndl
    
    cpdef getData(self)
    
    @staticmethod
    cdef mk(decl.IModelFieldData *)

cdef class Task(object):
    cdef decl.ITask             *_hndl
    
    cpdef apply(self, Accept it)
    
cdef class TypeConstraint(ObjBase):

    cdef decl.ITypeConstraint *asConstraint(self)
    
    @staticmethod
    cdef TypeConstraint mk(decl.ITypeConstraint *, bool owned=*)

cdef class TypeConstraintExpr(TypeConstraint):

    cpdef TypeExpr expr(self)

    cdef decl.ITypeConstraintExpr *asExpr(self)

    @staticmethod
    cdef TypeConstraintExpr mk(decl.ITypeConstraintExpr *, bool owned=*)

cdef class TypeConstraintIfElse(TypeConstraint):
    cpdef getCond(self)
    cpdef getTrue(self)
    cpdef getFalse(self)
    cpdef setFalse(self, TypeConstraint c)

    cdef decl.ITypeConstraintIfElse *asIfElse(self)

    @staticmethod
    cdef TypeConstraintIfElse mk(decl.ITypeConstraintIfElse *hndl, bool owned=*)

cdef class TypeConstraintImplies(TypeConstraint):
    cpdef getCond(self)
    cpdef getBody(self)

    cdef decl.ITypeConstraintImplies *asImplies(self)

    @staticmethod
    cdef TypeConstraintImplies mk(decl.ITypeConstraintImplies *hndl, bool owned=*)
   
cdef class TypeConstraintScope(TypeConstraint):
    
    cpdef addConstraint(self, TypeConstraint)
    
    cdef decl.ITypeConstraintScope *asScope(self)
    
    @staticmethod
    cdef TypeConstraintScope mk(decl.ITypeConstraintScope *, bool owned=*)

cdef class TypeConstraintSoft(TypeConstraint):
    
    cpdef TypeConstraintExpr constraint(self)
    
    cdef decl.ITypeConstraintSoft *asSoft(self)
    
    @staticmethod
    cdef TypeConstraintSoft mk(decl.ITypeConstraintSoft *, bool owned=*)

cdef class TypeConstraintUnique(TypeConstraint):
    
    cpdef getExprs(self)
    
    cdef decl.ITypeConstraintUnique *asUnique(self)
    
    @staticmethod
    cdef TypeConstraintUnique mk(decl.ITypeConstraintUnique *, bool owned=*)
    
    
cdef class TypeConstraintBlock(TypeConstraintScope):
    
    cpdef name(self)
    
    cdef decl.ITypeConstraintBlock *asBlock(self)
    
    @staticmethod
    cdef TypeConstraintBlock mk(decl.ITypeConstraintBlock *, bool owned=*)

cdef class TypeExpr(ObjBase):

    cdef decl.ITypeExpr *asExpr(self)
    
    @staticmethod
    cdef TypeExpr mk(decl.ITypeExpr *hndl, bool owned=*)
    
cdef class TypeExprRange(TypeExpr):

    cpdef isSingle(self)

    cpdef TypeExpr lower(self)
    
    cpdef TypeExpr upper(self)
  
    cdef decl.ITypeExprRange *asRange(self)
      
    @staticmethod
    cdef TypeExprRange mk(decl.ITypeExprRange *, bool owned=*)

cdef class TypeExprRangelist(TypeExpr):    

    cpdef addRange(self, TypeExprRange r)
    
    cpdef getRanges(self)
    
    cdef decl.ITypeExprRangelist *asRangelist(self)

    @staticmethod
    cdef TypeExprRangelist mk(decl.ITypeExprRangelist *hndl, bool owned=*)
    
cdef class TypeExprBin(TypeExpr):

    cpdef TypeExpr lhs(self)
    cpdef op(self)
    cpdef TypeExpr rhs(self)

    cdef decl.ITypeExprBin *asBin(self)
        
    @staticmethod
    cdef TypeExprBin mk(decl.ITypeExprBin *hndl, bool owned=*)    

cdef class TypeExprEnumRef(TypeExpr):
    cpdef DataTypeEnum getEnumType(self)
    cpdef int32_t getEnumeratorId(self)

    cdef decl.ITypeExprEnumRef *asEnumRef(self)

    @staticmethod
    cdef TypeExprEnumRef mk(decl.ITypeExprEnumRef *hndl, bool owned=*)

cdef class TypeExprFieldRef(TypeExpr):
    # cpdef getRootRefKind(self)
    # cpdef addPathElem(self, int32_t)
    # cpdef uint32_t size(self)
    # cpdef int32_t at(self, idx)
    # cpdef getPath(self)
    
    cdef decl.ITypeExprFieldRef *asFieldRef(self)
    
    @staticmethod
    cdef TypeExprFieldRef mk(decl.ITypeExprFieldRef *hndl, bool owned=*)
    
cdef class TypeExprVal(TypeExpr):
    cpdef ValRef val(self)
    
    cdef decl.ITypeExprVal *asVal(self)
    
    @staticmethod
    cdef TypeExprVal mk(decl.ITypeExprVal *hndl, bool owned=*)
    
cdef class TypeField(ObjBase):
    
    cpdef TypeField getParent(self)
    cpdef setParent(self, TypeField)
    cpdef getIndex(self)
    cpdef setIndex(self, idx)
    cpdef name(self)
    cpdef DataType getDataType(self)
    cpdef TypeField getField(self, idx)
    cpdef getAttr(self)

    cdef decl.ITypeField *asField(self)

    @staticmethod
    cdef mk(decl.ITypeField *, bool owned=*)

cdef class TypeFieldPhy(TypeField):

    cpdef ValRef getInit(self)
    
    cdef decl.ITypeFieldPhy *asPhy(self)
    
    @staticmethod
    cdef mk(decl.ITypeFieldPhy *, bool owned=*)

cdef class TypeFieldRef(TypeField):

    @staticmethod
    cdef mk(decl.ITypeFieldRef *, bool owned=*)    

cdef class ValRef(object):
    cdef decl.ValRef                    val;

    cpdef bool valid(self)

    cpdef DataType type(self)

    cpdef int vp(self)

    cpdef ValIterator iterator(self)

    @staticmethod
    cdef mk(const decl.ValRef &, bool owned=*)

cdef class ValRefInt(ValRef):

    cpdef bool is_signed(self)

    cpdef int get_val_s(self)

    cpdef int get_val_u(self)

    cpdef set_val(self, int v)

cdef class ValRefPtr(ValRef):
    cpdef uintptr_t get_val(self)
    cpdef void set_val(self, uintptr_t v)

cdef class ValRefStruct(ValRef):

    cpdef int getNumFields(self)

    cpdef ValRef getFieldRef(self, int i)

cdef class ValIterator(object):
    cdef decl.IValIterator      *_hndl
    cdef bool                   _owned
    cpdef void reset(self)
    cpdef DataType getDataType(self)
    cpdef ValRef getVal(self)
    cpdef int32_t numFields(self)
    cpdef DataType getFieldType(self, int32_t idx)
    cpdef str getFieldName(self, int32_t idx)
    cpdef bool push(self, int32_t idx)
    cpdef bool pop(self)

    @staticmethod
    cdef ValIterator mk(decl.IValIterator *hndl, bool owned=*)

cdef class VisitorBase(object):
    cdef cpp_vector[bool]               _visit_s
    cdef cpp_vector[decl.IVisitorP]     proxy_l
    
    cpdef visit(self, ObjBase obj)

    cdef visitAccept(self, decl.IAccept *obj)

    cpdef enter(self)

    cpdef leave(self)

    cpdef visitDataType(self, DataType t)
    
    cpdef visitDataTypeEnum(self, DataTypeEnum t)
    
    cpdef visitDataTypeInt(self, DataTypeInt t)
    
    cpdef visitDataTypeStruct(self, DataTypeStruct t)

    cpdef visitModelConstraintBlock(self, ModelConstraintBlock c)

    cpdef visitModelConstraintExpr(self, ModelConstraintExpr c)

    cpdef visitModelConstraintIfElse(self, ModelConstraintIfElse c)

    cpdef visitModelConstraintImplies(self, ModelConstraintImplies c)
    
    cpdef visitModelExprBin(self, ModelExprBin e)

    cpdef visitModelExprCond(self, ModelExprCond e)

    cpdef visitModelExprFieldRef(self, ModelExprFieldRef e)

    cpdef visitModelExprIn(self, ModelExprIn e)

    cpdef visitModelExprPartSelect(self, ModelExprPartSelect e)

    cpdef visitModelExprRange(self, ModelExprRange e)

    cpdef visitModelExprRangelist(self, ModelExprRangelist e)

    cpdef visitModelExprRef(self, ModelExprRef e)

    cpdef visitModelExprUnary(self, ModelExprUnary e)

    cpdef visitModelExprVecSubscript(self, ModelExprVecSubscript e)
    
    cpdef void visitModelFieldRef(self, ModelFieldRef f)

    cpdef void visitModelFieldRefRoot(self, ModelFieldRef f)

    cpdef void visitModelFieldRefType(self, ModelFieldTypeRef f)

    cpdef void visitModelFieldRoot(self, ModelFieldRoot f)

    cpdef void visitModelFieldType(self, ModelFieldType f)

    cpdef void visitTypeConstraintBlock(self, TypeConstraintBlock c)

    cpdef void visitTypeConstraintExpr(self, TypeConstraintExpr c)

    cpdef void visitTypeConstraintIfElse(self, TypeConstraintIfElse c)

    cpdef void visitTypeConstraintImplies(self, TypeConstraintImplies c)

    cpdef void visitTypeConstraintScope(self, TypeConstraintScope c)

    cpdef void visitTypeExprBin(self, TypeExprBin e)

    cpdef void visitTypeExprEnumRef(self, TypeExprEnumRef e)

#    cpdef void visitTypeExprFieldRef(self, TypeExprFieldRef e)

    cpdef void visitTypeExprRange(self, TypeExprRange e)

    cpdef void visitTypeExprRangelist(self, TypeExprRangelist e)

    cpdef void visitTypeExprVal(self, TypeExprVal e)
    
cdef class WrapperBuilder(VisitorBase):
    cdef list     _obj
    cdef DataType _data_type
    cdef ModelExpr _model_expr
    cdef ModelField _model_field
    cdef ModelConstraint _model_constraint
    cdef TypeConstraint _type_constraint
    cdef TypeExpr _type_expr

    cdef ObjBase mkObj(self, decl.IAccept *obj, bool owned)
    
    cdef _set_obj(self, ObjBase obj)

    cpdef visitModelConstraintBlock(self, ModelConstraintBlock c)

    cpdef visitModelConstraintExpr(self, ModelConstraintExpr c)

    cpdef visitModelConstraintIfElse(self, ModelConstraintIfElse c)

    cpdef visitModelConstraintImplies(self, ModelConstraintImplies c)

    cpdef visitModelExprBin(self, ModelExprBin e)

    cpdef visitModelExprCond(self, ModelExprCond e)

    cpdef visitModelExprFieldRef(self, ModelExprFieldRef e)

    cpdef visitModelExprIn(self, ModelExprIn e)

    cpdef visitModelExprPartSelect(self, ModelExprPartSelect e)

    cpdef visitModelExprRange(self, ModelExprRange e)

    cpdef visitModelExprRangelist(self, ModelExprRangelist e)

    cpdef visitModelExprRef(self, ModelExprRef e)

    cpdef visitModelExprUnary(self, ModelExprUnary e)

    cpdef visitModelExprVecSubscript(self, ModelExprVecSubscript e)

    cpdef void visitTypeConstraintBlock(self, TypeConstraintBlock c)

    cpdef void visitTypeConstraintExpr(self, TypeConstraintExpr c)

    cpdef void visitTypeConstraintIfElse(self, TypeConstraintIfElse c)

    cpdef void visitTypeConstraintImplies(self, TypeConstraintImplies c)

    cpdef void visitTypeConstraintScope(self, TypeConstraintScope c)

    cpdef void visitTypeExprBin(self, TypeExprBin e)

#    cpdef void visitTypeExprFieldRef(self, TypeExprFieldRef e)

    cpdef void visitTypeExprRange(self, TypeExprRange e)
 
    cpdef void visitTypeExprRangelist(self, TypeExprRangelist e)

    cpdef void visitTypeExprVal(self, TypeExprVal e)

cpdef addWrapperBuilder(WrapperBuilder builder)
    
#********************************************************************    
#* VscTasks
#********************************************************************
cpdef ModelField Task_ModelBuildField(
    Context     ctxt,
    DataType    dt, 
    name)
