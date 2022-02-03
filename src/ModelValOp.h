/*
 * ModelValOp.h
 *
 *  Created on: Nov 19, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelVal.h"

namespace vsc {

class ModelValOp {
public:
	ModelValOp();
	virtual ~ModelValOp();

	static void eq(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void ne(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void sge(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void uge(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void sgt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void ugt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void sle(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void ule(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void slt(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void ult(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void log_and(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void log_or(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void sll(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void srl(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

	static void sra(
			IModelVal		*dst,
			const IModelVal	*op1,
			const IModelVal	*op2);

};

} /* namespace vsc */

