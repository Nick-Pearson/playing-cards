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

namespace Logging
{
  void Log_Internal(const char* Message);
};

#define Fatal(Message) \
  Logging::Log_Internal(Message); \
  app->RequestClose();

#define Error(Message) Logging::Log_Internal(Message);

#if LOG_LEVEL >= 1
  #define Warn(Message) Logging::Log_Internal(Message);
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
