#include "application.h"

#include <unistd.h>
#include <time.h>
#include <math.h>

#include "../render/renderer.h"
#include "logging.h"

Application* app;

Application::~Application()
{
  delete m_Renderer;
}

void Application::RequestClose()
{
  m_ShouldBeClosed = true;
}

#define TARGET_FRAMERATE 30

void Application::PerformGameLoop()
{
  m_Renderer = new Renderer;

  long targetFrameDuration = floor(1000000.0 / TARGET_FRAMERATE);

  while(!ShouldBeClosed())
  {
    long frameStart = getTimestamp();

    //frame work
    m_Renderer->Update();

    //frame rate governing
    long frameEnd = getTimestamp();
    long sleepTime = targetFrameDuration - (frameEnd - frameStart);

    if(sleepTime > 0)
    {
      usleep(sleepTime);
    }
  }
}

void AddToWorld(GameObject* obj)
{
  if(obj == nullptr)
  {
    Error("Tried to add nullptr object to world");
    return;
  }
}

void RemoveFromWorld(GameObject* obj)
{
  if(obj == nullptr)
  {
    Error("Tried to remove nullptr object from world");
    return;
  }
}

long Application::getTimestamp() const
{
  timespec spec;
  clock_gettime(CLOCK_REALTIME, &spec);
  return (1000000 * spec.tv_sec) + round(spec.tv_nsec / 1.0e3);
}
