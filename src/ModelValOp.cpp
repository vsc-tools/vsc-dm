/*
 * ModelValOp.cpp
 *
 *  Created on: Nov 19, 2021
 *      Author: mballance
 */

#include "ModelValOp.h"

namespace vsc {
namespace dm {

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
	add_s(dst, op1, op2);
}

void ModelValOp::add_s(
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

void ModelValOp::bin_and(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) {
	bin_and_s(dst, op1, op2);
}

void ModelValOp::bin_and_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->set_val_u(op1->val_u() & op2->val_u());
	} else {
		// TODO:
	}
}

void ModelValOp::bin_or(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) {
    bin_or_s(dst, op1, op2);
}

void ModelValOp::bin_or_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->set_val_u(op1->val_u() | op2->val_u());
	} else {
		// TODO:
	}
}

void ModelValOp::bin_xor(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) {
    bin_xor_s(dst, op1, op2);			
}

void ModelValOp::bin_xor_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->set_val_u(op1->val_u() ^ op2->val_u());
	} else {
		// TODO:
	}
}

void ModelValOp::eq(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	eq_s(dst, op1, op2);
}

void ModelValOp::eq_s(
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

bool ModelValOp::eq(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	return eq_s(op1, op2);
}

bool ModelValOp::eq_s(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_u() == op2->val_u());
	} else {
		// TODO:
	}
}

void ModelValOp::ne(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	ne_s(dst, op1, op2);
}

void ModelValOp::ne_s(
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
	sge_s(dst, op1, op2);
}

void ModelValOp::sge_s(
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

bool ModelValOp::sge(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	return sge_s(op1, op2);
}

bool ModelValOp::sge_s(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_i() >= op2->val_i());
	} else {
		// TODO:
	}
}

void ModelValOp::uge(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	uge_s(dst, op1, op2);
}

void ModelValOp::uge_s(
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
	return uge_s(op1, op2);
}

bool ModelValOp::uge_s(
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
	sgt_s(dst, op1, op2);
}

void ModelValOp::sgt_s(
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
	return sgt_s(op1, op2);
}

bool ModelValOp::sgt_s(
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
	ugt_s(dst, op1, op2);
}

void ModelValOp::ugt_s(
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
	return ugt_s(op1, op2);
}

bool ModelValOp::ugt_s(
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
	return sle_s(dst, op1, op2);
}

void ModelValOp::sle_s(
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
	return sle_s(op1, op2);
}

bool ModelValOp::sle_s(
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
	ule_s(dst, op1, op2);
}

void ModelValOp::ule_s(
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
	return ule_s(op1, op2);
}

bool ModelValOp::ule_s(
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
	slt_s(dst, op1, op2);
}

void ModelValOp::slt_s(
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
	return slt_s(op1, op2);
}

bool ModelValOp::slt_s(
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
	ult_s(dst, op1, op2);
}

void ModelValOp::ult_s(
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
	return ult_s(op1, op2);
}

bool ModelValOp::ult_s(
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
	log_and_s(dst, op1, op2);
}

void ModelValOp::log_and_s(
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

bool ModelValOp::log_and(
			const IModelVal	*op1,
			const IModelVal	*op2) {
    return log_and_s(op1, op2);
}

bool ModelValOp::log_and_s(
			const IModelVal	*op1,
			const IModelVal	*op2) {
    if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_u() && op2->val_u());
    } else {
        // TODO:
    }
}

void ModelValOp::log_or(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	log_or_s(dst, op1, op2);
}

void ModelValOp::log_or_s(
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

bool ModelValOp::log_or(
			const IModelVal	*op1,
			const IModelVal	*op2) {
    return log_or_s(op1, op2);
}

bool ModelValOp::log_or_s(
			const IModelVal	*op1,
			const IModelVal	*op2) {
    if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_u() || op2->val_u());
	} else {
		// TODO:
	}
}

void ModelValOp::log_xor(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
    log_xor_s(dst, op1, op2);
}

void ModelValOp::log_xor_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
    if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->set_val_u(op1->val_u() != 0 ^ op2->val_u() != 0);
	} else {
		// TODO:
	}
}

bool ModelValOp::log_xor(
			const IModelVal	*op1,
			const IModelVal	*op2) {
	return log_xor_s(op1, op2);
}

bool ModelValOp::log_xor_s(
			const IModelVal	*op1,
			const IModelVal	*op2) {
    if (op1->bits() <= 64 && op2->bits() <= 64) {
		return (op1->val_u() != 0 ^ op2->val_u() != 0);
	}
}

void ModelValOp::sll(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
	sll_s(dst, op1, op2);
}

void ModelValOp::sll_s(
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
	sra_s(dst, op1, op2);
}

void ModelValOp::sra_s(
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
	srl_s(dst, op1, op2);
}

void ModelValOp::srl_s(
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

void ModelValOp::sub(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
    sub_s(dst, op1, op2);
}

void ModelValOp::sub_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) {
    if (op1->bits() <= 64 && op2->bits() <= 64) {
		dst->set_val_u(op1->val_u() - op2->val_u());
	} else {
		// TODO:
	}
}

}
} /* namespace vsc */

