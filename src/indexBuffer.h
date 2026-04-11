#pragma once

#include <vector>

class IndexBuffer
{
    private:
        unsigned int m_ID;
    public:
        IndexBuffer(const std::vector<unsigned int>& indices);
        ~IndexBuffer();

        unsigned int GetID();
        void Bind() const;
        void Unbind() const;
};
