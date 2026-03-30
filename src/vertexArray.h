#pragma once

#include "vertexBuffer.h"

class vertexBufferLayout;

#include "vertexBuffer.h"
class vertexArray
{
private:
  unsigned int m_RendererID;
public:
  vertexArray();
  ~vertexArray();
  
  void bufferAdd(const vertexBuffer& vb, const vertexBufferLayout& layout);

  void Bind() const;
  void Unbind() const;
};
