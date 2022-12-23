
#include "TestModelFieldFactory.h"
#include "vsc/dm/impl/TaskBuildModelField.h"
#include "Context.h"
#include "vsc/dm/impl/ModelBuildContext.h"

namespace vsc {
namespace dm {

TEST_F(TestModelFieldFactory, smoke) {
    Context ctxt;
    IDataTypeStruct *my_t = ctxt.mkDataTypeStruct("my_t");
    IDataTypeInt *ui8_t = ctxt.mkDataTypeInt(false, 8);
    ctxt.addDataTypeInt(ui8_t);

    my_t->addField(ctxt.mkTypeFieldPhy("a", ui8_t, false, TypeFieldAttr::Rand, 0));
    my_t->addField(ctxt.mkTypeFieldPhy("b", ui8_t, false, TypeFieldAttr::Rand, 0));

    ITypeConstraintBlock *c = ctxt.mkTypeConstraintBlock("ab_c");
    c->addConstraint(ctxt.mkTypeConstraintExpr(
        ctxt.mkTypeExprBin(
            ctxt.mkTypeExprFieldRef({{TypeExprFieldRefElemKind::IdxOffset, 0}}), // a
            BinOp::Lt,
            ctxt.mkTypeExprFieldRef({{TypeExprFieldRefElemKind::IdxOffset, 1}})  // b
        )));
    my_t->addConstraint(c);

    ctxt.addDataTypeStruct(my_t);

    ModelBuildContext build_ctxt(&ctxt);

    IModelFieldUP field(TaskBuildModelField(&build_ctxt).build(my_t, "abc"));

    ASSERT_EQ(field->fields().size(), 2);
    ASSERT_EQ(field->getField(0)->name(), "a");
    ASSERT_EQ(field->getField(1)->name(), "b");

#ifdef UNMDEFINED
    IRandStateUP state(ctxt.mkRandState("0"));
    ICompoundSolverUP solver(ctxt.mkCompoundSolver());

    for (uint32_t i=0; i<10; i++) {
        ASSERT_TRUE(solver->solve(
            state.get(),
            {field.get()},
            {},
            SolveFlags::RandomizeTopFields|SolveFlags::Randomize
        ));
        ASSERT_LT(
            field->getField(0)->val()->val_u(),
            field->getField(1)->val()->val_u());
    }
#endif
}

TEST_F(TestModelFieldFactory, struct_type_subfields) {
    Context ctxt;
    IDataTypeStruct *my_t = ctxt.mkDataTypeStruct("my_t");
    IDataTypeInt *ui8_t = ctxt.mkDataTypeInt(false, 8);
    ctxt.addDataTypeInt(ui8_t);


    IDataTypeStruct *my_subfield_t = ctxt.mkDataTypeStruct("my_subfield_t");
    my_subfield_t->addField(ctxt.mkTypeFieldPhy("a", ui8_t, false, TypeFieldAttr::Rand, 0));
    my_subfield_t->addField(ctxt.mkTypeFieldPhy("b", ui8_t, false, TypeFieldAttr::Rand, 0));

    ITypeConstraintBlock *c = ctxt.mkTypeConstraintBlock("ab_c");
    c->addConstraint(ctxt.mkTypeConstraintExpr(
        ctxt.mkTypeExprBin(
            ctxt.mkTypeExprFieldRef({{TypeExprFieldRefElemKind::IdxOffset, 0}}), // a
            BinOp::Lt,
            ctxt.mkTypeExprFieldRef({{TypeExprFieldRefElemKind::IdxOffset, 1}})  // b
        )));
    my_subfield_t->addConstraint(c);

    ctxt.addDataTypeStruct(my_subfield_t);

    my_t->addField(ctxt.mkTypeFieldPhy("a", my_subfield_t, false, TypeFieldAttr::Rand, 0));
    my_t->addField(ctxt.mkTypeFieldPhy("b", my_subfield_t, false, TypeFieldAttr::Rand, 0));
    ctxt.addDataTypeStruct(my_t);

    ModelBuildContext build_ctxt(&ctxt);

    IModelFieldUP field(TaskBuildModelField(&build_ctxt).build(my_t, "abc"));

    ASSERT_EQ(field->fields().size(), 2);
    ASSERT_EQ(field->getField(0)->name(), "a");
    ASSERT_EQ(field->getField(1)->name(), "b");

#ifdef UNDEFINED
    IRandStateUP state(ctxt.mkRandState("0"));
    ICompoundSolverUP solver(ctxt.mkCompoundSolver());

    for (uint32_t i=0; i<10; i++) {
        ASSERT_TRUE(solver->solve(
            state.get(),
            {field.get()},
            {},
            SolveFlags::RandomizeTopFields|SolveFlags::Randomize
        ));
        fprintf(stdout, "a.a=%lld a.b=%lld b.a=%lld b.b=%lld\n",
            field->getField(0)->getField(0)->val()->val_u(),
            field->getField(0)->getField(1)->val()->val_u(),
            field->getField(1)->getField(0)->val()->val_u(),
            field->getField(1)->getField(1)->val()->val_u());
        ASSERT_LT(
            field->getField(0)->getField(0)->val()->val_u(),
            field->getField(0)->getField(1)->val()->val_u());
        ASSERT_LT(
            field->getField(1)->getField(0)->val()->val_u(),
            field->getField(1)->getField(1)->val()->val_u());
    }
#endif
}

TEST_F(TestModelFieldFactory, struct_type_subfields_above_constraint) {
    Context ctxt;
    IDataTypeStruct *my_t = ctxt.mkDataTypeStruct("my_t");
    IDataTypeInt *ui8_t = ctxt.mkDataTypeInt(false, 8);
    ctxt.addDataTypeInt(ui8_t);


    IDataTypeStruct *my_subfield_t = ctxt.mkDataTypeStruct("my_subfield_t");
    my_subfield_t->addField(ctxt.mkTypeFieldPhy("a", ui8_t, false, TypeFieldAttr::Rand, 0));
    my_subfield_t->addField(ctxt.mkTypeFieldPhy("b", ui8_t, false, TypeFieldAttr::Rand, 0));

    ITypeConstraintBlock *c = ctxt.mkTypeConstraintBlock("ab_c");
    c->addConstraint(ctxt.mkTypeConstraintExpr(
        ctxt.mkTypeExprBin(
            ctxt.mkTypeExprFieldRef({{TypeExprFieldRefElemKind::IdxOffset, 0}}), // a
            BinOp::Lt,
            ctxt.mkTypeExprFieldRef({{TypeExprFieldRefElemKind::IdxOffset, 1}})  // b
        )));
    my_subfield_t->addConstraint(c);

    ctxt.addDataTypeStruct(my_subfield_t);

    my_t->addField(ctxt.mkTypeFieldPhy("a", my_subfield_t, false, TypeFieldAttr::Rand, 0));
    my_t->addField(ctxt.mkTypeFieldPhy("b", my_subfield_t, false, TypeFieldAttr::Rand, 0));

    my_t->addConstraint(ctxt.mkTypeConstraintExpr(
        ctxt.mkTypeExprBin(
            ctxt.mkTypeExprFieldRef({
                {TypeExprFieldRefElemKind::IdxOffset, 0},
                {TypeExprFieldRefElemKind::ActiveScope, 0} // a.a
            }),
            BinOp::Eq,
            ctxt.mkTypeExprFieldRef({
                {TypeExprFieldRefElemKind::IdxOffset, 1},
                {TypeExprFieldRefElemKind::ActiveScope, 0} // b.a
            }))));

    ctxt.addDataTypeStruct(my_t);

    ModelBuildContext build_ctxt(&ctxt);

    IModelFieldUP field(TaskBuildModelField(&build_ctxt).build(my_t, "abc"));

    ASSERT_EQ(field->fields().size(), 2);
    ASSERT_EQ(field->getField(0)->name(), "a");
    ASSERT_EQ(field->getField(1)->name(), "b");

#ifdef UNDEFINED
    IRandStateUP state(ctxt.mkRandState("0"));
    ICompoundSolverUP solver(ctxt.mkCompoundSolver());

    for (uint32_t i=0; i<10; i++) {
        ASSERT_TRUE(solver->solve(
            state.get(),
            {field.get()},
            {},
            SolveFlags::RandomizeTopFields|SolveFlags::Randomize
        ));
        fprintf(stdout, "a.a=%lld a.b=%lld b.a=%lld b.b=%lld\n",
            field->getField(0)->getField(0)->val()->val_u(),
            field->getField(0)->getField(1)->val()->val_u(),
            field->getField(1)->getField(0)->val()->val_u(),
            field->getField(1)->getField(1)->val()->val_u());
        ASSERT_LT(
            field->getField(0)->getField(0)->val()->val_u(),
            field->getField(0)->getField(1)->val()->val_u());
        ASSERT_LT(
            field->getField(1)->getField(0)->val()->val_u(),
            field->getField(1)->getField(1)->val()->val_u());
        ASSERT_EQ(
            field->getField(0)->getField(0)->val()->val_u(),
            field->getField(1)->getField(0)->val()->val_u());
    }
#endif
}

}
}
