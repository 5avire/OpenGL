#pragma once

#include <vector>

struct Vertex {
    float x, y, z;
    float r, g, b, a;
    float tx, ty;
};

class VertexBuffer 
{
    private:
        unsigned int m_ID;
    public:

        VertexBuffer(const std::vector<Vertex>& vertices);
        ~VertexBuffer();

        unsigned int GetID();
        void Bind() const;
        void Unbind() const;

};
