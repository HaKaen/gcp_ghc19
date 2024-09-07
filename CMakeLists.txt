cmake_minimum_required(VERSION 3.25)

project(ghc19
	VERSION 1.0.0
	LANGUAGES CXX)

set(BIN_NAME "ghc")

# ---------------------------------------------------------------------------------------
# Set default build to release
# ---------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

# ---------------------------------------------------------------------------------------
# Set install dir
# ---------------------------------------------------------------------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "default install path" FORCE)
endif()
include(GNUInstallDirs)

# ---------------------------------------------------------------------------------------
# Compilation settings
# ---------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(cmake/default_warnings.cmake)

# ---------------------------------------------------------------------------------------
# Pass cmake variables to c++
# ---------------------------------------------------------------------------------------
set(PROJECT_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)
configure_file(config.h.in config.h)

# ---------------------------------------------------------------------------------------
# Static libstdc++
# ---------------------------------------------------------------------------------------
add_link_options(-static-libstdc++)

# ---------------------------------------------------------------------------------------
# Targets
# ---------------------------------------------------------------------------------------
add_subdirectory(src)

add_executable(${CMAKE_PROJECT_NAME})
set_default_warnings(${CMAKE_PROJECT_NAME})
set_target_properties(${CMAKE_PROJECT_NAME}
	PROPERTIES
	OUTPUT_NAME ${BIN_NAME}
)

target_sources(${CMAKE_PROJECT_NAME}
	PRIVATE
	main.cpp
)

target_include_directories (${CMAKE_PROJECT_NAME}
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	${PROJECT_BINARY_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
	PUBLIC
	${CMAKE_PROJECT_NAME}_lib)

add_subdirectory(tests)

# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME_DEPENDENCIES)
