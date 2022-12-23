/*
 * TypeFieldAttr.h
 *
 *  Created on: Apr 5, 2022
 *      Author: mballance
 */

#pragma once

namespace vsc {
namespace dm {

enum class TypeFieldAttr {
	NoAttr   = 0,
	Rand     = (1 << 0),
	VecSize  = (1 << 1),
	Final    = (1 << 2) // Used to qualify methods
};

static inline TypeFieldAttr operator | (const TypeFieldAttr lhs, const TypeFieldAttr rhs) {
	return static_cast<TypeFieldAttr>(
			static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

static inline TypeFieldAttr operator & (const TypeFieldAttr lhs, const TypeFieldAttr rhs) {
	return static_cast<TypeFieldAttr>(
			static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

static inline TypeFieldAttr operator ~ (const TypeFieldAttr lhs) {
	return static_cast<TypeFieldAttr>(~static_cast<uint32_t>(lhs));
}

}
}
