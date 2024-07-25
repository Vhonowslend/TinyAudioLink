project(ARM_Cortex_M7
	LANGUAGES C CXX ASM
)
list(POP_BACK CMAKE_MESSAGE_INDENT)
list(APPEND CMAKE_MESSAGE_INDENT "[ARM Cortex M7]" " ")
message(STATUS "${PROJECT_NAME}")

add_library(${PROJECT_NAME} OBJECT)
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
)
target_sources(${PROJECT_NAME} INTERFACE $<TARGET_OBJECTS:${PROJECT_NAME}>)

# Always do this last, it's order dependent unfortunately.
generate_compile_commands_json(TARGETS ${PROJECT_NAME})
clang_tidy(TARGETS ${PROJECT_NAME} VERSION 15.0.0)
clang_format(TARGETS ${PROJECT_NAME} VERSION 15.0.0 DEPENDENCY GLOBAL)
