#include "indexBuffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
}

unsigned int IndexBuffer::GetID()
{
    return m_ID;
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
