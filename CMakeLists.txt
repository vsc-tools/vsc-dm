
cmake_minimum_required(VERSION 3.10)

project(libvsc)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boolector REQUIRED)
enable_testing()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_FLAGS_DEBUG "-O3 -g")

add_subdirectory(src)
add_subdirectory(test)
#add_subdirectory(deps)


#    test
#    deps)
#    "${PROJECT_SOURCE_DIR}/test")

#add_subdirectory(src)

