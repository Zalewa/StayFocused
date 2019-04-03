cmake_minimum_required(VERSION 2.8.7)
project(StayFocused)

if(MSVC12)
	set(CMAKE_GENERATOR_TOOLSET "v120_xp")
endif()

add_subdirectory(src)

message(STATUS "'INSTALL' will dump files to \"${CMAKE_INSTALL_PREFIX}\"")
