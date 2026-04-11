#pragma once

#include <string>

class Texture2D
{
    private:
        unsigned int m_TextureID;
        unsigned int m_Type;
        unsigned int m_Location;
        unsigned char* m_Data;
        int m_Width, m_Height, m_nrChannels;
    public:
        Texture2D(const std::string texPath, const unsigned int type, const unsigned int texLocation);
        ~Texture2D();

        void Bind() const;
};
