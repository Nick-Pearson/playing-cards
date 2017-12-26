#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
  //construct a texture from filepath (relative to the resources directory)
  Texture(const char* filepath);

  //copy constructor
  Texture(Texture* other);

  virtual ~Texture();

  unsigned int GetTextureID() const { return m_TID; }

private:
  unsigned int m_TID;
};

#endif
