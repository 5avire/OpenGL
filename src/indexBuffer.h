#pragma once

#include <vector>

class IndexBuffer
{
    private:
        unsigned int m_ID;
        unsigned int m_Count;
    public:
        IndexBuffer(const std::vector<unsigned int>& indices);
        ~IndexBuffer();

        unsigned int GetID();
        unsigned int GetCount();
        void Bind() const;
        void Unbind() const;
};
