/*
 * DataTypeWrapper.cpp
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
#include "DataTypeWrapper.h"


namespace vsc {
namespace dm {


DataTypeWrapper::DataTypeWrapper(
    IDataType           *type_phy,
    IDataType           *type_virt) : 
    m_type_phy(type_phy), m_type_virt(type_virt) {
    m_bytesz = type_phy->getByteSize();
}

DataTypeWrapper::~DataTypeWrapper() {

}

IModelField *DataTypeWrapper::mkRootField(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) {
    return m_type_phy->mkRootField(ctxt, name, is_ref);
}

IModelField *DataTypeWrapper::mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type,
        const ValRef        &val) {
    return m_type_phy->mkTypeField(ctxt, type, val);
}

void DataTypeWrapper::initVal(ValRef &v) {
    m_type_phy->initVal(v);
}

void DataTypeWrapper::finiVal(ValRef &v) {
    m_type_phy->finiVal(v);
}

ValRef DataTypeWrapper::copyVal(const ValRef &src) {
    return m_type_phy->copyVal(src);
}

void DataTypeWrapper::accept(IVisitor *v) {
    v->visitDataTypeWrapper(this);
}

}
}
