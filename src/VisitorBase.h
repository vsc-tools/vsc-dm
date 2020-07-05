
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
 * VisitorBase.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#ifndef SRC_VISITORBASE_H_
#define SRC_VISITORBASE_H_
#include "IVisitor.h"
#include "expr/ExprVisitorBase.h"
#include "DataModelVisitorBase.h"

namespace vsc {

class VisitorBase : public virtual IVisitor,
	public virtual DataModelVisitorBase,
	public virtual ExprVisitorBase {
public:
	VisitorBase();
	virtual ~VisitorBase();
};

} /* namespace vsc */

#endif /* SRC_VISITORBASE_H_ */
