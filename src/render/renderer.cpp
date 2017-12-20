#include "renderer.h"

#include "logging.h"
#include "shadermanager.h"

#include "renderable.h"
#include "renderables/square.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

  // compile shaders
  m_ShaderManager = new ShaderManager;
  m_ShaderManager->CompileAllShaders();

  // DEBUG
  Square* square = new Square;
  square->UpdateBuffers();
  AddRenderable(square);
}

Renderer::~Renderer()
{
  LogVerbose("Shutting down renderer");

  delete m_ShaderManager;

  glfwTerminate();
}

void Renderer::Update()
{
  glClear(GL_COLOR_BUFFER_BIT);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  for(Renderable* renderable : renderables)
  {
    glUseProgram(m_ShaderManager->GetShaderProgram(Shader::STD));
    glBindVertexArray(renderable->GetVAO());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  glfwPollEvents();
  glfwSwapBuffers(m_Window);

  if(glfwWindowShouldClose(m_Window))
  {
    app->RequestClose();
  }
}

void Renderer::AddRenderable(Renderable* renderable)
{
  if(renderable == nullptr)
  {
    Error("Attempted to add nullptr renderable");
    return;
  }

  renderables.push_back(renderable);
}

void Renderer::RemoveRenderable(Renderable* renderable)
{
  if(renderable == nullptr)
  {
    Error("Attempted to add nullptr renderable");
    return;
  }
}
