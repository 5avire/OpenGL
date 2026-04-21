#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
    private:
        unsigned int m_ID;
    private:
        mutable std::unordered_map<std::string, int> m_uniformLocationCache;
        int getUniformLocation(const std::string &name) const;
    public:
        Shader(const char* vertexPath,const char* fragmentPath);
        ~Shader();

        void use();

        unsigned int GetID();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFlaot(const std::string &name, float value) const;
        void setMatrix4f(const std::string &name, glm::mat4 &matrix) const;
};
