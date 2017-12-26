#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <glm.hpp>

class Renderable;

class Renderer
{
public:

  Renderer(int windowSizeX = 640, int windowSizeY = 480);
  virtual ~Renderer();

  void Update();

  void AddRenderable(Renderable* renderable);
  void RemoveRenderable(Renderable* renderable);

private:

  class GLFWwindow* m_Window = nullptr;

  class ShaderManager* m_ShaderManager = nullptr;

  class ShaderProgram* m_CurShader = nullptr;

  glm::mat4 m_ProjectionMatrix;

  int m_WindowSizeX;
  int m_WindowSizeY;

  std::vector<Renderable*> renderables;
};

#endif
