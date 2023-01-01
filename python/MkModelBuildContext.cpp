
#include "vsc/dm/impl/ModelBuildContext.h"

extern "C" vsc::dm::IModelBuildContext *mkModelBuildContext(vsc::dm::IContext *ctxt) {
    return new vsc::dm::ModelBuildContext(ctxt);
}
