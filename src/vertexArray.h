#pragma once

#include <cstdint>

class VertexArray
{
    private:
        unsigned int m_ID;
        uintptr_t m_Stride = 0;
    public:
        VertexArray();
        ~VertexArray();

        void PushFloat(unsigned int count, unsigned int location);
        void Bind() const;
        void Unbind() const;
};
