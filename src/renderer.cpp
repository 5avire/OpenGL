#include "renderer.h"


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(Shader& shader, const VertexArray& va, const IndexBuffer& ib) const
{
    shader.use();
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
