#ifndef LOGGING_H
#define LOGGING_H

#define LOGLEVEL_OFF    0
#define LOGLEVEL_ERR    1
#define LOGLEVEL_INF    2
#define LOGLEVEL_DBG    3

#include "settings.h"
#include "timeNTP.h"
#include <WebSocketsServer.h>

extern void WebLogInit();

extern void WebLogDebug(String msg);

extern void WebLogInfo(String msg);

extern void WebLogError(String msg);

extern void WebLogTick();

#endif