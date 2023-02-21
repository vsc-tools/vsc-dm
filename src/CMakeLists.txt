
file(GLOB libvsc_dm_SRC
  "*.h"
  "*.cpp"
  )
  
add_library(vsc-dm SHARED ${libvsc_dm_SRC})

target_include_directories(vsc-dm PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
    ${DEBUG_MGR_DIR}/src/include
    )
   
target_link_directories(vsc-dm PRIVATE
    ${CMAKE_BINARY_DIR}/lib
    ${CMAKE_BINARY_DIR}/lib64
    )
  
# add_library(vsc-dm_static STATIC ${libvsc_dm_SRC})

# target_include_directories(vsc-dm_static PUBLIC
#     ${PROJECT_SOURCE_DIR}/src
#     ${PROJECT_SOURCE_DIR}/src/include
#     ${DEBUG_MGR_DIR}/src/include
#     )
   
# target_link_directories(vsc-dm_static PRIVATE
#     ${CMAKE_BINARY_DIR}/lib
#     ${CMAKE_BINARY_DIR}/lib64
#     )

# install(TARGETS vsc-dm_static
#     DESTINATION lib
#     EXPORT libvsc-dm-targets)

install(TARGETS vsc-dm
    DESTINATION lib
    EXPORT libvsc-dm-targets)


