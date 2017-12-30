#include "inputmanager.h"

#include "clickable.h"
#include "logging.h"
#include "renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>

#include <iostream>

InputManager* gInputManager(nullptr);

void glfw_MouseButtonCallback(GLFWwindow* Window, int button, int action, int mods)
{
  gInputManager->OnMouseButtonPressed(button, action, mods);
}

InputManager::InputManager(GLFWwindow* Window)
{
  LogVerbose("Starting up InputManager");

  if(Window == nullptr)
  {
    Fatal("Invalid window passed to input manager");
    return;
  }

  m_Window = Window;

  glfwSetMouseButtonCallback(m_Window, glfw_MouseButtonCallback);
}

InputManager::~InputManager()
{
  LogVerbose("Shutting down InputManager");
}

void InputManager::RegisterClickable(Clickable* clickable)
{
  if(clickable == nullptr) return;

  m_Clickables.push_back(clickable);
}

void InputManager::UnregisterClickable(Clickable* clickable)
{
  for(unsigned int i = 0; i < m_Clickables.size(); ++i)
  {
    if(m_Clickables[i] == clickable)
    {
      m_Clickables.erase(m_Clickables.begin() + i);
      return;
    }
  }
}

void InputManager::OnMouseButtonPressed(int button, int action, int mods)
{
  double xpos, ypos;
  glfwGetCursorPos(m_Window, &xpos, &ypos);

  int windowSizeX, windowSizeY;
  gRenderer->GetWindowSize(windowSizeX, windowSizeY);

  glm::vec2 worldPos = gRenderer->Deproject(glm::vec2(xpos / (float)windowSizeX, 1.0f - (ypos / (float)windowSizeY)));

  //select the first clickable when contains this world pos
  for(Clickable* clickable : m_Clickables)
  {
    if(clickable->GetClickableArea().Contains(worldPos.x, worldPos.y))
    {
      clickable->OnClicked(worldPos.x, worldPos.y, button, action, mods);
      break;
    }
  }
}
