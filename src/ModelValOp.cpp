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

void ModelValOp::uge(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_u() >= op2.val_u());
		dst.bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::sgt(
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

void ModelValOp::ugt(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_u() >= op2.val_u());
		dst.bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::sle(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_i() <= op2.val_i());
		dst.bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::ule(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_u() <= op2.val_u());
		dst.bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::slt(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_i() < op2.val_i());
		dst.bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::ult(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_u() < op2.val_u());
		dst.bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::log_and(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_u() != 0 && op2.val_u() != 0);
	} else {
		// TODO:
	}
}

void ModelValOp::log_or(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_u() != 0 ||  op2.val_u() != 0);
	} else {
		// TODO:
	}
}

void ModelValOp::sll(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_u() <<  op2.val_u());
	} else {
		// TODO:
	}
}

void ModelValOp::sra(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_i() >>  op2.val_i());
	} else {
		// TODO:
	}
}

void ModelValOp::srl(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2) {
	if (op1.bits() <= 64 && op2.bits() <= 64) {
		dst.val_u(op1.val_u() >>  op2.val_u());
	} else {
		// TODO:
	}
}

} /* namespace vsc */
