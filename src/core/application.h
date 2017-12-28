#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

extern class Application* gApp;

class GameObject;

class Application
{
public:
  Application();
  virtual ~Application();

  inline bool ShouldBeClosed() { return m_ShouldBeClosed; }

  void RequestClose();

  void PerformGameLoop();

  void AddToWorld(GameObject* obj);
  void RemoveFromWorld(GameObject* obj);

private:

  static Application* instance;

  long getTimestamp() const;

private:

  bool m_ShouldBeClosed = false;

  std::vector<GameObject*> m_GameObjects;

  class Renderer* m_Renderer;
};

#endif
