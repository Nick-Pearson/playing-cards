#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

#include <glm.hpp>

class ShaderProgram
{

public:

  ShaderProgram(unsigned int vertexShader, unsigned int fragShader);
  virtual ~ShaderProgram() {}

  inline unsigned int GetID() const { return m_ID; }


  void SetBool(const std::string &name, bool value) const;
  void SetInt(const std::string &name, int value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetVector(const std::string &name, const glm::ivec4& value) const;
  void SetMatrix(const std::string &name, const glm::mat4& value) const;

private:

  unsigned int m_ID = 0;
};

#endif
