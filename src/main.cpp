#include "application.h"

//returns current time in microseconds
long get_timestamp();

int main(int argc, char** argv)
{
  gApp = new Application;

  gApp->PerformGameLoop();

  delete gApp;

  return 0;
}
