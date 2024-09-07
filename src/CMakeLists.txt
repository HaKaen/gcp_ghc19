set(MYLIB "${CMAKE_PROJECT_NAME}_lib")

add_library(${MYLIB} STATIC)
set_default_warnings(${MYLIB})

target_sources(${MYLIB}
	PRIVATE
	data.cpp
	reader.cpp
	solver.cpp
	writer.cpp
)

target_include_directories(${MYLIB}
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
	$<INSTALL_INTERFACE:include>
)

target_link_libraries(${MYLIB}
	PUBLIC
)