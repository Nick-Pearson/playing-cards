#include "logging.h"

#include <iostream>
#include <time.h>

namespace
{
  char buff[11];
};

void Logging::Log_Internal(const char* Message)
{
  time_t time_raw;
  time(&time_raw);

  strftime(buff, 11, "[%T] ", localtime(&time_raw));
  std::cout << buff << Message << std::endl;
}
