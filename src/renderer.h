#pragma once

#include <GL/glew.h>

#include "indexBuffer.h"
#include "shader.h"
#include "vertexArray.h"

#define ASSERT(x) if (!(x)) __builtin_trap();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(const vertexArray& va, const indexBuffer& ib, const Shader& shader) const;
};
