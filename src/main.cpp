#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>

#include "logging.h"
#include "leds.h"
#include "color.h"
#include "timeNTP.h"
#include "draw.h"
#include "ldr.h"
#include "settings.h"
#include "website.h"
#include "mqtt.h"


//##############################
//## Instances
//##############################
ESP8266WebServer server(CONF_WEBSERVER_PORT);
ESP8266HTTPUpdateServer httpUpdaterServer;

//##############################
//## Setup
//##############################

void setup() {
  //### calm after reset
  delay(500);
  
  //### Starte Serial  
  WebLogInit();
  Serial.begin(CONF_SERIAL_BAUD);

  WebLogInfo("");
  WebLogInfo("--- Init ---");
  
  WebLogInfo("Init Settings");
  SettingsInit();

  WebLogInfo("Start Hardware init");
  LedInit();  
  ColorInit();
  DrawInit();
  LDRInit();

  wifi_station_set_hostname(settings.n_hostname);
  WiFi.hostname(settings.n_hostname);
  
  WebLogInfo("Start Wifimanger");
  WiFiManager wifiManager;  
  wifiManager.setConnectTimeout(10);
  wifiManager.setConfigPortalTimeout(180);
  //wifiManager.setSaveConfigCallback(saveConfigCallback);
  if(settings.u_LOGGING >= LOGLEVEL_DBG){
    wifiManager.setDebugOutput(true);
  }  
  wifiManager.autoConnect(settings.n_hostname, NULL);

  //NTP Zeit
  WebLogInfo("Start Time init");
  TimeInit();

  //### Init Website
  WebLogInfo("Init Website");
  WebsiteInit(&server);  
  
  //### Init UpdateServer 
  WebLogInfo("Init Updateserver");
  httpUpdaterServer.setup(&server,REQ_OTA);
  
  //### Start Webserver
  WebLogInfo("Start Webserver");
  server.begin();

  if(settings.u_MQTT){
    //### Start MQTT
    WebLogInfo("Start MQTT");
    MQTTInit();
  }

  //### Start mDNS
  if(settings.u_MDNS == 1){
      WebLogInfo("Start mDNS");
      MDNS.begin(settings.n_hostname); 
      MDNS.addService("http", "tcp", CONF_WEBSERVER_PORT);      
      MDNS.addService("ws", "tcp", CONF_WEBSOCKET_PORT); 
      if(settings.u_MQTT){
          MDNS.addService("mqtt", "tcp", settings.m_port);
      }
  }

  WebLogInfo("--- Init End ---");
}

//##############################
//## Main Loop
//##############################

void loop() {  
  ColorTick();
  LedTick();
  DrawTick();
  TimeTick();  
  
  if(settings.u_LDR){
    LDRTick();
  }
  
  WebLogTick();
  
  if(settings.u_MQTT){
    MQTTTick(); 
  }

  SettingsTick();
  server.handleClient();  
}
