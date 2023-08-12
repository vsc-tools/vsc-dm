/*
 * TestVal.cpp
 *
 * Copyright 2023 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author:
 */
#include "TestVal.h"
#include "vsc/dm/Val.h"
#include "vsc/dm/impl/ValRef.h"
#include "vsc/dm/impl/ValRefInt.h"
#include "vsc/dm/impl/ValRefStr.h"
#include "vsc/dm/impl/ValRefStruct.h"


namespace vsc {
namespace dm {


TestVal::TestVal() {

}

TestVal::~TestVal() {

}

TEST_F(TestVal, smoke) {
    Val *v = m_ctxt->mkVal(63);

}

TEST_F(TestVal, int_add) {
    ValRefUInt v1(10, 16), v2(20, 16), v3;

    ValRefInt::add(v3, v1, v2);

    ASSERT_EQ(v3.get_val_s(), 30);
}

TEST_F(TestVal, str_init) {
    ValRefStr s1(m_ctxt.get(), "Hello World!");

    ASSERT_EQ(s1.val_s(), "Hello World!");
}

TEST_F(TestVal, str_move) {
    ValRefStr s1(m_ctxt.get(), "Hello World!");
    ASSERT_EQ(s1.val_s(), "Hello World!");
    ValRefStr s2(s1);

    ASSERT_EQ(s2.val_s(), "Hello World!");
    ASSERT_EQ(s1.vp(), 0);
}

TEST_F(TestVal, str_append_1) {
    ValRefStr s1(m_ctxt.get(), "Hello World!");
    ASSERT_EQ(s1.size(), 12);
    ASSERT_EQ(s1.val_s(), "Hello World!");

    s1.append(" How are you?");

    ASSERT_EQ(s1.val_s(), "Hello World! How are you?");

    s1.clear();

    ASSERT_EQ(s1.size(), 0);
    ASSERT_EQ(s1.val_s(), "");
}

TEST_F(TestVal, struct_1) {
    IDataTypeStruct *dt = m_ctxt->mkDataTypeStruct("dt");
    IDataTypeInt *u32_t = m_ctxt->mkDataTypeInt(false, 32);

    dt->addField(m_ctxt->mkTypeFieldPhy("a", u32_t, false, TypeFieldAttr::NoAttr, 0, false));
    dt->addField(m_ctxt->mkTypeFieldPhy("b", u32_t, false, TypeFieldAttr::NoAttr, 0, false));
    dt->addField(m_ctxt->mkTypeFieldPhy("c", u32_t, false, TypeFieldAttr::NoAttr, 0, false));

    m_ctxt->addDataTypeStruct(dt);

    ValRefStruct v1(
        m_ctxt.get(),
        dt);

    ValRef a(v1.getField(0));
    ASSERT_EQ(a.name(), "a");
    ValRef b(v1.getField(1));
    ASSERT_EQ(b.name(), "b");
    ValRef c(v1.getField(2));
    ASSERT_EQ(c.name(), "c");

    ValRefInt a_ref(v1.getFieldRef(0));
    ValRefInt b_ref(v1.getFieldRef(1));
    ValRefInt c_ref(v1.getFieldRef(2));

    a_ref.set_val(10);
    b_ref.set_val(20);
    c_ref.set_val(30);

    ASSERT_EQ(a_ref.get_val_u(), 10);
    ASSERT_EQ(b_ref.get_val_u(), 20);
    ASSERT_EQ(c_ref.get_val_u(), 30);
}

TEST_F(TestVal, struct_pad_1) {
    IDataTypeStruct *dt = m_ctxt->mkDataTypeStruct("dt");
    IDataTypeIntUP u32_t(m_ctxt->mkDataTypeInt(false, 32));
    IDataTypeIntUP u16_t(m_ctxt->mkDataTypeInt(false, 32));

    dt->addField(m_ctxt->mkTypeFieldPhy("a", u32_t.get(), false, TypeFieldAttr::NoAttr, 0, false));
    dt->addField(m_ctxt->mkTypeFieldPhy("b", u16_t.get(), false, TypeFieldAttr::NoAttr, 0, false));
    dt->addField(m_ctxt->mkTypeFieldPhy("c", u32_t.get(), false, TypeFieldAttr::NoAttr, 0, false));

    m_ctxt->addDataTypeStruct(dt);

    ASSERT_EQ(dt->getField(0)->getOffset(), 0);
    ASSERT_EQ(dt->getField(1)->getOffset(), 4);
    ASSERT_EQ(dt->getField(2)->getOffset(), 8);

    ValRefStruct v1(
        m_ctxt.get(),
        dt);

    ValRef a(v1.getField(0));
    ASSERT_EQ(a.name(), "a");
    ValRef b(v1.getField(1));
    ASSERT_EQ(b.name(), "b");
    ValRef c(v1.getField(2));
    ASSERT_EQ(c.name(), "c");

    ValRefInt a_ref(v1.getFieldRef(0));
    ValRefInt b_ref(v1.getFieldRef(1));
    ValRefInt c_ref(v1.getFieldRef(2));

    a_ref.set_val(10);
    b_ref.set_val(20);
    c_ref.set_val(30);

    ASSERT_EQ(a_ref.get_val_u(), 10);
    ASSERT_EQ(b_ref.get_val_u(), 20);
    ASSERT_EQ(c_ref.get_val_u(), 30);
}

}
}
