#pragma once

#include <cstddef>
#include <glm/glm.hpp>

#include "mesh.h"

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
