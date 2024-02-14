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

cmake_minimum_required(VERSION 3.26)
list(APPEND CMAKE_MESSAGE_INDENT "[TinyAudioLink] ")
project(TinyAudioLink)

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

# Parse & Log the detected version.
message(STATUS "Version ${_VERSION_THIN}")

# Metadata
version(GENERATE PROJECT_VERSION
	MAJOR "${_VERSION_MAJOR}"
	MINOR "${_VERSION_MINOR}"
	PATCH "${_VERSION_PATCH}"
	TWEAK "${_VERSION_TWEAK}"
	REQUIRE "PATCH;TWEAK"
)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

################################################################################
# Project
################################################################################

add_executable(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES
	# Set C++ Standard and Extensions
	C_STANDARD 23
	C_STANDARD_REQUIRED ON
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF

	# Remove prefix from generated files.
	PREFIX ""
	IMPORT_PREFIX ""

	# Never treat warnings as errors.
	COMPILE_WARNING_AS_ERROR OFF
)

file(GLOB_RECURSE SOURCES FOLLOW_SYMLINKS CONFIGURE_DEPENDS "source/*")
#list(FILTER SOURCES INCLUDE REGEX ".*\.(c|h|cxx|hxx|cpp|hpp)$")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/source" PREFIX "Source Files" FILES ${TEMPLATES})
target_sources(${PROJECT_NAME}
	PRIVATE
		${SOURCES}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		"source"
)

generate_compile_commands_json(
	TARGETS ${PROJECT_NAME}
)
clang_tidy(
	TARGETS ${PROJECT_NAME}
	DEPENDENCY
	VERSION 15.0.0
)
clang_format(
	TARGETS ${PROJECT_NAME}
	DEPENDENCY
	VERSION 15.0.0
)

# Board Specific
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
	# Teensy 4.1
	if(BOARD_NAME STREQUAL "Teensy 4.1")
		target_link_options(${PROJECT_NAME} PRIVATE
			"-T" "${PROJECT_SOURCE_DIR}/source/teensy41/layout.ld"
		)

		# Post-processing so it can actually be run.
		add_custom_command(
			TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND "${CMAKE_OBJCOPY_BIN}"
			ARGS -O ihex "$<TARGET_FILE:${PROJECT_NAME}>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>.bin"
		)
	endif()
endif()
