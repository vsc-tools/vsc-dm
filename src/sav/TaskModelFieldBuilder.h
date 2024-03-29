/*
 * TaskModelFieldBuilder.h
 *
 *  Created on: Apr 9, 2022
 *      Author: mballance
 */

#pragma once
#include <string>
#include <vector>
#include "dmgr/IDebug.h"
#include "vsc/dm/IContext.h"
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

class TaskModelFieldBuilder : public VisitorBase {
public:
	TaskModelFieldBuilder(IContext *ctxt);

	virtual ~TaskModelFieldBuilder();

	IModelFieldRoot *build(IDataTypeStruct *type, const std::string &name);

	virtual void visitTypeField(ITypeField *f) override;

	virtual void visitDataTypeInt(IDataTypeInt *t) override;

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override;

	virtual void visitTypeConstraintBlock(ITypeConstraintBlock *c) override;

	virtual void visitTypeConstraintExpr(ITypeConstraintExpr *c) override;

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) override;

private:
    static dmgr::IDebug                     *m_dbg;
	IContext								*m_ctxt;
	std::string								m_name;
	ITypeField								*m_type_field;
	std::vector<IModelField *>				m_field_s;
	std::vector<IModelConstraintScope *>	m_constraint_s;


};

}
} /* namespace vsc */

