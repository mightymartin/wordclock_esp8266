#include "logging.h"

WebSocketsServer webSocket(CONF_WEBSOCKET_PORT);

void WebLogInit(){
    webSocket.begin();
}

void WebLogDebug(String msg){
    if(settings.u_LOGGING >= LOGLEVEL_DBG){
        Serial.println(msg); 
        msg = TimeformatedTime() + String(" DBG ") + msg;
        webSocket.broadcastTXT(msg.c_str(),msg.length());
    }
}

void WebLogInfo(String msg){
    if(settings.u_LOGGING >= LOGLEVEL_INF){
        Serial.println(msg); 
        msg = TimeformatedTime() + String(" INF ") + msg;
        webSocket.broadcastTXT(msg.c_str(),msg.length());
    }
}

void WebLogError(String msg){
    if(settings.u_LOGGING >= LOGLEVEL_ERR){
        Serial.println(msg); 
        msg = TimeformatedTime() + String(" ERR ") + msg;
        webSocket.broadcastTXT(msg.c_str(),msg.length());
    }
}

void WebLogTick(){
    webSocket.loop();
}