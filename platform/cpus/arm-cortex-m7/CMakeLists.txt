project(ARM_Cortex_M7
	LANGUAGES C CXX ASM
)
list(POP_BACK CMAKE_MESSAGE_INDENT)
list(APPEND CMAKE_MESSAGE_INDENT "[ARM Cortex M7]" " ")
message(STATUS "${PROJECT_NAME}")

add_library(${PROJECT_NAME} OBJECT EXCLUDE_FROM_ALL)
add_library(ARM::Cortex_M7 ALIAS ${PROJECT_NAME})
configure(${PROJECT_NAME})

file(GLOB_RECURSE _INCLUDE FOLLOW_SYMLINKS CONFIGURE_DEPENDS "include/*")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Public" FILES ${_INCLUDE})
file(GLOB_RECURSE _SOURCE FOLLOW_SYMLINKS CONFIGURE_DEPENDS "source/*")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/source" PREFIX "Private" FILES ${_SOURCE})
target_sources(${PROJECT_NAME}
	PRIVATE ${_SOURCE}
	PUBLIC ${_INCLUDE}
)
target_include_directories(${PROJECT_NAME}
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/source"
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_compile_options(${PROJECT_NAME}
	PUBLIC
		# ARMv7 Thumb, with Hard Float v5/d16
		"--target=thumbv7em-none-unknown-eabihf"
		"-mfpu=fpv5-d16"
		# Read/Write Position Independent Code
		"-frwpi"		
		# C++: Prefer Copy without temporary objects
		"$<$<COMPILE_LANGUAGE:CXX>:-felide-constructors>"
		# C++: Run-Time Type Information
		"$<$<COMPILE_LANGUAGE:CXX>:-frtti>"
		# Don't bother with frame pointers
		"$<$<COMPILE_LANGUAGE:CXX>:-fomit-frame-pointer>"
		# Default to hiding everything. Sometimes results in smaller binaries
		"$<$<COMPILE_LANGUAGE:CXX>:-fvisibility=hidden>"
)
target_link_options(${PROJECT_NAME}
	PUBLIC
		# Default to hiding everything. Sometimes results in smaller binaries
		"-fvisibility=hidden"
)

# Always do this last, it's order dependent unfortunately.
generate_compile_commands_json(TARGETS ${PROJECT_NAME})
clang_tidy(TARGETS ${PROJECT_NAME} VERSION 15.0.0)
clang_format(TARGETS ${PROJECT_NAME} VERSION 15.0.0 DEPENDENCY GLOBAL)
