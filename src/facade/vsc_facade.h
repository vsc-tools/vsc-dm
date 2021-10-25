/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * vsc_facade.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#pragma once

#include "attr.h"
#include "rand_attr.h"
#include "rand_obj.h"
#include "constraint.h"
#include "constraint_if_then.h"

/**
 * User-facade macro that captures source location
 */
#define if_then(cond, body) \
	if_then(cond, body, __FILE__, __LINE__)

#define else_if(cond, body) \
	else_if(cond, body, __FILE__, __LINE__)

#define else_then(body) \
	else_then(body, __FILE__, __LINE__)



