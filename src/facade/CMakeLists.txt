
file(GLOB libvsc_facade_SRC
	"*.h"
	"*.cpp"
	)

add_library(vsc_facade STATIC ${libvsc_facade_SRC})

target_include_directories(vsc_facade PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/..
	${CMAKE_CURRENT_SOURCE_DIR}/../include
	${PACKAGES_DIR}/magic_enum/include
	)
