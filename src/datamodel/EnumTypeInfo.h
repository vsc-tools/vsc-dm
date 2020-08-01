/*
 * EnumTypeInfo.h
 *
 *  Created on: Jul 31, 2020
 *      Author: ballance
 */

#pragma once
#include <stdint.h>
#include <map>
#include <memory>
#include <vector>

namespace vsc {

/**
 * Captures type information about an enumerated type
 * - Value set
 * - Enumerator names
 */
class EnumTypeInfo {
public:
	EnumTypeInfo();

	virtual ~EnumTypeInfo();

	void addEnumerator(
			int64_t			value,
			std::string		img);

private:
	std::vector<int64_t>			m_values;
	std::map<int64_t, std::string>	m_v2e;
	std::map<std::string, int64_t>	m_e2v;
};

typedef std::shared_ptr<EnumTypeInfo> EnumTypeInfoSP;

} /* namespace vsc */

