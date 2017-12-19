#include "renderer.h"
#include "logging.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Renderer::Renderer(int windowSizeX /*= 640*/, int windowSizeY /*= 480*/) :
  m_WindowSizeX(windowSizeX), m_WindowSizeY(windowSizeY)
{
  LogVerbose("Starting up renderer");

  // Initialise GLFW
  if(!glfwInit())
  {
    Fatal("Failed to initialse GLFW");
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create the game window
  m_Window = glfwCreateWindow(m_WindowSizeX, m_WindowSizeY, "Playing Cards", NULL, NULL);
  if(!m_Window)
  {
    Fatal("Failed to create GLFW window");
    return;
  }

  glfwMakeContextCurrent(m_Window);

  // Initialise GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    Fatal("Failed to initialse GLAD");
    return;
  }

  glViewport(0, 0, m_WindowSizeX, m_WindowSizeY);
}

Renderer::~Renderer()
{
  LogVerbose("Shutting down renderer");

  glfwTerminate();
}

void Renderer::Update()
{
  LogVerbose("Frame update");

  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(m_Window);

  glfwPollEvents();

  if(glfwWindowShouldClose(m_Window))
  {
    app->RequestClose();
  }
}
