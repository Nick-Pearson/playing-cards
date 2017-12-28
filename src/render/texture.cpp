#include "texture.h"

#include "paths.h"
#include "logging.h"

#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& filepath)
{
  std::string path = filepath;
  path.insert(0, "/");
  path.insert(0, Paths::TexturePath);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

  if(data == nullptr)
  {
    Error(path.c_str());
    Fatal("Failed to load texture");
    return;
  }

  glGenTextures(1, &m_TID);
  glBindTexture(GL_TEXTURE_2D, m_TID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

Texture::Texture(Texture* other)
{
  if(other) m_TID = other->GetTextureID();
}


Texture::~Texture()
{
  glDeleteTextures(1, &m_TID);
}
