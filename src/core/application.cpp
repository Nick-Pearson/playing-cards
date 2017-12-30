#include "application.h"

#include <unistd.h>
#include <time.h>
#include <math.h>

#include "renderer.h"
#include "logging.h"
#include "solitairegame.h"

Application* gApp(nullptr);

Application::Application()
{
  if(gApp != nullptr)
  {
    Fatal("Multiple application objects have been created");
  }
}

Application::~Application()
{
  {
    Renderer* renderer = gRenderer;
    gRenderer = nullptr;
    delete renderer;
  }
}

void Application::RequestClose()
{
  m_ShouldBeClosed = true;
}

#define TARGET_FRAMERATE 30

void Application::PerformGameLoop()
{
  gRenderer = new Renderer;

  SolitaireGame* game = new SolitaireGame;
  game->Initialise();

  long targetFrameDuration = floor(1000000.0 / TARGET_FRAMERATE);

  while(!ShouldBeClosed())
  {
    long frameStart = getTimestamp();

    //frame work
    gRenderer->Update();

    //frame rate governing
    long frameEnd = getTimestamp();
    long sleepTime = targetFrameDuration - (frameEnd - frameStart);

    if(sleepTime > 0)
    {
      usleep(sleepTime);
    }
  }
}

long Application::getTimestamp() const
{
  timespec spec;
  clock_gettime(CLOCK_REALTIME, &spec);
  return (1000000 * spec.tv_sec) + round(spec.tv_nsec / 1.0e3);
}
