#include "shadermanager.h"

#include "paths.h"
#include "logging.h"
#include "shaderprogram.h"

#include <iostream>
#include <cstring>

ShaderManager::ShaderManager()
{
  LogVerbose("Starting up ShaderManager");
}

ShaderManager::~ShaderManager()
{
  LogVerbose("Shutting down ShaderManager");

  for(int i = 0; i < (int)ShaderType::MAX; ++i)
    delete shaderPrograms[i];
}

void ShaderManager::CompileAllShaders()
{
  unsigned int vertexShader = CompileShader("vertex.glsl", GL_VERTEX_SHADER);
  unsigned int fragAtlasShader = CompileShader("frag_atlas.glsl", GL_FRAGMENT_SHADER);
  unsigned int fragDefaultShader = CompileShader("frag_default.glsl", GL_FRAGMENT_SHADER);

  shaderPrograms[ShaderType::STD] = new ShaderProgram(vertexShader, fragDefaultShader);
  shaderPrograms[ShaderType::ATLAS] = new ShaderProgram(vertexShader, fragAtlasShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragAtlasShader);
  glDeleteShader(fragDefaultShader);
}

ShaderProgram* ShaderManager::GetShaderProgram(ShaderType program) const
{
  if(program == ShaderType::MAX)
  {
    return nullptr;
  }

  return shaderPrograms[(int)program];
}

unsigned int ShaderManager::GetShaderProgramID(ShaderType program) const
{
  if(ShaderProgram* shader = GetShaderProgram(program))
    return shader->GetID();

  return 0;
}

unsigned int ShaderManager::CompileShader(const std::string& shaderFileName, GLenum ShaderType)
{
  std::string filepath = shaderFileName;

  filepath.insert(0, "/");
  filepath.insert(0, Paths::ShaderPath);

  FILE* fp = fopen(filepath.c_str(), "r");

  filepath.append("...");
  filepath.insert(0, "Compiling ");
  LogVerbose(filepath.c_str());

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

  unsigned int shader = glCreateShader(ShaderType);
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
