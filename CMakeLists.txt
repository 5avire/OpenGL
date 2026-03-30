cmake_minimum_required(VERSION 3.16)
project(theChernoGL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw-3.4)

add_library(glew STATIC vendor/glew-2.3.1/src/glew.c)
target_include_directories(glew PUBLIC vendor/glew-2.3.1/include)
target_compile_definitions(glew PUBLIC GLEW_STATIC)
target_link_libraries(glew PUBLIC OpenGL::GL)

file(GLOB SRC_FILES src/*.cpp)
add_executable(theChernoGL ${SRC_FILES})
target_include_directories(theChernoGL PRIVATE src)
target_link_libraries(theChernoGL PRIVATE glfw glew)

add_custom_target(copy-compile-commands ALL
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
)
