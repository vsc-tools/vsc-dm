/*
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



