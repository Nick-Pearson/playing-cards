#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:

  Renderer(int windowSizeX = 640, int windowSizeY = 480);
  virtual ~Renderer();

  void Update();

private:

  class GLFWwindow* m_Window;

  class ShaderManager* m_ShaderManager;

  int m_WindowSizeX;
  int m_WindowSizeY;

  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
};

#endif
