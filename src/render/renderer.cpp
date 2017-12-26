#include "renderer.h"

#include "logging.h"
#include "shadermanager.h"
#include "shaderprogram.h"
#include "renderable.h"
#include "sprite.h"
#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <memory>

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

  //camera location
  float aspectRatio = (float)m_WindowSizeY / (float)m_WindowSizeX;
  m_ProjectionMatrix = glm::ortho(0.0f, 200.0f, 0.0f, 200.0f * aspectRatio, -1.0f, 100.0f);

  // DEBUG
  Sprite* sprite = new Sprite;
  sprite->UpdateBuffers();
  sprite->SetAtlasTexture(std::make_shared<Texture>(new Texture("playingCards.png")), 1, 1);

  sprite->transform.SetPosition(glm::vec3(50.0f, 50.0f, 0.0f));
  sprite->transform.SetScale(glm::vec3(14.0f, 19.0f, 10.0f));

  AddRenderable(sprite);
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

  for(Renderable* renderable : renderables)
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
