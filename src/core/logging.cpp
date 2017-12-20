#include "logging.h"

#include <iostream>
#include <time.h>

namespace
{
  char buff[11];
};

void Logging::Log_Internal(const char* Message, const char* Colour /*= ANSI_COLOR_RESET*/)
{
  time_t time_raw;
  time(&time_raw);

  strftime(buff, 11, "[%T] ", localtime(&time_raw));
  printf("%s %s%s%s\n", buff, Colour, Message, ANSI_COLOR_RESET);
}
