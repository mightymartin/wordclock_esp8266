#ifndef LOGGING_H
#define LOGGING_H

#define LOGLEVEL_OFF    0
#define LOGLEVEL_ERR    1
#define LOGLEVEL_INF    2
#define LOGLEVEL_DBG    3

#include "settings.h"

extern void LogDebug(String msg);

extern void LogInfo(String msg);

extern void LogError(String msg);

#endif