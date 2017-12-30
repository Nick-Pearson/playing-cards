#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>

#include <glm.hpp>

class Renderable;

extern class Renderer* gRenderer;

class Renderer
{
public:

  Renderer(int windowSizeX = 640, int windowSizeY = 480);
  virtual ~Renderer();

  void Update();

  void AddRenderable(std::shared_ptr<Renderable> renderable);
  void RemoveRenderable(std::shared_ptr<Renderable> renderable);

  void SetGameAreaSize(float minSizeX, float minSizeY);
  void OnWindowSizeChanged(int width, int height);

private:

  class GLFWwindow* m_Window = nullptr;

  class ShaderManager* m_ShaderManager = nullptr;

  class ShaderProgram* m_CurShader = nullptr;

  glm::mat4 m_ProjectionMatrix;

  int m_WindowSizeX;
  int m_WindowSizeY;

  float m_GameAreaSizeX;
  float m_GameAreaSizeY;

  std::vector<std::shared_ptr<Renderable>> renderables;
};

#endif
