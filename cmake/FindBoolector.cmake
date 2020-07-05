# Find Boolector
# Boolector_FOUND       - found Boolector
# Boolector_INCLUDE_DIR - the Boolector include directory
# Boolector_LIBRARIES   - Libraries needed to use Boolector

find_path(Boolector_INCLUDE_DIR NAMES boolector/boolector.h)
find_library(Boolector_LIBRARIES NAMES boolector)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Boolector
  DEFAULT_MSG Boolector_INCLUDE_DIR Boolector_LIBRARIES)

mark_as_advanced(Boolector_INCLUDE_DIR Boolector_LIBRARIES)
if(Boolector_LIBRARIES)
  message(STATUS "Found Btor2Tools library: ${Boolector_LIBRARIES}")
endif()
