
cmake_minimum_required(VERSION 3.10)

project(libvsc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

include (ExternalProject)

ExternalProject_Add(
  gtest
  URL https://github.com/google/googletest/archive/master.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  # Disable install step
  INSTALL_COMMAND ""
  )
  
ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
  "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
  "IMPORTED_LINK_ITERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
  )
  
#pkg_check_modules(GTEST REQUIRED gtest>=1.7.0)

#include_directories(
#    ${GTEST_INCLUDE_DIRS}
#    )

add_subdirectory(src)

