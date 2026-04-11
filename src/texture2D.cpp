#include "texture2D.h"

#include <stb_image.h>
#include <glad/glad.h>
#include <iostream>


Texture2D::Texture2D(const std::string texPath, const unsigned int type, const unsigned int texLocation)
    : m_Location(texLocation)
{
    stbi_set_flip_vertically_on_load(true);
    m_Data = stbi_load(texPath.c_str(), &m_Width, &m_Height, &m_nrChannels, 0);
    glGenTextures(1, &m_TextureID);
    glActiveTexture(GL_TEXTURE0 + texLocation);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (m_Data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, type, m_Width, m_Height, 0, type, GL_UNSIGNED_BYTE, m_Data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load Texture\n";
    }
    stbi_image_free(m_Data);
}

Texture2D::~Texture2D()
{

}

void Texture2D::Bind() const
{
    glActiveTexture(GL_TEXTURE0 + m_Location);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}
