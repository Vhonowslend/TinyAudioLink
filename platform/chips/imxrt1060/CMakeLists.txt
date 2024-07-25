project(NXP_IMXRT1060
	LANGUAGES C CXX ASM
)
list(POP_BACK CMAKE_MESSAGE_INDENT)
list(APPEND CMAKE_MESSAGE_INDENT "[NXP IMXRT1060]" " ")
message(STATUS "${PROJECT_NAME}")

add_library(${PROJECT_NAME} OBJECT)
add_library(NXP::IMXRT1060 ALIAS ${PROJECT_NAME})
configure(${PROJECT_NAME})
link(${PROJECT_NAME} "ARM::Cortex_M7")

file(GLOB_RECURSE _INCLUDE FOLLOW_SYMLINKS CONFIGURE_DEPENDS "include/*")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Public" FILES ${_INCLUDE})
file(GLOB_RECURSE _SOURCE FOLLOW_SYMLINKS CONFIGURE_DEPENDS "source/*")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/source" PREFIX "Private" FILES ${_SOURCE})
target_sources(${PROJECT_NAME}
	PRIVATE ${_SOURCE}
	PUBLIC ${_INCLUDE}
)
target_include_directories(${PROJECT_NAME}
	PRIVATE "source"
	PUBLIC "include"
)
target_link_libraries(${PROJECT_NAME}
	PRIVATE
		"m" # C Math
		"c++" # C++ Stuff
)
target_compile_options(${PROJECT_NAME}
	PUBLIC
		# C++: Omit thread safety guarantees, as IMXRT1060 is entirely single core.
		"$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>"
)
target_sources(${PROJECT_NAME} INTERFACE $<TARGET_OBJECTS:${PROJECT_NAME}>)

# Always do this last, it's order dependent unfortunately.
generate_compile_commands_json(TARGETS ${PROJECT_NAME})
clang_tidy(TARGETS ${PROJECT_NAME} VERSION 15.0.0)
clang_format(TARGETS ${PROJECT_NAME} VERSION 15.0.0 DEPENDENCY GLOBAL)
