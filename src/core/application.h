#ifndef APPLICATION_H
#define APPLICATION_H

extern class Application* app;

class Application
{
public:

  inline bool ShouldBeClosed() { return m_ShouldBeClosed; }

  void RequestClose();

private:

  bool m_ShouldBeClosed = false;
};

#endif
