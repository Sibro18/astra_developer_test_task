cmake_minimum_required(VERSION 3.5)

project(astra-developer-test-task VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

add_subdirectory(utils)

option(BUILD_TESTS "Build unit tests" OFF)

set(PROJECT_SOURCES
        src/main.cpp
		src/main_window.h
		src/main_window.cpp
		src/ui_parts/custom_system_model_delegate.h
		src/ui_parts/custom_system_model_delegate.cpp
		src/ui_parts/custom_system_model.h
		src/ui_parts/custom_system_model.cpp
		src/ui_parts/custom_sort_filter_proxy_model.h
		src/ui_parts/custom_sort_filter_proxy_model.cpp
)

add_executable(${PROJECT_NAME}
	${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	utils
	Qt${QT_VERSION_MAJOR}::Widgets
)

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
)

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()
