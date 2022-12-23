
cmake_minimum_required(VERSION 3.10)

project(libvsc)

include (ExternalProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if (NOT PACKAGES_DIR)
  set(PACKAGES_DIR ${CMAKE_SOURCE_DIR}/packages)


  # Testing is only enabled when libvsc is the top-level project
  enable_testing()
  add_subdirectory(test)

endif()

if(NOT WIN32)
  add_compile_options(-fPIC)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INSTALL_RPATH $ORIGIN)



#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

add_subdirectory(src)


