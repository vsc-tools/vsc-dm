/*
 * ModelValOp.h
 *
 *  Created on: Nov 19, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelVal.h"
#include "vsc/IModelValOp.h"

namespace vsc {

class ModelValOp : public virtual IModelValOp {
public:
	ModelValOp();
	virtual ~ModelValOp();

	virtual void add(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) override;

	static void add_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2);

	static void add_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			int64_t			op2,
			uint32_t		bits);

	virtual void bin_and(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) override;

	static void bin_and_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2);

	virtual void bin_or(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) override;

	static void bin_or_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2);

	virtual void bin_xor(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) override;

	static void bin_xor_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2);

	virtual void eq(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void eq_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool eq(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool eq_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void ne(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void ne_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void sge(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void sge_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool sge(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool sge_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void uge(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void uge_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool uge(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool uge_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void sgt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void sgt_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool sgt(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool sgt_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void ugt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void ugt_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool ugt(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool ugt_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void sle(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void sle_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool sle(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool sle_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void ule(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void ule_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool ule(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool ule_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void slt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void slt_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool slt(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool slt_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void ult(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void ult_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool ult(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool ult_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void log_and(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void log_and_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool log_and(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool log_and_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void log_or(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;
	static void log_or_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool log_or(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool log_or_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void log_xor(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void log_xor_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual bool log_xor(
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static bool log_xor_s(
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void sll(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void sll_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void srl(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void srl_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void sra(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void sra_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	virtual void sub(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) override;

	static void sub_s(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

};

} /* namespace vsc */

