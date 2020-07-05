/*
 * FieldScalar.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_DATAMODEL_FIELDSCALAR_H_
#define SRC_DATAMODEL_FIELDSCALAR_H_
#include "Field.h"

namespace vsc {

class FieldScalar : public Field {
public:
	FieldScalar(
			const std::string		&name,
			int32_t					width,
			bool					is_signed,
			bool					is_rand);

	virtual ~FieldScalar();

	virtual int32_t width() const { return m_width; }

	virtual bool is_signed() const { return m_is_signed; }

	virtual void accept(IDataModelVisitor *v) { v->visitFieldScalar(this); }

private:
	int32_t							m_width;
	bool							m_is_signed;

};
typedef std::shared_ptr<FieldScalar> FieldScalarSP;

} /* namespace vsc */

#endif /* SRC_DATAMODEL_FIELDSCALAR_H_ */
