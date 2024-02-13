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

set(LLVM_VERSION "17.0.1")
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows") # Windows
	set(LLVM_FILENAME "LLVMEmbeddedToolchainForArm-${LLVM_VERSION}-Windows-x86_64")
	set(LLVM_FILEEXT "zip")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin") # Darwin
	set(LLVM_FILENAME "LLVMEmbeddedToolchainForArm-${LLVM_VERSION}-Darwin")
	set(LLVM_FILEEXT "dmg")
else() # Generic Unix-like
	set(LLVM_FILEEXT "tar.xz")
	if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
		set(LLVM_FILENAME "LLVMEmbeddedToolchainForArm-${LLVM_VERSION}-Linux-x86_64")
	else()
		set(LLVM_FILENAME "LLVMEmbeddedToolchainForArm-${LLVM_VERSION}-Linux-AArch64")
	endif()
endif()

# Check if the version is what we expect.
if(EXISTS "${PROJECT_BINARY_DIR}/toolchain/toolchain.version")
	file(READ "${PROJECT_BINARY_DIR}/toolchain/toolchain.version" LLVM_VERSION_STORED)
endif()
file(WRITE "${PROJECT_BINARY_DIR}/toolchain/toolchain.version" "${LLVM_VERSION}")
if(NOT (LLVM_VERSION_STORED EQUAL LLVM_VERSION))
	message(STATUS "LLVM-ARM not downloaded or version mismatch, redownloading...")

	# Download the appropriate package from https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm
	#- Grab the latest hash from the remote.
	set(_HASH_FILE "${PROJECT_BINARY_DIR}/toolchain/toolchain.sha256")
	file(DOWNLOAD
		"https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm/releases/download/release-${LLVM_VERSION}/${LLVM_FILENAME}.${LLVM_FILEEXT}.sha256"
		"${_HASH_FILE}"
	)
	file(READ "${_HASH_FILE}" LLVM_DOWNLOAD_SHA256)
	string(REGEX MATCH "[0-9a-fA-F]+" LLVM_DOWNLOAD_SHA256 "${LLVM_DOWNLOAD_SHA256}")
	#message(STATUS "Expected Hash: ${LLVM_DOWNLOAD_SHA256}")
	#- Download the latest toolchain
	set(_PACKAGE_FILE "${PROJECT_BINARY_DIR}/toolchain/toolchain.${LLVM_FILEEXT}")
	file(DOWNLOAD
		"https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm/releases/download/release-${LLVM_VERSION}/${LLVM_FILENAME}.${LLVM_FILEEXT}"
		"${_PACKAGE_FILE}"
		SHOW_PROGRESS
		EXPECTED_HASH SHA256=${LLVM_DOWNLOAD_SHA256}
	)
endif()
if(NOT (EXISTS "${PROJECT_BINARY_DIR}/toolchain/${LLVM_FILENAME}/bin"))
	#- Extract the contents
	file(ARCHIVE_EXTRACT 
		INPUT "${_PACKAGE_FILE}"
		DESTINATION "${PROJECT_BINARY_DIR}/toolchain/"
	)
endif()

# Find necessary programs.
find_program(
	CLANG_C_COMPILER
	NAMES
		clang
		clang-cl
		clang++
		clang-cpp
	PATHS
		"${PROJECT_BINARY_DIR}/toolchain/${LLVM_FILENAME}/bin"
	NO_DEFAULT_PATH NO_PACKAGE_ROOT_PATH NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_INSTALL_PREFIX NO_CMAKE_FIND_ROOT_PATH
	NO_CACHE
)
find_program(
	CLANG_CPP_COMPILER
	NAMES
		clang++
		clang-cpp
		clang
		clang-cl
	PATHS
		"${PROJECT_BINARY_DIR}/toolchain/${LLVM_FILENAME}/bin"
	NO_DEFAULT_PATH NO_PACKAGE_ROOT_PATH NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_INSTALL_PREFIX NO_CMAKE_FIND_ROOT_PATH
	NO_CACHE
)
find_program(
	CLANG_LLVM_AR
	NAMES
		llvm-ar
	PATHS
		"${PROJECT_BINARY_DIR}/toolchain/${LLVM_FILENAME}/bin"
	NO_DEFAULT_PATH NO_PACKAGE_ROOT_PATH NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_INSTALL_PREFIX NO_CMAKE_FIND_ROOT_PATH
	NO_CACHE
)
find_program(
	CLANG_LLVM_LD_LDD
	NAMES
		ld.lld
	PATHS
		"${PROJECT_BINARY_DIR}/toolchain/${LLVM_FILENAME}/bin"
	NO_DEFAULT_PATH NO_PACKAGE_ROOT_PATH NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_INSTALL_PREFIX NO_CMAKE_FIND_ROOT_PATH
	NO_CACHE
)
mark_as_advanced(CLANG_C_COMPILER CLANG_CPP_COMPILER CLANG_LLVM_AR CLANG_LLVM_LD_LDD)

set(CMAKE_C_COMPILER "${CLANG_C_COMPILER}")
set(CMAKE_CXX_COMPILER "${CLANG_CPP_COMPILER}")
set(CMAKE_AR "${CLANG_LLVM_AR}")

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
	set(CMAKE_LINKER_TYPE "LLD")
else()
#	set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=\"${CLANG_LLVM_LD_LDD}\"")
#	set(CMAKE_STATIC_LINKER_FLAGS_INIT "-fuse-ld=\"${CLANG_LLVM_LD_LDD}\"")
#	set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fuse-ld=\"${CLANG_LLVM_LD_LDD}\"")
#	set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=\"${CLANG_LLVM_LD_LDD}\"")
endif()
