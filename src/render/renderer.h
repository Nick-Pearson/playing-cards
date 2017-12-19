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

  int m_WindowSizeX;
  int m_WindowSizeY;
};

#endif
