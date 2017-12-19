#include <iostream>

#include "core/application.h"
#include "render/renderer.h"

int main(int argc, char** argv)
{
  app = new Application;
  Renderer* renderer = new Renderer;

  while(!app->ShouldBeClosed())
  {
    renderer->Update();
  }

  delete renderer;
  delete app;

  return 0;
}
