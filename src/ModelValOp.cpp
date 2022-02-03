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
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() == op2->val_u());
		dst->bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::ne(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() != op2->val_u());
		dst->bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::sge(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_i() >= op2->val_i());
		dst->bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::uge(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() >= op2->val_u());
		dst->bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::sgt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_i() >= op2->val_i());
		dst->bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::ugt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() >= op2->val_u());
		dst->bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::sle(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_i() <= op2->val_i());
		dst->bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::ule(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() <= op2->val_u());
		dst->bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::slt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_i() < op2->val_i());
		dst->bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::ult(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() < op2->val_u());
		dst->bits(1);
	} else {
		// TODO:
	}
}

void ModelValOp::log_and(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() != 0 && op2->val_u() != 0);
	} else {
		// TODO:
	}
}

void ModelValOp::log_or(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() != 0 ||  op2->val_u() != 0);
	} else {
		// TODO:
	}
}

void ModelValOp::sll(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() <<  op2->val_u());
	} else {
		// TODO:
	}
}

void ModelValOp::sra(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_i() >>  op2->val_i());
	} else {
		// TODO:
	}
}

void ModelValOp::srl(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() >>  op2->val_u());
	} else {
		// TODO:
	}
}

} /* namespace vsc */
