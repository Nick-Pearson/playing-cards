#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum Shader
{
  STD,

  MAX
};

class ShaderManager
{
public:
  ShaderManager() {}
  virtual ~ShaderManager() {}

  void CompileAllShaders();

  int GetShaderProgram(Shader program) const;

private:

  int CompileShader(const char* shaderFileName, GLenum ShaderType);

  int shaderPrograms[(int)Shader::MAX];
};

#endif
