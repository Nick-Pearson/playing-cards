#ifndef LOGGING_H
#define LOGGING_H

#include "application.h"

/*
0 - errors only
1 - errors and warnings
2 - errors warnings and messages
3 - all messages
*/
#define LOG_LEVEL 3

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

namespace Logging
{
  void Log_Internal(const char* Message, const char* Colour = ANSI_COLOR_RESET);
};

#define Fatal(Message) \
  Logging::Log_Internal(Message, ANSI_COLOR_RED); \
  app->RequestClose();

#define Error(Message) Logging::Log_Internal(Message, ANSI_COLOR_RED);

#if LOG_LEVEL >= 1
  #define Warn(Message) Logging::Log_Internal(Message, ANSI_COLOR_YELLOW);
#else
  #define Warn(Message)
#endif

#if LOG_LEVEL >= 2
  #define Log(Message) Logging::Log_Internal(Message);
#else
  #define Log(Message)
#endif

#if LOG_LEVEL == 3
  #define LogVerbose(Message) Logging::Log_Internal(Message);
#else
  #define LogVerbose(Message)
#endif

#endif
