#include "shadermanager.h"

#include "core/paths.h"
#include "core/logging.h"

#include <iostream>
#include <cstring>

void ShaderManager::CompileAllShaders()
{
  int vertexShader = CompileShader("vertex.glsl", GL_VERTEX_SHADER);
  int fragShader = CompileShader("frag.glsl", GL_FRAGMENT_SHADER);

  shaderPrograms[Shader::STD] = glCreateProgram();
  glAttachShader(shaderPrograms[Shader::STD], vertexShader);
  glAttachShader(shaderPrograms[Shader::STD], fragShader);
  glLinkProgram(shaderPrograms[Shader::STD]);

  int success;
  glGetProgramiv(shaderPrograms[Shader::STD], GL_LINK_STATUS, &success);
  if(!success)
  {
    char infoLog[512];
    glGetProgramInfoLog(shaderPrograms[Shader::STD], 512, NULL, infoLog);

    Fatal("Failed to link shader program");
    std::cout << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);
}

int ShaderManager::GetShaderProgram(Shader program) const
{
  if(program == Shader::MAX)
  {
    return -1;
  }

  return shaderPrograms[(int)program];
}

int ShaderManager::CompileShader(const char* shaderFileName, GLenum ShaderType)
{
  static char filepath[100];
  filepath[0] = '\0';

  std::strcat(filepath, Paths::ShaderPath);
  std::strcat(filepath, "/");
  std::strcat(filepath, shaderFileName);

  FILE* fp = fopen(filepath, "r");

  sprintf(filepath,"Compiling %s...",  shaderFileName);
  LogVerbose(filepath);

  if(fp == nullptr)
  {
    Fatal("Failed to open shader file");
    return -1;
  }

  fseek(fp, 0, SEEK_END);
  long filesize = ftell(fp);

  fseek(fp, 0, SEEK_SET);
  char* filebuffer = (char*)malloc(filesize + 1);
  filebuffer[filesize] = '\0';

  fread(filebuffer, filesize, 1, fp);

  fclose(fp);

  int shader = glCreateShader(ShaderType);
  glShaderSource(shader, 1, &filebuffer, NULL);
  glCompileShader(shader);

  // check for errors
  int  success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  free(filebuffer);

  if(!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, infoLog);

    Fatal("Shader Compilation Failed");
    std::cout << infoLog << std::endl;

    return -1;
  }

  return shader;
}
