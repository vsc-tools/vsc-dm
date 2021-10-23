
file(GLOB libvsc_SRC
  "*.h"
  "*.cpp"
  )
  
add_library(vsc SHARED ${libvsc_SRC})

target_include_directories(vsc PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/facade
    ${CMAKE_BINARY_DIR}/include
	${CMAKE_BINARY_DIR}/glog/include
    ${Boolector_INCLUDE_DIR}
    )
   
target_link_directories(vsc PRIVATE
    ${CMAKE_BINARY_DIR}/lib
    ${CMAKE_BINARY_DIR}/lib64
	${CMAKE_BINARY_DIR}/glog/lib64
    )
  
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(libglog glogd)
else()
	set(libglog glog)
endif()     

target_link_libraries(vsc 
	boolector
	btor2parser
	cadical
	${libglog}
	)

add_dependencies(vsc Boolector Bitwuzla GLOG)

add_subdirectory(facade)


