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

set(TARGET "${PROJECT_NAME}")

project(Teensy4
	LANGUAGES C CXX ASM
)
list(POP_BACK CMAKE_MESSAGE_INDENT)
list(APPEND CMAKE_MESSAGE_INDENT "[Teensy 4.x]" " ")
message(STATUS "${PROJECT_NAME}")

set(TEENSY_STACK_SIZE "64K" CACHE STRING "Size (in bytes) of the Stack area.")

# Boards:
# - Teensy 4.0
# - Teensy 4.1

set(BOARD_ITCM "0x00000000")
set(BOARD_ITCM_SIZE "524288")
set(BOARD_DTCM "0x20000000")
set(BOARD_DTCM_SIZE "524288")
set(BOARD_IRAM "0x20200000")
set(BOARD_IRAM_SIZE "524288")
set(BOARD_FLASH "0x60000000")
set(BOARD_ERAM "0x70000000")
if(BOARD_VERSION STREQUAL "4\.1")
	set(BOARD_LINK_VERSION "41")
	set(BOARD_FLASH_SIZE_LINK "7936K") # Flash is slightly smaller if we exclude the bootloader
	set(BOARD_FLASH_SIZE "8388608")
	set(BOARD_ERAM_SIZE "16777216")
	set(MCU "TEENSY41")
elseif(BOARD_VERSION MATCHES "4(\.0)?")
	set(BOARD_LINK_VERSION "40")
	set(BOARD_FLASH_SIZE_LINK "1984K")
	set(BOARD_FLASH_SIZE "2097152")
	set(BOARD_ERAM_SIZE "0")
	set(MCU "TEENSY40")
elseif(BOARD_VERSION STREQUAL "M(icro)?M(od)?")
	set(BOARD_LINK_VERSION "MM")
	set(BOARD_FLASH_SIZE_LINK "16128K")
	set(BOARD_FLASH_SIZE "16777216")
	set(BOARD_ERAM_SIZE "0")
	set(MCU "TEENSY_MICROMOD")
else()
	message(FATAL_ERROR "This board (Teensy ${BOARD_VERSION}) is not yet supported. Add support for it and contribute to the project!")
endif()

add_library(${PROJECT_NAME} OBJECT)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		"m" # C Math
		"c++" # C++ Stuff
)
link(${PROJECT_NAME} "NXP::IMXRT1060")
link(${PROJECT_NAME} "ARM::v7")

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		TEENSY_FLASH_SIZE=${BOARD_FLASH_SIZE_FULL}
		TEENSY_IRAM_SIZE=${BOARD_IRAM_SIZE}
		TEENSY_ERAM_SIZE=${BOARD_ERAM_SIZE}
)
target_sources(${PROJECT_NAME} INTERFACE $<TARGET_OBJECTS:${PROJECT_NAME}>)

configure_file(
	"${PROJECT_SOURCE_DIR}/include/board.h.in"
	"${PROJECT_BINARY_DIR}/include/board.h"
)

configure_file(
	"${PROJECT_SOURCE_DIR}/linker/layout.ld"
	"${PROJECT_BINARY_DIR}/linker/layout.ld"
	@ONLY
)
target_link_options(${PROJECT_NAME}
	PUBLIC
		"-T" "${CMAKE_CURRENT_BINARY_DIR}/linker/layout.ld"
)

configure(${PROJECT_NAME})

# Always do this last, it's order dependent unfortunately.
generate_compile_commands_json(TARGETS ${PROJECT_NAME})
clang_tidy(TARGETS ${PROJECT_NAME} VERSION 15.0.0)
clang_format(TARGETS ${PROJECT_NAME} VERSION 15.0.0 DEPENDENCY GLOBAL)

# Upload command
if(CMAKE_HOST_WIN32)
	set(FURL "https://github.com/Xaymar/teensy_loader_cli/releases/download/2.3.1/Windows.2022.zip")
	set(FEXT ".exe")
elseif(CMAKE_HOST_APPLE)
	set(FURL "https://github.com/Xaymar/teensy_loader_cli/releases/download/2.3.1/MacOS.14.zip")
	set(FEXT "")
else()
	set(FURL "https://github.com/Xaymar/teensy_loader_cli/releases/download/2.3.1/Ubuntu.24.zip")
	set(FEXT "")
endif()
if(NOT EXISTS "${PROJECT_BINARY_DIR}/bin/teensy_loader_cli${FEXT}")
	set(FDST "${PROJECT_BINARY_DIR}/teensy_loader_cli.zip")
	file(DOWNLOAD
		"${FURL}"
		"${FDST}"
	)
	
	file(ARCHIVE_EXTRACT 
		INPUT "${FDST}"
		DESTINATION "${PROJECT_BINARY_DIR}/"
	)
endif()

add_custom_target(upload
	COMMAND "${PROJECT_BINARY_DIR}/bin/teensy_loader_cli${FEXT}" --mcu=${MCU} -w "$<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.hex"
	DEPENDS all
	COMMAND_EXPAND_LISTS
)
