/*
 * attr_scope.cpp
 *
 *  Created on: Nov 14, 2021
 *      Author: mballance
 */

#include "ctor.h"
#include "obj_scope.h"

namespace vsc {
namespace facade {

obj_scope::obj_scope(obj_t t) : obj(t|ObjType_Scope) {
	// TODO Auto-generated constructor stub

}

obj_scope::~obj_scope() {
	// TODO Auto-generated destructor stub
}

void obj_scope::build() {
	for (auto it=children().begin(); it!=children().end(); it++) {
		(*it)->build();
	}
}

} /* namespace facade */
} /* namespace vsc */
