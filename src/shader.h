#pragma once

#include <string>
#include <unordered_map>


struct ShaderProgSource
{
    std::string VertexSource;
    std::string FragmentSource;
};


class Shader
{
private:
  std::string m_FilePath;
  unsigned int m_RendererID;
  std::unordered_map<std::string, unsigned int> m_UniformLocationCache;
public:
  Shader(const std::string& filePath);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  // Set Uniforms and blah
  void setUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
private:
  unsigned int getUniformLocation(const std::string& name);

  unsigned int compileShader(unsigned int type, const std::string& source);
  unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
  ShaderProgSource parseShader(const std::string& filePath);
};
