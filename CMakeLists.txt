
cmake_minimum_required(VERSION 3.10)

project(libvsc)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boolector REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
#add_subdirectory(deps)


#    test
#    deps)
#    "${PROJECT_SOURCE_DIR}/test")

#add_subdirectory(src)

