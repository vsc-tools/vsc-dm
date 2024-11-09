
# cdef class Context(object):

#     ModelBuildContext mkModelBuildContext(self, Context ctxt)
#     ModelField buildModelField(self, DataTypeStruct, name=*)
#     DataTypeEnum findDataTypeEnum(self, name)
#     DataTypeEnum mkDataTypeEnum(self,
#         name,
#         bool is_signed)
#     addDataTypeEnum(self, DataTypeEnum)
#     mkModelConstraintBlock(self, name)
#     mkModelConstraintExpr(self, ModelExpr)
#     mkModelConstraintIfElse(self, 
#         ModelExpr           cond,
#         ModelConstraint     true_c,
#         ModelConstraint     false_c)
#     mkModelConstraintImplies(self, 
#         ModelExpr           cond,
#         ModelConstraint     body)
#     mkModelConstraintScope(self)
#     ModelConstraintSoft mkModelConstraintSoft(self, ModelConstraintExpr c)
#     ModelConstraintUnique mkModelConstraintUnique(self, exprs)
#     bool addDataTypeInt(self, DataTypeInt)
#     DataTypeInt findDataTypeInt(self, bool is_signed, int width)
#     DataTypeInt mkDataTypeInt(self, bool is_signed, int width)
#     bool addDataTypeStruct(self, DataTypeStruct)
#     DataTypeStruct findDataTypeStruct(self, name)
#     DataTypeStruct mkDataTypeStruct(self, name)
#     mkModelExprBin(self, ModelExpr, op, ModelExpr)
#     mkModelExprIn(self, ModelExpr, ModelExprRangelist)
#     mkModelExprFieldRef(self, ModelField field)
#     mkModelExprPartSelect(self, ModelExpr lhs, int32_t lower, int32_t upper)
#     mkModelExprRange(self, bool, ModelExpr, ModelExpr)
#     mkModelExprRangelist(self)
#     mkModelFieldRoot(self, DataType type, name)
#     mkModelFieldVecRoot(self, DataType type, name)
#     TypeConstraintBlock mkTypeConstraintBlock(self, name)
#     TypeConstraintExpr mkTypeConstraintExpr(self, TypeExpr)
#     TypeConstraintIfElse mkTypeConstraintIfElse(self, 
#         TypeExpr        cond,
#         TypeConstraint  true_c,
#         TypeConstraint  false_c)
#     TypeConstraintImplies mkTypeConstraintImplies(self, 
#         TypeExpr        cond,
#         TypeConstraint  body)
#     TypeConstraintScope mkTypeConstraintScope(self)
#     TypeConstraintSoft mkTypeConstraintSoft(self, TypeConstraintExpr c)
#     TypeConstraintUnique mkTypeConstraintUnique(self, exprs)
#     TypeExprBin mkTypeExprBin(self, TypeExpr, op, TypeExpr)
# #    TypeExprFieldRef mkTypeExprFieldRef(self, root_kind, int32_t root_idx)
#     TypeExprRange mkTypeExprRange(self, bool, TypeExpr, TypeExpr)
#     TypeExprRangelist mkTypeExprRangelist(self)
#     TypeExprVal mkTypeExprVal(self, ValRef v)
#     TypeFieldPhy mkTypeFieldPhy(self, name, DataType, bool, attr, TypeExpr)
#     TypeFieldRef mkTypeFieldRef(self, name, DataType, attr)
#     ValRefInt mkValRefInt(self, int value, bool is_signed, int width)
