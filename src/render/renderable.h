#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "shadermanager.h"
#include "transform.h"

#include <glm.hpp>

#include <vector>
#include <memory>

class Texture;

class Renderable : public std::enable_shared_from_this<Renderable>
{

public:

  Renderable() {}

  Renderable(const Renderable* other);

  virtual ~Renderable();

  template<typename T, typename... Args>
  static std::shared_ptr<T> CreateRenderable(Args... args)
  {
    std::shared_ptr<T> instance = std::make_shared<T>(new T(args...));
    instance->UpdateBuffers();
    instance->SetVisible(true);
    return instance;
  }

  // force the mesh buffer to update
  void UpdateBuffers();

  void SetVisible(bool visible);

  int GetVAO() const { return m_VAO; }
  ShaderType GetShader() const { return m_Shader; }
  Texture* GetTexture() const { return m_Texture.get(); }
  glm::ivec4 GetTileCoords() const { return m_TileCoords; }

  void SetTexture(const std::shared_ptr<Texture>& texture);
  void SetAtlasTexture(const std::shared_ptr<Texture>& texture, const glm::ivec4& tileCoords);

  Transform transform;

protected:

  // returns the mesh data for this object
  virtual void GetMeshData(std::vector<float>& outVerticies, std::vector<unsigned int>& outIndicies) const = 0;

private:

  std::shared_ptr<Texture> m_Texture;
  glm::ivec4 m_TileCoords;

  void GenerateBuffers();

  unsigned int m_VAO = -1;
  unsigned int m_VBO = -1;
  unsigned int m_EBO = -1;
  bool m_IsValid = false;

  bool m_IsVisible = false;

  ShaderType m_Shader = ShaderType::STD;
};

#endif
