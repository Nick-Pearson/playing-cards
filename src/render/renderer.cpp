#include "renderer.h"

#include "logging.h"
#include "shadermanager.h"

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

  // compile shaders
  m_ShaderManager = new ShaderManager;
  m_ShaderManager->CompileAllShaders();

  //DEBUG
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  // 2. copy our vertices array in a buffer for OpenGL to use
  float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
  };
  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  };

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  // 3. then set our vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
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

  glUseProgram(m_ShaderManager->GetShaderProgram(Shader::STD));
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glfwPollEvents();
  glfwSwapBuffers(m_Window);

  if(glfwWindowShouldClose(m_Window))
  {
    app->RequestClose();
  }
}
