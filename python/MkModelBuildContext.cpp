
#include "vsc/impl/ModelBuildContext.h"

extern "C" vsc::IModelBuildContext *mkModelBuildContext(vsc::IContext *ctxt) {
    return new vsc::ModelBuildContext(ctxt);
}
