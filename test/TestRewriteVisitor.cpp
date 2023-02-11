/*
 * TestRewriteVisitor.cpp
 *
 * Copyright 2022 Matthew Ballance and Contributors
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
#include "TestRewriteVisitor.h"
#include "vsc/dm/impl/RewriteVisitorBase.h"


namespace vsc {
namespace dm {


TestRewriteVisitor::TestRewriteVisitor() {

}

TestRewriteVisitor::~TestRewriteVisitor() {

}

TEST_F(TestRewriteVisitor, smoke) {

    class MyRewriter : public RewriteVisitorBase {

        virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override {
            fprintf(stdout, "visitTypeFieldPhy\n");
            ITypeField *fi = m_ctxt->mkTypeFieldPhy(
                "bcd",
                m_ctxt->mkDataTypeInt(true, 16),
                true,
                TypeFieldAttr::NoAttr,
                0);
            rewrite(fi);
        }

    };

    IDataTypeIntUP uint32(m_ctxt->mkDataTypeInt(true, 32));
    IDataTypeStructUP my_s(m_ctxt->mkDataTypeStruct("my_s"));

    my_s->addField(m_ctxt->mkTypeFieldPhy(
        "a",
        uint32.get(),
        false,
        TypeFieldAttr::NoAttr,
        0), true);


    IRewriteContextUP ctxt(m_factory->mkRewriteContext(
        m_ctxt.get(),
        {my_s.get()}
    ));

    MyRewriter w;

    w.rewrite(ctxt.get());

    ASSERT_NE(ctxt->getRoots().at(0).get(), my_s.get());
    ASSERT_TRUE(dynamic_cast<IDataTypeStruct *>(ctxt->getRoots().at(0).get()));
    ASSERT_EQ(dynamic_cast<IDataTypeStruct *>(ctxt->getRoots().at(0).get())->name(), "my_s");
    ASSERT_EQ(dynamic_cast<IDataTypeStruct *>(ctxt->getRoots().at(0).get())->getField(0)->name(), 
        "bcd");
}

TEST_F(TestRewriteVisitor, add_field) {

    class MyRewriter : public RewriteVisitorBase {

        virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override {
            fprintf(stdout, "visitTypeFieldPhy\n");
            retain(f);
            ITypeField *fi = m_ctxt->mkTypeFieldPhy(
                "bcd",
                m_ctxt->mkDataTypeInt(true, 16),
                true,
                TypeFieldAttr::NoAttr,
                0);
            add(fi);
        }

    };

    IDataTypeIntUP uint32(m_ctxt->mkDataTypeInt(true, 32));
    IDataTypeStructUP my_s(m_ctxt->mkDataTypeStruct("my_s"));

    my_s->addField(m_ctxt->mkTypeFieldPhy(
        "a",
        uint32.get(),
        false,
        TypeFieldAttr::NoAttr,
        0), true);


    IRewriteContextUP ctxt(m_factory->mkRewriteContext(
        m_ctxt.get(),
        {my_s.get()}
    ));

    MyRewriter w;

    w.rewrite(ctxt.get());

    ASSERT_NE(ctxt->getRoots().at(0).get(), my_s.get());
    ASSERT_TRUE(dynamic_cast<IDataTypeStruct *>(ctxt->getRoots().at(0).get()));
    ASSERT_EQ(dynamic_cast<IDataTypeStruct *>(ctxt->getRoots().at(0).get())->name(), "my_s");
    ASSERT_EQ(dynamic_cast<IDataTypeStruct *>(ctxt->getRoots().at(0).get())->getFields().size(), 2);
    ASSERT_EQ(dynamic_cast<IDataTypeStruct *>(ctxt->getRoots().at(0).get())->getField(0)->name(), 
        "a");
    ASSERT_EQ(dynamic_cast<IDataTypeStruct *>(ctxt->getRoots().at(0).get())->getField(1)->name(), 
        "bcd");
}

}
}
