#include "renderable.h"

#include "logging.h"
#include "renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gtc/matrix_transform.hpp>

Renderable::Renderable(const Renderable* other)
{
  SetVisible(false);

  transform = other->transform;
  m_Texture = other->m_Texture;
  m_TileCoords = other->m_TileCoords;

  m_VAO = other->m_VAO;
  m_VBO = other->m_VBO;
  m_EBO = other->m_EBO;
  m_IsValid = other->m_IsValid;
  m_Shader = other->m_Shader;

  SetVisible(other->m_IsVisible);
}

Renderable::~Renderable()
{
  SetVisible(false);
}

void Renderable::GenerateBuffers()
{
  if(m_IsValid)
  {
    Error("Attempted to initalise renderable twice");
    return;
  }

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  m_IsValid = true;
}

void Renderable::UpdateBuffers()
{
  if(!m_IsValid)
    GenerateBuffers();

  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  GetMeshData(vertices, indices);

  glBindVertexArray(m_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderable::SetVisible(bool visible)
{
  if(visible == m_IsVisible) return;

  m_IsVisible = visible;

  if(gRenderer)
  {
    if(m_IsVisible)
      gRenderer->AddRenderable(shared_from_this());
    else
      gRenderer->RemoveRenderable(shared_from_this());
  }
}

void Renderable::SetTexture(const std::shared_ptr<Texture>& texture)
{
  m_Texture = texture;

  m_Shader = ShaderType::STD;
}

void Renderable::SetAtlasTexture(const std::shared_ptr<Texture>& texture, const glm::ivec4& tileCoords)
{
  m_Texture = texture;
  m_TileCoords = tileCoords;

  m_Shader = ShaderType::ATLAS;
}
