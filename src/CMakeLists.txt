
file(GLOB_RECURSE libvsc_SRC
  "*.h"
  "*.cpp"
  )
  
add_library(vsc SHARED ${libvsc_SRC})

target_include_directories(vsc PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/src/constraints"
    "${PROJECT_SOURCE_DIR}/src/coverage"
    "${PROJECT_SOURCE_DIR}/src/datamodel"
    "${PROJECT_SOURCE_DIR}/src/expr"
    "${PROJECT_SOURCE_DIR}/src/solver"
    )


