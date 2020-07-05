/*
 * IDataModelVisitor.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_DATAMODEL_IDATAMODELVISITOR_H_
#define SRC_DATAMODEL_IDATAMODELVISITOR_H_

namespace vsc {

class FieldScalar;

class IDataModelVisitor {
public:

	virtual ~IDataModelVisitor() { }

	virtual void visitFieldScalar(FieldScalar *f) = 0;

};

}




#endif /* SRC_DATAMODEL_IDATAMODELVISITOR_H_ */
