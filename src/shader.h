#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Shader
{
private:
    mutable std::unordered_map<std::string, int> m_uniformLocationCache;

    unsigned int m_ID;
    int getUniformLocation(const std::string &name) const;
public:
    Shader(const char* vertexPath,const char* fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFlaot(const std::string &name, float value) const;
};
