#pragma once


#include <vector>
#include <GL/glew.h>
#include "renderer.h"


struct vertexBufferElement
{
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int GetSizeOfType(unsigned int type)
  {
    switch (type)
    {
      case GL_FLOAT: return 4;
      case GL_UNSIGNED_INT: return 4;
      case GL_UNSIGNED_BYTE: return 1;
    }
    ASSERT(false);
    return 0;
  }
};


class vertexBufferLayout
{
private:
  std::vector<vertexBufferElement> m_Elements;
  unsigned int m_Stride;
public:
  vertexBufferLayout()
    : m_Stride(0) {}

  template<typename T>
  void push(unsigned int count)
  {
    static_assert(sizeof(T) == 0, "Unsupported type");
  }

  inline const std::vector<vertexBufferElement> getElements() const { return m_Elements; };
  inline unsigned int getStride() const { return m_Stride; };
};

template<>
inline void vertexBufferLayout::push<float>(unsigned int count)
{
  m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
  m_Stride += count * vertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
inline void vertexBufferLayout::push<unsigned int>(unsigned int count)
{
  m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_Stride += count * vertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
inline void vertexBufferLayout::push<unsigned char>(unsigned int count)
{
  m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
  m_Stride += count * vertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
