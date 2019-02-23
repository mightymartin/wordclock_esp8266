#include "logging.h"

void LogDebug(String msg){
    if(settings.u_LOGGING >= LOGLEVEL_DBG){
        Serial.println(msg); 
    }
}

void LogInfo(String msg){
    if(settings.u_LOGGING >= LOGLEVEL_INF){
        Serial.println(msg); 
    }
}

void LogError(String msg){
    if(settings.u_LOGGING >= LOGLEVEL_ERR){
        Serial.println(msg); 
    }
}
