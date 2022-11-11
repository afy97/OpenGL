cmake_minimum_required(VERSION 3.20)

project("OpenGL_Demo")

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(cglm CONFIG REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.cc" "${SRC_DIR}/*.c")
file(GLOB_RECURSE INC_FILES "${INC_DIR}/*.hpp" "${INC_DIR}/*.hh" "${INC_DIR}/*.h")

include_directories(${INC_DIR})

add_executable(${PROJECT_NAME} ${SRC_FILES} ${INC_FILES})

target_link_libraries(
${PROJECT_NAME}
	PRIVATE
        OpenGL::GL
		glfw
        GLEW::GLEW
        cglm::cglm
)

target_precompile_headers(
${PROJECT_NAME}
    PRIVATE
        "${INC_DIR}/pch.h"
)

add_compile_options(/permissive-)
