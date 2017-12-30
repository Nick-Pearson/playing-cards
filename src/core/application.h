#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

extern class Application* gApp;

class Application
{
public:
  Application();
  virtual ~Application();

  inline bool ShouldBeClosed() { return m_ShouldBeClosed; }

  void RequestClose();

  void PerformGameLoop();

private:

  static Application* instance;

  long getTimestamp() const;

private:

  bool m_ShouldBeClosed = false;
};

#endif
