#include "texture.h"

#include "../core/paths.h"
#include "../core/logging.h"

#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* filepath)
{
  int fullpath_len = std::strlen(filepath) + std::strlen(Paths::TexturePath) + 2;
  char full_path[fullpath_len];

  full_path[0] = '\0';
  full_path[fullpath_len - 1] = '\0';

  std::strcat(full_path, Paths::TexturePath);
  std::strcat(full_path, "/");
  std::strcat(full_path, filepath);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(full_path, &width, &height, &nrChannels, 0);

  if(data == nullptr)
  {
    Error(full_path);
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
