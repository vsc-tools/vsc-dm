
#include "ModelConstraintRef.h"

namespace vsc {
namespace dm {

ModelConstraintRef::ModelConstraintRef(IModelConstraint *target) : m_target(target) {

}

ModelConstraintRef::~ModelConstraintRef() { }


}
}
