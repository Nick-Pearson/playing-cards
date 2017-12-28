#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class ShaderProgram;

enum ShaderType
{
  STD,
  ATLAS,

  MAX
};

class ShaderManager
{
public:
  ShaderManager() {}
  virtual ~ShaderManager();

  void CompileAllShaders();

  ShaderProgram* GetShaderProgram(ShaderType program) const;
  unsigned int GetShaderProgramID(ShaderType program) const;

private:

  unsigned int CompileShader(const std::string& shaderFileName, GLenum ShaderType);

  ShaderProgram* shaderPrograms[(int)ShaderType::MAX];
};

#endif
