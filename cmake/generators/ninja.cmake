# Copyright (C) 2024 Michael Fabian 'Xaymar' Dirks
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
include_guard(GLOBAL)

list(APPEND CMAKE_MESSAGE_INDENT "[Ninja] ")
set(_VERSION "1.12.1")
set(_FILE "ninja-${CMAKE_HOST_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}")
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows") # Windows
	set(_FILEEXT "zip")
	if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
		set(_FILENAME "ninja-win")
	else()
		set(_FILENAME "ninja-winarm64")
	endif()
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin") # Darwin
	set(_FILEEXT "dmg")
	set(_FILENAME "ninja-mac")
else() # Generic Unix-like
	set(_FILEEXT "tar.xz")
	if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
		set(_FILENAME "ninja-linux")
	else()
		set(_FILENAME "ninja-linux-aarch64")
	endif()
endif()

# Very hacky way to get CMake to behave like a normal makefile generator, instead of a mentally challenged makefile generator.
if(TRUE) # Check if we've already installed one of these, 
	if(WIN32)
		set(TEMP "$ENV{TEMP}")
	else()
		set(TEMP "$ENV{TMPDIR}")
	endif()
	set(_PATH "${TEMP}/cmake/ninja/${_VERSION}")
	if(EXISTS "${_PATH}")
		file(READ "${_PATH}" _DIR)
		if (NOT EXISTS "${_DIR}")
			file(REMOVE "${_PATH}")
			unset(_DIR)
		endif()
	endif()
endif()

find_program(
	_NINJA
	NAMES
		ninja
	PATHS

	NO_CACHE
)
if(_NINJA)
	execute_process(
		COMMAND "${_NINJA}" "--version"
		OUTPUT_VARIABLE _VERSION_INSTALLED
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	string(REGEX REPLACE "[\r\n]+" "" _VERSION_INSTALLED "${_VERSION_INSTALLED}")
endif()

if((NOT _DIR) OR (EXISTS "${PROJECT_BINARY_DIR}/toolchain/${_FILE}.version"))
	if((NOT _VERSION_INSTALLED) OR (_VERSION_INSTALLED VERSION_LESS _VERSION))
		if(EXISTS "${PROJECT_BINARY_DIR}/toolchain/${_FILE}.version")
			file(READ "${PROJECT_BINARY_DIR}/toolchain/${_FILE}.version" _VERSION_STORED)
		endif()
		if((NOT _VERSION_STORED) OR (_VERSION_STORED VERSION_LESS _VERSION))
			message(STATUS "Updating... (${_VERSION_INSTALLED} < ${_VERSION}, ${_VERSION_STORED} < ${_VERSION})")

			# Download the appropriate package from https://github.com/ninja-build/ninja
			set(_PACKAGE_FILE "${PROJECT_BINARY_DIR}/toolchain/${_FILE}.${_FILEEXT}")
			file(DOWNLOAD
				"https://github.com/ninja-build/ninja/releases/download/v${_VERSION}/${_FILENAME}.${_FILEEXT}"
				"${_PACKAGE_FILE}"
			)

			#- Extract the contents
			file(ARCHIVE_EXTRACT 
				INPUT "${_PACKAGE_FILE}"
				DESTINATION "${PROJECT_BINARY_DIR}/toolchain/ninja/"
			)
			file(REMOVE "${_PACKAGE_FILE}")

			file(WRITE "${PROJECT_BINARY_DIR}/toolchain/${_FILE}.version" "${_VERSION}")
		endif()

		find_program(
			CMAKE_MAKE_PROGRAM
			NAMES
				ninja
			PATHS
				"${PROJECT_BINARY_DIR}/toolchain/ninja/"
			NO_DEFAULT_PATH NO_PACKAGE_ROOT_PATH NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_INSTALL_PREFIX NO_CMAKE_FIND_ROOT_PATH
		)
	endif()
	
	# Update the virtual link
	file(WRITE "${_PATH}" "${PROJECT_BINARY_DIR}/toolchain/ninja/")
else()
	find_program(
		CMAKE_MAKE_PROGRAM
		NAMES
			ninja
		PATHS
			"$_DIR"
		NO_DEFAULT_PATH NO_PACKAGE_ROOT_PATH NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_INSTALL_PREFIX NO_CMAKE_FIND_ROOT_PATH
	)
endif()

execute_process(
	COMMAND "${CMAKE_MAKE_PROGRAM}" "--version"
	OUTPUT_VARIABLE _VERSION_INSTALLED
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "v${_VERSION_INSTALLED}")
list(POP_BACK CMAKE_MESSAGE_INDENT)