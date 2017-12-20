#ifndef SQUARE_H
#define SQUARE_H

#include "../renderable.h"

class Square : public Renderable
{
  virtual void GetMeshData(std::vector<float>& outVerticies, std::vector<unsigned int>& outIndicies) const override;
};

#endif
