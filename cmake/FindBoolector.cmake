# Find Boolector
# Boolector_FOUND       - found Boolector
# Boolector_INCLUDE_DIR - the Boolector include directory
# Boolector_LIBRARIES   - Libraries needed to use Boolector

if(Boolector_DIR)
set(Boolector_INCLUDE_DIR "${Boolector_DIR}/include")
set(Boolector_LIBRARIES "${Boolector_DIR}/lib/libboolector.so")
else()
find_path(Boolector_INCLUDE_DIR NAMES boolector/boolector.h)
find_library(Boolector_LIBRARIES NAMES boolector)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Boolector
  DEFAULT_MSG Boolector_INCLUDE_DIR Boolector_LIBRARIES)

mark_as_advanced(Boolector_INCLUDE_DIR Boolector_LIBRARIES)
if(Boolector_LIBRARIES)
  message(STATUS "Found Boolector library: ${Boolector_LIBRARIES} ${Boolector_INCLUDE_DIR}")
endif()
