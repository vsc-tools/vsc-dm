/*
 * DataModelVisitorBase.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_DATAMODEL_DATAMODELVISITORBASE_H_
#define SRC_DATAMODEL_DATAMODELVISITORBASE_H_
#include "IDataModelVisitor.h"

namespace vsc {

class DataModelVisitorBase : public virtual IDataModelVisitor {
public:
	DataModelVisitorBase();

	virtual ~DataModelVisitorBase();

};

} /* namespace vsc */

#endif /* SRC_DATAMODEL_DATAMODELVISITORBASE_H_ */
