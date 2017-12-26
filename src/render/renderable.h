#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "shadermanager.h"
#include "transform.h"

#include <glm.hpp>

#include <vector>
#include <memory>

class Texture;

class Renderable
{

public:

  Renderable() {}
  virtual ~Renderable() {}

  // force the mesh buffer to update
  void UpdateBuffers();

  int GetVAO() const { return m_VAO; }
  ShaderType GetShader() const { return m_Shader; }
  Texture* GetTexture() const { return m_Texture.get(); }

  void SetTexture(const std::shared_ptr<Texture>& texture);
  void SetAtlasTexture(const std::shared_ptr<Texture>& texture, int tileX, int tileY);

  Transform transform;

protected:

  // returns the mesh data for this object
  virtual void GetMeshData(std::vector<float>& outVerticies, std::vector<unsigned int>& outIndicies) const = 0;

private:

  std::shared_ptr<Texture> m_Texture;
  int m_TileX = -1;
  int m_TileY = -1;

  void GenerateBuffers();

  unsigned int m_VAO = -1;
  unsigned int m_VBO = -1;
  unsigned int m_EBO = -1;
  bool m_IsValid = false;

  ShaderType m_Shader = ShaderType::STD;
};

#endif
