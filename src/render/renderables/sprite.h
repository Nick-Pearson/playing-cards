#ifndef SPRITE_H
#define SPRITE_H

#include "renderable.h"

class Sprite : public Renderable
{
  virtual void GetMeshData(std::vector<float>& outVerticies, std::vector<unsigned int>& outIndicies) const override;
};

#endif
