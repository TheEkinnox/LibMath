
# set target
get_filename_component(CURRENT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(TARGET_NAME ${CURRENT_FOLDER_NAME})


###############################
#                             #
# Sources                     #
#                             #
###############################

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc # C with classes
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

# Add header files
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Header)
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

###############################
#                             #
# Catch2                      #
#                             #
###############################

Include(FetchContent)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v3.8.1
)

set(CATCH_DEVELOPMENT_BUILD OFF)
set(CATCH_INSTALL_DOCS OFF)
set(CATCH_INSTALL_EXTRAS OFF)

FetchContent_MakeAvailable(Catch2)



###############################
#                             #
# GLM                         #
#                             #
###############################

FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG        1.0.1
)

set(GLM_BUILD_TESTS OFF)
set(GLM_TEST_ENABLE OFF)

FetchContent_MakeAvailable(glm)


###############################
#                             #
# Executable                  #
#                             #
###############################

add_executable(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${TARGET_NAME}
	PRIVATE ${TARGET_INCLUDE_DIR} ${LIBMATH_INCLUDE_DIR}
)

target_include_directories(${TARGET_NAME} SYSTEM PRIVATE ${glm_SOURCE_DIR})

target_link_libraries(${TARGET_NAME}
	PRIVATE ${LIBMATH_NAME} Catch2::Catch2
)

if(MSVC)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
	target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Setup ctest
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(${TARGET_NAME})