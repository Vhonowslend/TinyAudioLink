# TinyAudioLink - Seamlessly transfer Audio between USB capable devices
# Copyright (C) 2019 Michael Fabian 'Xaymar' Dirks
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.30...4.0)
project(TinyAudioLink
	LANGUAGES C CXX ASM
)
list(APPEND CMAKE_MESSAGE_INDENT "[TinyAudioLink]" " ")

################################################################################
# Modules
################################################################################

# Search Paths
set(CMAKE_MODULE_PATH
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/clang"
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/version"
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

# Include required Modules
include("CheckIPOSupported")
include("version")
include("Clang")

################################################################################
# Versioning
################################################################################

version(GENERATE _VERSION COMPRESSED MAJOR 0 MINOR 0 PATCH 0 TWEAK 0 REQUIRE "PATCH;")
version(PARSE _VERSION "${_VERSION}" REQUIRE "PATCH;TWEAK")

# If possible, automatically generate versions from git.
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/.git")
	find_program(GIT
		NAMES
			git
			git.exe
	)

	if(EXISTS "${GIT}")
		# Try and calculate the exist version using git.
		execute_process(COMMAND "${GIT}" describe --tags --long --abbrev=8 HEAD WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} RESULT_VARIABLE GIT_RESULT OUTPUT_VARIABLE GIT_OUTPUT ERROR_VARIABLE GIT_ERROR OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
		if((GIT_RESULT EQUAL 0) AND (NOT "${GIT_OUTPUT}" STREQUAL ""))
			# Result will be MAJOR.MINOR.PATCH-TWEAK-gHASH
			string(REPLACE "-" ";" GIT_OUTPUT "${GIT_OUTPUT}")
			string(REPLACE "." ";" GIT_OUTPUT "${GIT_OUTPUT}")

			# Split into components
			list(GET GIT_OUTPUT 0 GIT_OUTPUT_MAJOR)
			list(GET GIT_OUTPUT 1 GIT_OUTPUT_MINOR)
			list(GET GIT_OUTPUT 2 GIT_OUTPUT_PATCH)
			list(GET GIT_OUTPUT 3 GIT_OUTPUT_TWEAK)
			list(GET GIT_OUTPUT 4 GIT_OUTPUT_BUILD)

			# Special case: Tag contains prerelease
			if(GIT_OUTPUT_PATCH MATCHES "([0-9]+)([a-zA-Z]+)([0-9]*)")
				# Patch requires special parsing.
				set(GIT_OUTPUT_PATCH "${CMAKE_MATCH_1}")
				if(CMAKE_MATCH_3 GREATER 0)
					set(GIT_OUTPUT_PRERELEASE "${CMAKE_MATCH_2}")
				else()
					set(GIT_OUTPUT_PRERELEASE "a")
				endif()
				MATH(EXPR GIT_OUTPUT_TWEAK "${GIT_OUTPUT_TWEAK} + ${CMAKE_MATCH_3}")

				# Modify the global version
				version(MODIFY _VERSION "${_VERSION}" COMPRESS
					MAJOR "${GIT_OUTPUT_MAJOR}"
					MINOR "${GIT_OUTPUT_MINOR}"
					PATCH "${GIT_OUTPUT_PATCH}"
					TWEAK "${GIT_OUTPUT_TWEAK}"
					BUILD "${GIT_OUTPUT_BUILD}"
					PRERELEASE "${GIT_OUTPUT_PRERELEASE}"
					REQUIRE "PATCH;TWEAK"
				)
			else()
				# Modify the global version
				version(MODIFY _VERSION "${_VERSION}" COMPRESS
					MAJOR "${GIT_OUTPUT_MAJOR}"
					MINOR "${GIT_OUTPUT_MINOR}"
					PATCH "${GIT_OUTPUT_PATCH}"
					TWEAK "${GIT_OUTPUT_TWEAK}"
					BUILD "${GIT_OUTPUT_BUILD}"
					PRERELEASE "a"
					REQUIRE "PATCH;TWEAK"
				)
			endif()
		else()
			execute_process(COMMAND "${GIT}" rev-list --count HEAD WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} RESULT_VARIABLE GIT_RESULT OUTPUT_VARIABLE GIT_OUTPUT ERROR_VARIABLE GIT_ERROR OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
			if((GIT_RESULT EQUAL 0) AND (NOT "${GIT_OUTPUT}" STREQUAL ""))
				version(MODIFY _VERSION "${_VERSION}" COMPRESS
					TWEAK "${GIT_OUTPUT}"
					PRERELEASE "a"
					REQUIRE "PATCH;TWEAK"
				)

				# Determine the build using git.
				execute_process(COMMAND "${GIT}" log -1 "--pretty=format:g%h" --abbrev=8 HEAD WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} RESULT_VARIABLE GIT_RESULT OUTPUT_VARIABLE GIT_OUTPUT ERROR_VARIABLE GIT_ERROR OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
				if((GIT_RESULT EQUAL 0) AND (NOT "${GIT_OUTPUT}" STREQUAL ""))
					version(MODIFY _VERSION "${_VERSION}" COMPRESS
						BUILD "${GIT_OUTPUT}"
						REQUIRE "PATCH;TWEAK"
					)
				else()
					message(WARNING "Failed to detect build version with 'git'.")
				endif()
			else()
				message(WARNING "Failed to automatically detect version with 'git'.")
			endif()
		endif()
	else()
		message(WARNING "'git' not found, automatic version detection disabled.")
	endif()
else()
	message(STATUS "Not a git repository, automatic version detection disabled.")
endif()

# Allow manual overrides of the detected version.
if(${PREFIX}VERSION)
	version(PARSE _VERSION_CFG "${${PREFIX}VERSION}" REQUIRE "PATCH;TWEAK")
	if("${_VERSION_CFG_BUILD}" STREQUAL "")
		set(_VERSION_CFG_BUILD "${_VERSION_BUILD}")
	endif()
	version(GENERATE _VERSION COMPRESS
		MAJOR "${_VERSION_CFG_MAJOR}"
		MINOR "${_VERSION_CFG_MINOR}"
		PATCH "${_VERSION_CFG_PATCH}"
		TWEAK "${_VERSION_CFG_TWEAK}"
		PRERELEASE "${_VERSION_CFG_PRERELEASE}"
		BUILD "${_VERSION_CFG_BUILD}"
	)
endif()

# Fix up missing parts of the Version
version(PARSE _VERSION "${_VERSION}" REQUIRE "PATCH;TWEAK")

set(_VERSION_THIN "${_VERSION_MAJOR}.${_VERSION_MINOR}.${_VERSION_PATCH}")
if(NOT (_VERSION_PRERELEASE STREQUAL ""))
	set(_VERSION_THIN "${_VERSION_THIN}${_VERSION_PRERELEASE}${_VERSION_TWEAK}")
endif()
if(NOT (VERSION_COMMIT STREQUAL ""))
	set(_VERSION_THIN "${_VERSION_THIN}-${_VERSION_BUILD}")
endif()

# Metadata
version(GENERATE PROJECT_VERSION
	MAJOR "${_VERSION_MAJOR}"
	MINOR "${_VERSION_MINOR}"
	PATCH "${_VERSION_PATCH}"
	TWEAK "${_VERSION_TWEAK}"
	REQUIRE "PATCH;TWEAK"
)

################################################################################
# Options
################################################################################
set(BOARD_NAME "${BOARD_NAME}" CACHE STRING "The Board for which to build, see '/platform/boards'.")
set(BOARD_VERSION "${BOARD_VERSION}" CACHE STRING "Which board version are we building for? See '/platform/boards/$BOARD_NAME/.")
set(ENABLE_EXCEPTIONS ON CACHE BOOL "Enable support for C++ Exceptions? This massively bloats the file.")

################################################################################
# Functionality
################################################################################
function(configure TARGET)
	set_target_properties(${TARGET} PROPERTIES
		# Set C++ Standard and Extensions
		C_STANDARD 17
		C_STANDARD_REQUIRED ON
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
	)
	target_compile_options(${TARGET}
		PRIVATE
			# C++: Prefer Copy without temporary objects
			"$<$<COMPILE_LANGUAGE:CXX>:-felide-constructors>"
			# Don't bother with frame pointers
			"$<$<COMPILE_LANGUAGE:CXX>:-fomit-frame-pointer>"
			# Experimental support for C++ Modules.
			"$<$<COMPILE_LANGUAGE:CXX>:-fmodules>"
			# Default to hiding everything. Sometimes results in smaller binaries
			"$<$<COMPILE_LANGUAGE:CXX>:-fvisibility=hidden>"
	)
	target_link_options(${TARGET}
		PRIVATE
			# Tell the linker to strip whatever is not needed at the end.
			"$<$<CONFIG:Release,MinSizeRel>:-Xlinker>" "$<$<CONFIG:Release,MinSizeRel>:--strip-all>"
	)
	if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
		# Prefer Thin-LTO over Whole-LTO (it's faster, and seems to be better now too).
		foreach(CONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
			get_target_property(LTO ${TARGET} INTERPROCEDURAL_OPTIMIZATION_${CONFIG})
			if(LTO)
				target_compile_options(${TARGET} PRIVATE "$<$<CONFIG:${CONFIG}>:-flto=thin>")
				target_link_options(${TARGET} PRIVATE "$<$<CONFIG:${CONFIG}>:-flto=thin>")
			endif()
		endforeach()
	endif()
	if(NOT ENABLE_EXCEPTIONS)
		target_compile_options(${TARGET}
			PRIVATE
				# C++: No Run-Time Type Information
				"$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>"
				"$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>"
		)
	else()
		target_compile_options(${TARGET}
			PRIVATE
				# C++: Run-Time Type Information
				"$<$<COMPILE_LANGUAGE:CXX>:-frtti>"
				"$<$<COMPILE_LANGUAGE:CXX>:-fexceptions>"
		)
	endif()

	# Add Source and Include Files
	file(GLOB_RECURSE _INCLUDE FOLLOW_SYMLINKS CONFIGURE_DEPENDS "${${TARGET}_SOURCE_DIR}/include/*")
	source_group(TREE "${${TARGET}_SOURCE_DIR}/include" PREFIX "Public" FILES ${_INCLUDE})
	file(GLOB_RECURSE _SOURCE FOLLOW_SYMLINKS CONFIGURE_DEPENDS "${${TARGET}_SOURCE_DIR}/source/*")
	source_group(TREE "${${TARGET}_SOURCE_DIR}/source" PREFIX "Private" FILES ${_SOURCE})
	file(GLOB_RECURSE _INCLUDEG FOLLOW_SYMLINKS CONFIGURE_DEPENDS "${${TARGET}_BINARY_DIR}/include/*")
	source_group(TREE "${${TARGET}_BINARY_DIR}/include" PREFIX "Public" FILES ${_INCLUDEG})
	file(GLOB_RECURSE _SOURCEG FOLLOW_SYMLINKS CONFIGURE_DEPENDS "${${TARGET}_BINARY_DIR}/source/*")
	source_group(TREE "${${TARGET}_BINARY_DIR}/source" PREFIX "Private" FILES ${_SOURCEG})
	target_sources(${TARGET}
		PRIVATE ${_SOURCE} ${_SOURCEG}
		PUBLIC ${_INCLUDE} ${_INCLUDEG}
	)
	target_include_directories(${TARGET}
		PRIVATE
			"${PROJECT_SOURCE_DIR}/source"
			"${PROJECT_BINARY_DIR}/source"
		PUBLIC
			"${PROJECT_SOURCE_DIR}/include"
			"${PROJECT_BINARY_DIR}/include"
	)
endfunction()

function(link TARGET LINK_TARGET)
	target_link_libraries(${TARGET}
		PUBLIC
			${LINK_TARGET}
	)	
	# Supposedly no longer needed as of CMake 3.12 or so, but does not work as expected on 3.30. GG
#	target_sources(${TARGET} PUBLIC $<TARGET_OBJECTS:${LINK_TARGET}>)
#	target_include_directories(${TARGET} PUBLIC
#		"$<TARGET_PROPERTY:${LINK_TARGET},INTERFACE_INCLUDE_DIRECTORIES>"
#	)
#	target_link_options(${TARGET} PUBLIC
#		"$<TARGET_PROPERTY:${LINK_TARGET},INTERFACE_LINK_OPTIONS>"
#	)
#	target_compile_options(${TARGET} PUBLIC
#		"$<TARGET_PROPERTY:${LINK_TARGET},INTERFACE_COMPILE_OPTIONS>"
#	)
endfunction()

function(postprocess TARGET)
	# Post-Processing for debugging Assembly.
	set_property(
		TARGET ${TARGET}
		APPEND PROPERTY ADDITIONAL_CLEAN_FILES "$<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.asm"
	)
	add_custom_command(
		TARGET ${TARGET}
		POST_BUILD
		COMMAND "${CMAKE_OBJDUMP}"
		ARGS --disassemble-all --disassemble-zeroes --source --line-numbers --symbolize-operands "$<TARGET_FILE:${TARGET}>" > "$<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.asm"
	)

	# Post-processing so it can actually be run.
	set_property(
		TARGET ${TARGET}
		APPEND PROPERTY ADDITIONAL_CLEAN_FILES "$<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.hex"
	)
	add_custom_command(
		TARGET ${TARGET}
		POST_BUILD
		COMMAND "${CMAKE_OBJCOPY}"
		ARGS -O ihex "$<TARGET_FILE:${TARGET}>" "$<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.hex"
	)

endfunction()

################################################################################
# Sub-projects
################################################################################

# CPUs
file(GLOB _CPUS LIST_DIRECTORIES TRUE RELATIVE "${CMAKE_SOURCE_DIR}" CONFIGURE_DEPENDS "platform/cpus/*")
message(STATUS "CPUs Supported: ")
foreach(_T IN LISTS _CPUS)
	add_subdirectory("${_T}")
endforeach()

# System-on-Chips
file(GLOB _SOCS LIST_DIRECTORIES TRUE RELATIVE "${CMAKE_SOURCE_DIR}" CONFIGURE_DEPENDS "platform/chips/*")
message(STATUS "SoCs Supported: ")
foreach(_T IN LISTS _SOCS)
	add_subdirectory("${_T}")
endforeach()

# Boards
file(GLOB _BOARDS LIST_DIRECTORIES TRUE RELATIVE "${CMAKE_SOURCE_DIR}" CONFIGURE_DEPENDS "platform/boards/*")
message(STATUS "Boards Supported: ")
foreach(_T IN LISTS _BOARDS)
	add_subdirectory("${_T}")
endforeach()

################################################################################
# Project
################################################################################

project(TinyAudioLink
	LANGUAGES C CXX ASM
	VERSION ${PROJECT_VERSION}
)

# Log the detected version.
message(STATUS "Version ${_VERSION_THIN}")

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
	m
	c++
)
link(${PROJECT_NAME} ${BOARD_NAME})

configure(${PROJECT_NAME})

postprocess(${PROJECT_NAME})

# Always do this last, it's order dependent unfortunately.
generate_compile_commands_json(TARGETS ${PROJECT_NAME})
clang_tidy(TARGETS ${PROJECT_NAME} VERSION 15.0.0)
clang_format(TARGETS ${PROJECT_NAME} VERSION 15.0.0 DEPENDENCY GLOBAL)
