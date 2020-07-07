/*
 * FieldArray.h
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#ifndef SRC_DATAMODEL_FIELDARRAY_H_
#define SRC_DATAMODEL_FIELDARRAY_H_
#include "datamodel/Field.h"

namespace vsc {

class FieldArray : public Field {
public:
	FieldArray(
			const std::string		&name,
			bool					is_rand);

	virtual ~FieldArray();

};

} /* namespace vsc */

#endif /* SRC_DATAMODEL_FIELDARRAY_H_ */
