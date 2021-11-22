/*
 * obj_t.h
 *
 *  Created on: Nov 14, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>

namespace vsc {
namespace facade {

using obj_t = uint32_t;

static const obj_t ObjType_Scope       = (1 << 0);
static const obj_t ObjType_Covergroup  = (1 << 1);
static const obj_t ObjType_Coverpoint  = (1 << 2);
static const obj_t ObjType_CoverBins   = (1 << 4);
static const obj_t ObjType_CoverCross  = (1 << 5);
static const obj_t ObjType_CoverSample = (1 << 6);
static const obj_t ObjType_RandObj     = (1 << 7);
static const obj_t ObjType_Constraint  = (1 << 8);
// Item that references other items
// - constraints
// - coverpoints
static const obj_t ObjType_IsRef      = (1 << 4);

} /* namespace facade */
} /* namespace vsc */

