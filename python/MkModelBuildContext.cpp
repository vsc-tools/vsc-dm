
#include "vsc/dm/impl/ModelBuildContext.h"

vsc::dm::IModelBuildContext *mkModelBuildContext(vsc::dm::IContext *ctxt) {
    return new vsc::dm::ModelBuildContext(ctxt);
}
