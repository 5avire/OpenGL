#pragma once

#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

class Renderer
{
    private:
        unsigned int m_RendererID;
    public:
        Renderer();
        ~Renderer();

        void Clear() const;
        void Draw(Shader& shader, const VertexArray& va, const IndexBuffer& ib) const;
};
