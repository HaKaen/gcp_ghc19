set(MYLIB "${CMAKE_PROJECT_NAME}_lib")

add_library(${MYLIB} STATIC)
set_default_warnings(${MYLIB})

target_sources(${MYLIB}
	PRIVATE
	reader.cpp
	solver.cpp
	writer.cpp
)

target_include_directories(${MYLIB}
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}
	$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}
	$<INSTALL_INTERFACE:include
)

target_link_libraries(${MYLIB}
	PUBLIC
)