cmake_minimum_required(VERSION 3.16)
project(theChernoGL)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(include/glfw-3.4)

add_library(glew STATIC include/glew-2.3.1/src/glew.c)
target_include_directories(glew PUBLIC include/glew-2.3.1/include)
target_compile_definitions(glew PUBLIC GLEW_STATIC)
target_link_libraries(glew PUBLIC OpenGL::GL)

add_library(imgui STATIC
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imgui_impl_glfw.cpp
    vendor/imgui/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC vendor/imgui)
target_link_libraries(imgui PUBLIC glfw glew)

add_library(stb_image STATIC vendor/stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC vendor/stb_image)

file(GLOB SRC_FILES src/*.cpp)
file(GLOB TEST_FILES src/tests/*.cpp)
add_executable(theChernoGL ${SRC_FILES} ${TEST_FILES})
set_target_properties(theChernoGL PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_include_directories(theChernoGL PRIVATE vendor/glm)
target_include_directories(theChernoGL PRIVATE src)
target_include_directories(theChernoGL PRIVATE src/tests)
target_link_libraries(theChernoGL PRIVATE glfw glew stb_image imgui)

add_custom_target(copy-compile-commands ALL
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
)
