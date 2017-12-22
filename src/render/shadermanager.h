#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum Shader
{
  STD,
  ATLAS,

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

  int LinkProgram(int vertexShader, int fragShader);

  int CompileShader(const char* shaderFileName, GLenum ShaderType);

  int shaderPrograms[(int)Shader::MAX];
};

#endif
