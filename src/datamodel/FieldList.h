
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
 * FieldArray.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_DATAMODEL_FIELDLIST_H_
#define SRC_DATAMODEL_FIELDLIST_H_
#include "FieldComposite.h"

namespace vsc {

class FieldList : public FieldComposite {
public:

	FieldList(
			const std::string		&name,
			bool					is_scalar,
			int32_t					width,
			bool					is_signed,
			bool					is_rand,
			bool					is_rand_sz);

	virtual ~FieldList();

private:
	bool							m_is_scalar;
	int32_t							m_width;
	bool							m_is_signed;
	bool							m_is_rand_sz;
};

typedef std::shared_ptr<FieldList> FieldListSP;

} /* namespace vsc */

#endif /* SRC_DATAMODEL_FIELDLIST_H_ */
