#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <WiFiManager.h>

#include "leds.h"
#include "color.h"
#include "timeNTP.h"
#include "draw.h"
#include "ldr.h"
#include "settings.h"
#include "website.h"

//##############################
//## Instances
//##############################
ESP8266WebServer server(CONF_WEBSERVER_PORT);
ESP8266WebServer updateServer(CONF_UPDATESERVER_PORT);
ESP8266HTTPUpdateServer httpUpdaterServer;


//##############################
//## Diverses noch in func file!!!!
//##############################
void log_debug(String msg){
  #ifdef CONF_DEBUG
    Serial.println(msg);
  #endif
}

void log(String msg){
  Serial.println(msg);  
}

void saveConfigCallback () {
  log_debug("Saved -> do Reset");
  ESP.reset();
}

//##############################
//## Setup
//##############################

void setup() {
  //### Starte Serial
  Serial.begin(CONF_SERIAL_BAUD);
  log("");
  log("--- Init ---");
  
  log("Start Hardware init");
  LedInit();  
  ColorInit();
  DrawInit();
  LDRInit();

  log("Start Time init");
  TimeInit();

  log("Start Wifimanger");
  WiFiManager wifiManager;  
  wifiManager.setConnectTimeout(10);
  wifiManager.setConfigPortalTimeout(180);
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  #ifndef CONF_DEBUG
    wifiManager.setDebugOutput(false);
  #endif  
  String ssid = settings.n_ap_ssid + String(ESP.getChipId());
  wifiManager.autoConnect(ssid.c_str(), NULL);

  //### Starte Webserver
  log("Start Webserver");
  WebsiteInit(&server);  
  server.begin();

  //### Starte UpdateServer 
  log("Start Updateserver");
  httpUpdaterServer.setup(&updateServer);
  updateServer.begin();

  log("--- Init End ---");
}

//##############################
//## Main Loop
//##############################

void loop() {  
  ColorTick();
  LedTick();
  DrawTick();
  TimeTick();
  LDRTick();
  
  server.handleClient();
  updateServer.handleClient();  
}
