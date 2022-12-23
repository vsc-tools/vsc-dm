
#pragma once
#include "vsc/dm/IModelVal.h"

namespace vsc {
namespace dm {

class IModelValOp {
public:

	virtual void add(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) = 0;

	virtual void bin_and(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) = 0;

	virtual void bin_or(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) = 0;

	virtual void bin_xor(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal *op2) = 0;

	virtual void eq(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool eq(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void ne(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void sge(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool sge(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;
            
	virtual void uge(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool uge(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void sgt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool sgt(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void ugt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool ugt(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void sle(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool sle(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void ule(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool ule(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void slt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool slt(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void ult(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool ult(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void log_and(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool log_and(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void log_or(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool log_or(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void log_xor(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual bool log_xor(
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void sll(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void sra(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void srl(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

	virtual void sub(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2) = 0;

};

}
}
