cmake_minimum_required(VERSION 3.25)

include_guard(GLOBAL)

function(set_default_warnings target)
	if (CMAKE_COMPILER_IS_GNUCXX)
		target_compile_options(${target}
			PRIVATE
			-Wall
			#https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#index-Wall
			-Wextra
			#https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#index-W
			-Werror
			)
	endif()
endfunction()