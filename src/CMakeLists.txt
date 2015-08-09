cmake_minimum_required(VERSION 2.8.7)

# Regarding Microsoft Visual Studio:
# Creating proper builds with MSVC required setting subsystem to windows,
# otherwise an unwanted console window was created. However when subsystem is
# set to windows MSVC uses WinMain() as the entry point, while MinGW simply
# keeps using the main() function. Also note that since console window is useful
# for debugging, Debug builds still have subsystem set to console.
#
# To solve all the issues WinMain() has been implemented and is now used
# depending on certain defines: if _MSC_VER is defined it means that user is
# attempting to create a build with MSVC. Also if NDEBUG is defined it means
# that user chose one of the Release builds. When both of these conditions are
# met then, and only then, WinMain() is used instead of main() as the
# entry point.
#
# Conclusion: If current MSVC subsystem setup is changed the code may not
# compile, as the proper entry point will be missing.

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
	cmake_policy(SET CMP0005 NEW)
	if (POLICY CMP0020)
		cmake_policy(SET CMP0020 OLD) # We have our own WinMain.
	endif()
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
set(QT_LIBRARIES Qt5::Widgets Qt5::Gui Qt5::Core)
set(QT_INCLUDES ${Qt5Widgets_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})
get_target_property(QMAKE_EXEC Qt5::qmake LOCATION)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${QT_INCLUDES}
	${CMAKE_CURRENT_BINARY_DIR}
)

if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif ()

include("CMakeSpawnFileListing.txt")
# This hack allows CMake to regenerate the project when spawned
# file listing file changes from outside sources. This covers
# updating local repo and checking out different revisions.
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/CMakeFileListing.txt"
	"${CMAKE_CURRENT_SOURCE_DIR}/CMakeFileListing.txt"
	NEWLINE_STYLE LF
)
include("CMakeFileListing.txt")

qt5_wrap_ui(ui ${UI_FILES})

qt5_add_resources(resources
	${CMAKE_SOURCE_DIR}/media/resources.qrc
)

# windows.rc
if(WIN32)
	# compile the Windows resource file.  How we do this depends on the compiler.
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		add_custom_command(
			OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/windows.o
			COMMAND windres -o ${CMAKE_CURRENT_BINARY_DIR}/windows.o -i ${CMAKE_CURRENT_SOURCE_DIR}/windows.rc
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			COMMENT "Generating windows resources (windows.rc)"
		)

		set(SOURCE_FILES ${SOURCE_FILES} windows.o)
	else()
		set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/windows.rc)
	endif()
endif()

add_executable(stayfocused
	${ui}
	${resources}
	${UI_FILES}
	${SOURCE_FILES}
	${HEADER_FILES}
)

target_link_libraries(stayfocused ${QT_LIBRARIES} ${CMAKE_DL_LIBS})

set_target_properties(stayfocused PROPERTIES AUTOMOC 1)
set_target_properties(stayfocused PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
if(WIN32)
	if(MSVC)
		set_target_properties(stayfocused PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
		set_target_properties(stayfocused PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")
		set_target_properties(stayfocused PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
	else(MSVC)
		set_target_properties(stayfocused PROPERTIES LINK_FLAGS_RELEASE "-Wl,-subsystem,windows")
		set_target_properties(stayfocused PROPERTIES LINK_FLAGS_MINSIZEREL "-Wl,-subsystem,windows")
	endif()

	# Install program DIRECTLY to directory specified by
	# ${CMAKE_INSTALL_PREFIX}. If ${CMAKE_INSTALL_PREFIX} is set to something
	# stupid like "C:\Program Files\" (this is the CMake's default, BTW)
	# then program.exe will be dumped to "C:\Program Files\program.exe"
	install(TARGETS stayfocused RUNTIME DESTINATION .)
	# Install Qt libraries.
	# Qt5*.dll
	foreach(qtlib ${QT_LIBRARIES})
		get_target_property(qtlib_location ${qtlib} LOCATION)
		install(FILES ${qtlib_location} DESTINATION .)
	endforeach()
	# plugins
	execute_process(COMMAND ${QMAKE_EXEC} -query QT_INSTALL_PLUGINS
		OUTPUT_VARIABLE QT_PLUGINS_DIR
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	install(FILES ${QT_PLUGINS_DIR}/platforms/qwindows.dll DESTINATION platforms)
	# ICU (the 26.6 Megabyte bastard)
	#
	# Installation of ICU is optional. If you don't have ICU
	# files, it's possible that your Qt installation doesn't
	# need them. That's very good as ICU files weight about 30
	# Megabytes and program makes no use of them.
	execute_process(COMMAND ${QMAKE_EXEC} -query QT_INSTALL_LIBEXECS
		OUTPUT_VARIABLE QT_LIBEXECS_DIR
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	install(FILES
		${QT_LIBEXECS_DIR}/icuin53.dll
		${QT_LIBEXECS_DIR}/icuuc53.dll
		${QT_LIBEXECS_DIR}/icudt53.dll
		DESTINATION . OPTIONAL)
	# Install .ico file. No idea what purpose would this serve but some
	# programs come with their icons in the .ico file so why not.
	install(FILES ${CMAKE_SOURCE_DIR}/media/icon.ico DESTINATION .
		RENAME stayfocused.ico
	)
	# Install MSVC runtime. Only Visual 2008 and 2013 are supported at the moment.
	if (MSVC90 OR MSVC12)
		# Install redist and manifest for the program.
		include("${CMAKE_SOURCE_DIR}/cmake/Modules/FindRequiredSystemLibraries.cmake")
		install_programs(. ${REQUIRED_SYSTEM_LIBRARIES})
	endif()

	# License files.
	# Text files in Windows distribution really should have a .txt extension
	# so rename them all accordingly.
	set(LICENSE_FILES
		LICENSE.txt
	)
	install(FILES "${CMAKE_SOURCE_DIR}/LICENSE.txt" DESTINATION .)
endif()
