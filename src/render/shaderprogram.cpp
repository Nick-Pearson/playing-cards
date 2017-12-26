#include "shaderprogram.h"

#include "logging.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gtc/type_ptr.hpp>

#include <iostream>

ShaderProgram::ShaderProgram(unsigned int vertexShader, unsigned int fragShader)
{
  m_ID = glCreateProgram();
  glAttachShader(m_ID, vertexShader);
  glAttachShader(m_ID, fragShader);
  glLinkProgram(m_ID);

  int success;
  glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
  if(!success)
  {
    char infoLog[512];
    glGetProgramInfoLog(m_ID, 512, NULL, infoLog);

    Fatal("Failed to link shader program");
    std::cout << infoLog << std::endl;
  }
}

void ShaderProgram::SetBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void ShaderProgram::SetInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void ShaderProgram::SetFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void ShaderProgram::SetMatrix(const std::string &name, const glm::mat4& value) const
{
  glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
