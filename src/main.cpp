#include "application.h"

//returns current time in microseconds
long get_timestamp();

int main(int argc, char** argv)
{
  app = new Application;

  app->PerformGameLoop();

  delete app;

  return 0;
}
