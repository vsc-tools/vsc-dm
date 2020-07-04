/*
 * FieldComposite.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_DATAMODEL_FIELDCOMPOSITE_H_
#define SRC_DATAMODEL_FIELDCOMPOSITE_H_
#include <vector>
#include "Field.h"

namespace vsc {

class FieldComposite : public Field {
public:
	FieldComposite(
			const std::string			&name,
			bool						is_rand);

	virtual ~FieldComposite();

	const std::vector<FieldSP> &children() const { return m_children; }

	virtual void set_used_rand(bool used_rand, int32_t level=0);

private:
	std::vector<FieldSP>			m_children;
	// TODO: constraint_model
	// ...

};

} /* namespace vsc */

#endif /* SRC_DATAMODEL_FIELDCOMPOSITE_H_ */
