#include "renderer.h"

#include "logging.h"
#include "shadermanager.h"
#include "shaderprogram.h"
#include "renderable.h"
#include "texture.h"
#include "texturemanager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <memory>

Renderer* gRenderer(nullptr);

void glfw_FramebufferChangedCallback(GLFWwindow* window, int width, int height)
{
  if(gRenderer) gRenderer->OnWindowSizeChanged(width, height);
}

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

  m_GameAreaSizeX = 200.0f;
  m_GameAreaSizeY = 100.0f;

  glfwSetFramebufferSizeCallback(m_Window, glfw_FramebufferChangedCallback);
  OnWindowSizeChanged(windowSizeX, windowSizeY);

  glClearColor(0.01f, 0.20f, 0.04f, 1.0f);

  // compile shaders
  m_ShaderManager = new ShaderManager;
  m_ShaderManager->CompileAllShaders();

  //texture manager
  gTextureManager = new TextureManager;
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

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for(auto& renderable : renderables)
  {
    //shader
    ShaderProgram* shaderptr = m_ShaderManager->GetShaderProgram(renderable->GetShader());
    if(m_CurShader != shaderptr)
    {
      glUseProgram(shaderptr ? shaderptr->GetID() : 0);

      if(shaderptr)
      {
        shaderptr->SetMatrix("projection", m_ProjectionMatrix);
      }

      m_CurShader = shaderptr;
    }

    // apply texture if applicable
    glActiveTexture(GL_TEXTURE0);
    if(Texture* tex = renderable->GetTexture())
    {
      glBindTexture(GL_TEXTURE_2D, tex->GetTextureID());
    }
    else
    {
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    shaderptr->SetVector("tileCoords", renderable->GetTileCoords());

    //apply the model transform
    if(m_CurShader)
    {
      m_CurShader->SetMatrix("model", renderable->transform.GetMatrix());
    }

    //apply verticies and draw
    glBindVertexArray(renderable->GetVAO());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  glfwPollEvents();
  glfwSwapBuffers(m_Window);

  if(glfwWindowShouldClose(m_Window))
  {
    gApp->RequestClose();
  }
}

void Renderer::AddRenderable(std::shared_ptr<Renderable> renderable)
{
  if(renderable.get() == nullptr)
  {
    Error("Attempted to add nullptr renderable");
    return;
  }

  renderables.push_back(renderable);
}

void Renderer::RemoveRenderable(std::shared_ptr<Renderable> renderable)
{
  if(renderable.get() == nullptr)
  {
    Error("Attempted to add nullptr renderable");
    return;
  }

  //TODO remove swap
}

void Renderer::SetGameAreaSize(float minSizeX, float minSizeY)
{
  m_GameAreaSizeX = minSizeX;
  m_GameAreaSizeY = minSizeY;

  float reqAspectRatio = minSizeY / minSizeX;
  float aspectRatio = (float)m_WindowSizeY / (float)m_WindowSizeX;

  if(reqAspectRatio > aspectRatio)
  {
    float sizeX = minSizeY / aspectRatio;
    float Xoffset = (sizeX - minSizeX) * 0.5f;

    m_ProjectionMatrix = glm::ortho(-Xoffset, minSizeX + Xoffset, 0.0f, minSizeY, -1.0f, 100.0f);
  }
  else
  {
    float sizeY = minSizeX * aspectRatio;
    float Yoffset = (sizeY - minSizeY) * 0.5f;

    m_ProjectionMatrix = glm::ortho(0.0f, minSizeX, -Yoffset, minSizeY + Yoffset, -1.0f, 100.0f);
  }

  if(m_CurShader != nullptr)
  {
    m_CurShader->SetMatrix("projection", m_ProjectionMatrix);
  }
}

void Renderer::OnWindowSizeChanged(int width, int height)
{
  m_WindowSizeX = width;
  m_WindowSizeY = height;

  glViewport(0, 0, width, height);
  SetGameAreaSize(m_GameAreaSizeX, m_GameAreaSizeY);
}
