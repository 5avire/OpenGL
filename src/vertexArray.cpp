#include "vertexArray.h"

#include <glad/glad.h>
#include "vertexBuffer.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
    glBindVertexArray(m_ID);
}

VertexArray::~VertexArray()
{
}

void VertexArray::PushFloat(unsigned int count, unsigned int location)
{
    glBindVertexArray(m_ID);
    glVertexAttribPointer(location, (int)count, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(m_Stride));
    glEnableVertexAttribArray(location);
    m_Stride = m_Stride + (sizeof(float) * count);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_ID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
