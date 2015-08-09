cmake_minimum_required(VERSION 2.8.7)
project(StayFocused)

if(MSVC12)
	set(CMAKE_GENERATOR_TOOLSET "v120_xp")
endif()

if(NOT WIN32)
	find_package( ZLIB )
	find_package( BZip2 )
endif()

if(MSVC AND NOT MSVC90 AND NOT MSVC12)
	message(WARNING
		"Full automatic packaging is only supported for Microsoft Visual C++ 2008 and 2013. "
		"Remember that redist needs to be accessible both by the main program "
		"and by the engines/ directory. Copy over Manifest and redist DLLs to "
		"engines/ directory if you do not plan on installing redist on target "
		"machines."
	)
endif()

add_subdirectory(src)

message(STATUS "'INSTALL' will dump files to \"${CMAKE_INSTALL_PREFIX}\"")
