
file(GLOB libvsc_SRC
  "*.h"
  "*.cpp"
  )
  
add_library(vsc SHARED ${libvsc_SRC})

target_include_directories(vsc PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/src/facade"
    ${CMAKE_BINARY_DIR}/include
    ${Boolector_INCLUDE_DIR}
    )
target_link_directories(vsc PRIVATE
    ${CMAKE_BINARY_DIR}/lib
    ${CMAKE_BINARY_DIR}/lib64
    )
target_link_libraries(vsc 
	boolector
	btor2parser
	cadical
	)
add_dependencies(vsc Boolector Bitwuzla)

add_subdirectory(facade)


