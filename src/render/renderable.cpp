#include "renderable.h"

#include "logging.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gtc/matrix_transform.hpp>

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

void Renderable::SetTexture(const std::shared_ptr<Texture>& texture)
{
  m_Texture = texture;
  m_TileX = -1;
  m_TileY = -1;

  m_Shader = ShaderType::STD;
}

void Renderable::SetAtlasTexture(const std::shared_ptr<Texture>& texture, int tileX, int tileY)
{
  m_Texture = texture;
  m_TileX = tileX;
  m_TileY = tileY;

  m_Shader = ShaderType::ATLAS;
}
