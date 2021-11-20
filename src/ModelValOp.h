/*
 * ModelValOp.h
 *
 *  Created on: Nov 19, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelVal.h"

namespace vsc {

class ModelValOp {
public:
	ModelValOp();
	virtual ~ModelValOp();

	static void eq(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void ne(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void sge(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void uge(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void sgt(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void ugt(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void sle(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void ule(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void slt(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void ult(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void log_and(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void log_or(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void sll(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void srl(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

	static void sra(
			ModelVal		&dst,
			const ModelVal	&op1,
			const ModelVal	&op2);

};

} /* namespace vsc */

