#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Window {
    GLFWwindow* Init(int width, int height, const char* title);
    void processInput(GLFWwindow* window);
}
