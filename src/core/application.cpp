#include "application.h"

Application* app;

void Application::RequestClose()
{
  m_ShouldBeClosed = true;
}
