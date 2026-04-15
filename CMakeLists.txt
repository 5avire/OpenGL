cmake_minimum_required(VERSION 3.16)
project(learnGL)

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

add_library(imgui STATIC
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imgui_impl_glfw.cpp
    vendor/imgui/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC vendor/imgui)

add_library(stb_image STATIC vendor/stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC vendor/stb_image)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC include)

file(GLOB SRC_FILES src/*.cpp)
add_executable(learnGL ${SRC_FILES})

set_target_properties(learnGL PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_include_directories(learnGL PRIVATE vendor/glm src)
target_link_libraries(learnGL PRIVATE glfw glad stb_image imgui OpenGL::GL)

add_custom_target(copy-compile-commands ALL
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
)
