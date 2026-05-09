#pragma once

#include <cstddef>

struct Vertex {
    float x, y, z;
    float r, g, b, a;
    float tx, ty;
    float nx, ny, nz;
};

class VertexBuffer 
{
    private:
        unsigned int m_ID;
    public:
        VertexBuffer(const Vertex vertices[], size_t noOfData);
        ~VertexBuffer();

        unsigned int GetID();
        void Bind() const;
        void Unbind() const;
};
