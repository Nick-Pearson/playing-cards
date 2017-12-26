#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

  unsigned int CompileShader(const char* shaderFileName, GLenum ShaderType);

  ShaderProgram* shaderPrograms[(int)ShaderType::MAX];
};

#endif
