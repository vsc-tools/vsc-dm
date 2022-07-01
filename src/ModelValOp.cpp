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

void ModelValOp::add(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		if (op1->bits() > op2->bits()) {
			dst->bits(op1->bits());
		} else {
			dst->bits(op2->bits());
		}
		dst->set_val_u(op1->val_u()+op2->val_u());
	} else {
		// TODO:
	}
	;
}

void ModelValOp::add_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			int64_t			op2,
			uint32_t		bits) {
	if (op1->bits() <= 64) {
		if (op1->bits() > bits) {
			dst->bits(op1->bits());
		} else {
			dst->bits(bits);
		}
		dst->set_val_i(op1->val_i()+op2, bits);
	} else {
		// TODO:
	}
}

void ModelValOp::eq(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	dst->setBits(1);
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
	dst->setBits(1);
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
	dst->setBits(1);
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
	dst->setBits(1);
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() >= op2->val_u());
		dst->bits(1);
	} else {
		// TODO:
	}
}

bool ModelValOp::uge(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		return op1->val_u() >= op2->val_u();
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

bool ModelValOp::sgt(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_i() >= op2->val_i());
	} else {
		// TODO:
	}
}

void ModelValOp::ugt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	dst->setBits(1);
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() >= op2->val_u());
		dst->bits(1);
	} else {
		// TODO:
	}
}

bool ModelValOp::ugt(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_u() >= op2->val_u());
	} else {
		// TODO:
	}
}

void ModelValOp::sle(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	dst->setBits(1);
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_i() <= op2->val_i());
		dst->bits(1);
	} else {
		// TODO:
	}
}

bool ModelValOp::sle(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_i() <= op2->val_i());
	} else {
		// TODO:
	}
}

void ModelValOp::ule(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	dst->setBits(1);
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() <= op2->val_u());
		dst->bits(1);
	} else {
		// TODO:
	}
}

bool ModelValOp::ule(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_u() <= op2->val_u());
	} else {
		// TODO:
	}
}

void ModelValOp::slt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	dst->setBits(1);
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_i() < op2->val_i());
		dst->bits(1);
	} else {
		// TODO:
	}
}

bool ModelValOp::slt(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_i() < op2->val_i());
	} else {
		// TODO:
	}
}

void ModelValOp::ult(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	dst->setBits(1);
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() < op2->val_u());
		dst->bits(1);
	} else {
		// TODO:
	}
}

bool ModelValOp::ult(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_u() < op2->val_u());
	} else {
		// TODO:
	}
}

void ModelValOp::log_and(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	dst->setBits(1);
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
	dst->setBits(1);
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
	dst->setBits(op1->bits());
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
	dst->setBits(op1->bits());
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
	dst->setBits(op1->bits());
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->val_u(op1->val_u() >>  op2->val_u());
	} else {
		// TODO:
	}
}

} /* namespace vsc */
