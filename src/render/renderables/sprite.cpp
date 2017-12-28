#include "sprite.h"

void Sprite::GetMeshData(std::vector<float>& outVerticies, std::vector<unsigned int>& outIndicies) const
{
  outVerticies = {
    // vertex co-ords    tex co-ords
     1.0f,  1.0f, 0.0f,  1.0f, 0.0f, // top right
     1.0f, -1.0f, 0.0f,  1.0f, 1.0f, // bottom right
    -1.0f, -1.0f, 0.0f,  0.0f, 1.0f, // bottom left
    -1.0f,  1.0f, 0.0f,  0.0f, 0.0f // top left
  };

  outIndicies = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  };
}
