/*
 * FieldArray.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_DATAMODEL_FIELDLIST_H_
#define SRC_DATAMODEL_FIELDLIST_H_
#include "FieldComposite.h"

namespace vsc {

class FieldList : public FieldComposite {
public:

	FieldList(
			const std::string		&name,
			bool					is_scalar,
			int32_t					width,
			bool					is_signed,
			bool					is_rand,
			bool					is_rand_sz);

	virtual ~FieldList();

private:
	bool							m_is_scalar;
	int32_t							m_width;
	bool							m_is_signed;
	bool							m_is_rand_sz;
};

typedef std::shared_ptr<FieldList> FieldArraySP;

} /* namespace vsc */

#endif /* SRC_DATAMODEL_FIELDLIST_H_ */
