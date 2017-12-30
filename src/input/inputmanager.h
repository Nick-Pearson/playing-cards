#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>

extern class InputManager* gInputManager;

class GLFWwindow;
class Clickable;

class InputManager
{
public:
  InputManager(GLFWwindow* Window);
  virtual ~InputManager();

  void RegisterClickable(Clickable* clickable);
  void UnregisterClickable(Clickable* clickable);

  void OnMouseButtonPressed(int button, int action, int mods);

private:

  GLFWwindow* m_Window;

  std::vector<Clickable*> m_Clickables;
};

#endif
