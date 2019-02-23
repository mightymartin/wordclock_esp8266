#ifndef LOGGING_H
#define LOGGING_H

#define LOGLEVEL_OFF    0
#define LOGLEVEL_ERR    1
#define LOGLEVEL_INF    2
#define LOGLEVEL_DBG    3

#include "settings.h"

inline void LogDebug(String msg){
    if(settings.u_LOGGING >= LOGLEVEL_DBG){
        Serial.println(msg); 
    }
}

inline void LogInfo(String msg){
    if(settings.u_LOGGING >= LOGLEVEL_INF){
        Serial.println(msg); 
    }
}

inline void LogError(String msg){
    if(settings.u_LOGGING >= LOGLEVEL_ERR){
        Serial.println(msg); 
    }
}

#endif