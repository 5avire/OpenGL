#include "vertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
}

unsigned int VertexBuffer::GetID()
{
    return m_ID;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
