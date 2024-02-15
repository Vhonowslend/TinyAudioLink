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

# Boards:
# - Teensy 4.0
# - Teensy 4.1

set(BOARD_LIB_NAME "Teensy")
set(BOARD_ITCM "0x00000000")
set(BOARD_ITCM_SIZE "512K")
set(BOARD_DTCM "0x20000000")
set(BOARD_DTCM_SIZE "512K")
set(BOARD_SRAM "0x20200000")
set(BOARD_SRAM_SIZE "512K")
set(BOARD_FLASH "0x60000000")
set(BOARD_ERAM "0x70000000")
if(BOARD_VERSION STREQUAL "4\.1")
	set(BOARD_LINK_VERSION "41")
	set(BOARD_FLASH_SIZE "7936K")
	set(BOARD_FLASH_SIZE_FULL "8388608")
	set(BOARD_ERAM_SIZE "16384K")
elseif(BOARD_VERSION MATCHES "4(\.0)?")
	set(BOARD_LINK_VERSION "40")
	set(BOARD_FLASH_SIZE "1984K")
	set(BOARD_FLASH_SIZE_FULL "2097152")
	set(BOARD_ERAM_SIZE "0K")
elseif(BOARD_VERSION STREQUAL "M(icro)?M(od)?")
	set(BOARD_LINK_VERSION "MM")
	set(BOARD_FLASH_SIZE "16128K")
	set(BOARD_FLASH_SIZE_FULL "16777216")
	set(BOARD_ERAM_SIZE "0K")
else()
	message(FATAL_ERROR "This board (Teensy ${BOARD_VERSION}) is not yet supported. Add support for it and contribute to the project!")
endif()

add_library(${BOARD_LIB_NAME} OBJECT)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/linker/layout.ld"
	"${CMAKE_CURRENT_BINARY_DIR}/layout.ld"
	@ONLY
)

# Add Source and Include Files
file(GLOB_RECURSE SOURCES FOLLOW_SYMLINKS CONFIGURE_DEPENDS "source/*")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/source" PREFIX "Source Files" FILES ${SOURCES})
file(GLOB_RECURSE INCLUDES FOLLOW_SYMLINKS CONFIGURE_DEPENDS "include/*")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Include Files" FILES ${INCLUDES})
target_sources(${BOARD_LIB_NAME}
	PRIVATE
		${SOURCES}
	PUBLIC
		${INCLUDES}
)

# Add Include Directories
target_include_directories(${BOARD_LIB_NAME}
	PUBLIC
		"source"
		"include"
)

# Add Compile and Link Options
target_compile_options(${BOARD_LIB_NAME}
	PUBLIC
		"--target=thumbv7em-none-unknown-eabihf"
		"-mthumb"
		"-mcpu=cortex-m7"
		"-m32"
		"-mfpu=fpv5-d16"
		"-mfloat-abi=hard"
		"-funsigned-char"
		"-fpack-struct=1"
		"-fmax-type-align=4"
		"-fshort-enums"
		"-fshort-wchar"
#		"-fno-builtin"
		"-frwpi"
#		"-fpic"
#		"-fpie"
		# Unclear if Compiler or Linker 
		"-ffreestanding"
#		"-fdata-sections"
#		"-ffunction-sections"
)
target_link_options(${BOARD_LIB_NAME}
	PUBLIC
		"--target=thumbv7em-none-unknown-eabihf"
		"-nostdlib"
		"-ffreestanding"
		"-fdata-sections"
		"-ffunction-sections"
		"-frwpi"
#		"-fpic"
#		"-fpie"
	INTERFACE
		"-T" "${CMAKE_CURRENT_BINARY_DIR}/layout.ld"
)
target_compile_definitions(${BOARD_LIB_NAME}
	PRIVATE
		TEENSY_FLASH_SIZE=${BOARD_FLASH_SIZE_FULL}
)

set_target_properties(${BOARD_LIB_NAME} PROPERTIES
	# Set C++ Standard and Extensions
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF

	# Remove prefix from generated files.
	PREFIX ""
	IMPORT_PREFIX ""

	# Never treat warnings as errors.
	COMPILE_WARNING_AS_ERROR OFF
)

generate_compile_commands_json(
	TARGETS ${BOARD_LIB_NAME}
)
clang_tidy(
	TARGETS ${BOARD_LIB_NAME}
	VERSION 15.0.0
)
clang_format(
	TARGETS ${BOARD_LIB_NAME}
	VERSION 15.0.0
	DEPENDENCY
	GLOBAL
)

function(configure_board TARGET)
	get_target_property(_INTERFACE_LINK_OPTIONS "Teensy" INTERFACE_LINK_OPTIONS)

	target_sources(${TARGET} PRIVATE $<TARGET_OBJECTS:Teensy>)
	target_link_libraries(${TARGET} PRIVATE
#		$<TARGET_OBJECTS:Teensy>
		"Teensy"
	)
	target_link_options(${TARGET} PRIVATE
		"$<TARGET_PROPERTY:Teensy,INTERFACE_LINK_OPTIONS>"
		#${_INTERFACE_LINK_OPTIONS}		
	)
	target_include_directories(${TARGET} PRIVATE
		"$<TARGET_PROPERTY:Teensy,INTERFACE_INCLUDE_DIRECTORIES>"
	)

	# Post-processing so it can actually be run.
	add_custom_command(
		TARGET ${TARGET}
		POST_BUILD
		COMMAND "${CMAKE_OBJCOPY}"
		ARGS -O ihex "$<TARGET_FILE:${TARGET}>" "$<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.hex"
#		BYPRODUCTS "$<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.hex"
	)

	# Post-Processing for debugging Assembly.
	add_custom_command(
		TARGET ${TARGET}
		POST_BUILD
		COMMAND "${CMAKE_OBJDUMP}"
		ARGS --disassemble-all --line-numbers --source --demangle --symbolize-operands "$<TARGET_FILE:${TARGET}>" > "$<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.asm"
#		BYPRODUCTS "$<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.asm"
	)
endfunction()
