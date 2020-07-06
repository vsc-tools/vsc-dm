
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * FieldComposite.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_DATAMODEL_FIELDCOMPOSITE_H_
#define SRC_DATAMODEL_FIELDCOMPOSITE_H_
#include <vector>
#include "datamodel/Field.h"
#include "constraints/ConstraintBlock.h"

namespace vsc {

class FieldComposite : public Field {
public:
	FieldComposite(
			const std::string			&name,
			bool						is_rand);

	virtual ~FieldComposite();

	const std::vector<FieldSP> &children() const { return m_children; }

	const std::vector<ConstraintBlockSP> &constraints() const { return m_constraints; }

	virtual void set_used_rand(bool used_rand, int32_t level=0);

	virtual void accept(IVisitor *v) { v->visitFieldComposite(this); }

private:
	std::vector<FieldSP>				m_children;
	std::vector<ConstraintBlockSP>		m_constraints;
	// TODO: constraint_model
	// ...

};

} /* namespace vsc */

#endif /* SRC_DATAMODEL_FIELDCOMPOSITE_H_ */
