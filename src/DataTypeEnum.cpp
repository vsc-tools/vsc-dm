/*
 * DataTypeEnum.cpp
 *
 *  Created on: Nov 3, 2021
 *      Author: mballance
 */

#include <algorithm>
#include "DataTypeEnum.h"
#include "ModelValOp.h"
#include "TypeExprRange.h"
#include "TypeExprRangelist.h"
#include "TypeExprVal.h"

namespace vsc {

DataTypeEnum::DataTypeEnum(
		const std::string	&name,
		bool 				is_signed) :
				m_name(name), m_is_signed(is_signed) {

}

DataTypeEnum::~DataTypeEnum() {
	// TODO Auto-generated destructor stub
}

bool DataTypeEnum::addEnumerator(
			const std::string	&name,
			const IModelVal		*val) {
	std::unordered_map<std::string,ModelVal>::const_iterator it;

	if ((it=m_enum_val_m.find(name)) == m_enum_val_m.end()) {
		m_enum_val_m.insert({name, ModelVal(val)});

		return true;
	} else{
		// Already have an entry
		return false;
	}
}

ITypeExprRangelist *DataTypeEnum::getDomain() {
	if (!m_domain.get()) {
		TypeExprRangelist *rl = new TypeExprRangelist();

		std::vector<const ModelVal *> values;

		for (std::unordered_map<std::string,ModelVal>::const_iterator
				it=m_enum_val_m.begin();
				it!=m_enum_val_m.end(); it++) {
			values.push_back(&it->second);
		}

		// Sort the values
		std::sort(
				values.begin(),
				values.end(), [](const ModelVal *v1, const ModelVal *v2) {
					return v1->val_i() > v2->val_i();
				});

		// Now, collapse the values into compact ranges
		std::vector<const ModelVal *>::const_iterator it=values.begin();
		std::vector<const ModelVal *>::const_iterator start;
		ModelVal exp_n;

		while (it!=values.end()) {
			start = it;


			// Move ahead until next != prev+1
			std::vector<const ModelVal *>::const_iterator prev = it;
			it++;

			if (it != values.end()) {
				ModelVal eq;
				ModelValOp::add_s(
						&exp_n,
						*prev,
						1,
						32);

				// Check if
				ModelValOp::eq(&eq, &exp_n, *it);
				if (eq.val_u()) {
					// Keep going
				} else {
					// Create a range and move on
					TypeExprRange *rng = 0;

					if (start == prev) {
						// Single-value range
						rng = new TypeExprRange(
								true,
								new TypeExprVal(*start),
								0);

					} else {
						// Extends start..prev
						rng = new TypeExprRange(
								false,
								new TypeExprVal(*start),
								new TypeExprVal(*prev));
					}
					rl->addRange(rng);

					start = it;
				}
			} else {
				TypeExprRange *rng = 0;

				// Have from start..prev to stick in a range
				if (start == prev) {
					// Single-value range
					rng = new TypeExprRange(
							true,
							new TypeExprVal(*start),
							0);
				} else {
					// Extends start..prev
					rng = new TypeExprRange(
							false,
							new TypeExprVal(*start),
							new TypeExprVal(*prev));
				}
				rl->addRange(rng);
			}
		}
	}

	return m_domain.get();
}

} /* namespace vsc */
