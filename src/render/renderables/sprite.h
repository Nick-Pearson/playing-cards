#ifndef SPRITE_H
#define SPRITE_H

#include "renderable.h"

class Sprite : public Renderable
{
public:
  Sprite() {}
  Sprite(const Sprite* other) : Renderable(other) {}

protected:
  virtual void GetMeshData(std::vector<float>& outVerticies, std::vector<unsigned int>& outIndicies) const override;
};

#endif
