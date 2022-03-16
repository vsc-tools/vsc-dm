/*
 * Context.h
 *
 *  Created on: Sep 8, 2021
 *      Author: mballance
 */

#pragma once
#include <unordered_map>
#include "vsc/IContext.h"
#include "DataTypeInt.h"
#include "DataTypeStruct.h"

namespace vsc {

class Context : public IContext {
public:
	Context();

	virtual ~Context();

	DataTypeStruct *findStructType(const std::string &name);

	void addStructType(DataTypeStruct *t);

	DataTypeInt *findIntType(
			bool			is_signed,
			int32_t			width,
			bool			create=true);

	void addIntType(DataTypeInt		*t);

	virtual IDataTypeInt *mkDataTypeInt(
			bool			is_signed,
			int32_t			width) override;

	virtual IModelField *mkModelFieldRoot(
			IDataType 			*type,
			const std::string	&name) override;

	virtual IRandomizer *mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) override;

	virtual IRandState *mkRandState(uint32_t seed) override;

private:

	std::unordered_map<std::string,DataTypeStructUP>		m_struct_type_m;
	std::vector<DataTypeStruct *>							m_struct_type_l;

	std::unordered_map<int32_t, DataTypeInt*>				m_uint_type_m;
	std::vector<DataTypeIntUP>								m_uint_type_l;

	std::unordered_map<int32_t, DataTypeInt*>				m_sint_type_m;
	std::vector<DataTypeIntUP>								m_sint_type_l;

};

} /* namespace vsc */

