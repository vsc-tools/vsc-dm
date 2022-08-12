
#include "ModelConstraintRef.h"

namespace vsc {

ModelConstraintRef::ModelConstraintRef(IModelConstraint *target) : m_target(target) {

}

ModelConstraintRef::~ModelConstraintRef() { }


}