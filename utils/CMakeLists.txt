add_library(utils STATIC
	format_utils.h
	format_utils.cpp
	file_utils.h
	file_utils.cpp
	types.h
)

target_include_directories(utils PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(utils PUBLIC
	Qt${QT_VERSION_MAJOR}::Core
)
