add_custom_target(tests
	DEPENDS ${CMAKE_PROJECT_NAME}
)

enable_testing()
find_package(GTest)
if(GTEST_FOUND)
	set(GTEST_TARGET ${CMAKE_PROJECT_NAME}_test)
    add_executable(${GTEST_TARGET})
    target_sources(${GTEST_TARGET}
		PRIVATE
		gtests.cpp
	)
	target_include_directories(${GTEST_TARGET}
		PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
		${GTEST_INCLUDE_DIRS}
	)
	target_link_libraries(${GTEST_TARGET}
		PUBLIC
		${CMAKE_PROJECT_NAME}_lib
		GTest::gtest
		GTest::gtest_main
	)
	add_dependencies(tests ${GTEST_TARGET})
	gtest_discover_tests(${GTEST_TARGET})
endif()

# ---------------------------------------------------------------------------------------
# Test main binary
# ---------------------------------------------------------------------------------------
add_custom_command(TARGET tests
	COMMAND $<TARGET_FILE:${CMAKE_PROJECT_NAME}> && echo '\\033[0;32mBINARY OK\\033[0m'
)
# ---------------------------------------------------------------------------------------
# Google tests
# ---------------------------------------------------------------------------------------
add_custom_command(TARGET tests
	COMMAND ctest
)