/*
 * ModelValOp.cpp
 *
 *  Created on: Nov 19, 2021
 *      Author: mballance
 */

#include "ModelValOp.h"

namespace vsc {

ModelValOp::ModelValOp() {
	// TODO Auto-generated constructor stub

}

ModelValOp::~ModelValOp() {
	// TODO Auto-generated destructor stub
}

void ModelValOp::eq(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_u() == op2.val_u());
		dst.bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::ne(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_u() != op2.val_u());
		dst.bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::sge(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_i() >= op2.val_i());
		dst.bits(1);
	} else {
		// TODO:
	}
}


} /* namespace vsc */
