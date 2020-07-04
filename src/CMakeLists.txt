
file(GLOB_RECURSE libvsc_SRC
  "*.h"
  "*.cpp"
  )


add_library(vsc SHARED ${libvsc_SRC})
