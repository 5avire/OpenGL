#include "vertexBuffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const Vertex vertices[], size_t noOfData)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, noOfData ,vertices, GL_DYNAMIC_DRAW);
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
