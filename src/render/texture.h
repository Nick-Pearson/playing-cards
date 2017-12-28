#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
  //construct a texture from filepath (relative to the resources directory)
  Texture(const std::string& filepath);

  //copy constructor
  Texture(Texture* other);

  virtual ~Texture();

  unsigned int GetTextureID() const { return m_TID; }

private:
  unsigned int m_TID;
};

#endif
