#include "mqtt.h"

static Ticker MQTTTimer(MQTTUpdate, 60000);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

uint32 lastChecksum = 0;

String cmdTopic, stateTopic;
char *mqtt_user = NULL;
char *mqtt_pass = NULL;

void MQTTUpdate(){    
    MQTTPublish(); 
}

boolean MQTTReconnect(){
    if(!mqttClient.connected()) {     
        WebLogInfo("Attempting MQTT connection...");        
        if (mqttClient.connect(settings.m_client_id, mqtt_user, mqtt_pass)) { 
            WebLogInfo("Connect succeeded");      
            mqttClient.subscribe(cmdTopic.c_str());
            WebLogDebug("subscribe to " + String(cmdTopic)); 
        } else {
            WebLogError("Connect failed, rc=" + String(mqttClient.state()));                  
        }        
    }  
    return mqttClient.connected();
}


void MQTTTick(){  
    MQTTTimer.update();
    mqttClient.loop();
    
    if(lastChecksum != SettingsGetChecksum()){
        MQTTPublish();  
        lastChecksum = SettingsGetChecksum();
    }    
}



void MQTTSubCallback(char* topic, byte* payload, unsigned int length) {
    uint8   validCmd = 1;
    String  command = String(strrchr(topic, '/')).substring(1);
    char    value = (length > 0) ? payload[0] : '0'; //only first Char, numbers only!

    if(
        command.equalsIgnoreCase(U_ONOFF_TAG) ||
        command.equalsIgnoreCase(C_BRIGHTNESS_TAG) ||
        command.equalsIgnoreCase(C_MODE_TAG) ||
        command.equalsIgnoreCase(D_MODE_TAG) 
    ){
        if(length > 0){
            SettingsSetValue(command,String(value));
        }        
    }else{    
        validCmd = 0;
    }

    if(validCmd == 1){
        WebLogInfo(String(topic) + " = " +  value);        
    }else{
        WebLogInfo("MQTT invalid Command " + command + " : " +  String((char*) payload) + ".");
    }
}

void MQTTPublish() {    
    if(MQTTReconnect()){        
        WebLogInfo(stateTopic + " = " + SettingsToJson());
        mqttClient.publish(stateTopic.c_str(),SettingsToJson().c_str());           
    }    
}

void MQTTInit(){
  if (strlen(settings.m_user) > 0) mqtt_user = settings.m_user;
    if (strlen(settings.m_pass) > 0) mqtt_pass = settings.m_pass;

    if(strlen(settings.m_topic) > 0 && strlen(settings.m_client_id) > 0 && strlen(settings.m_host) > 0 && settings.m_port > 0){
        cmdTopic = String(MQTT_TOPIC_PREFIX + String(settings.m_topic) + MQTT_CMD_TOPIC);
        stateTopic = String(MQTT_TOPIC_PREFIX + String(settings.m_topic) + MQTT_STATE_TOPIC);
                
        mqttClient.setServer(settings.m_host, settings.m_port);
        mqttClient.setCallback(MQTTSubCallback);
        MQTTTimer.start();

        MQTTPublish();
    }else{
        WebLogError("MQTT Missing Parameter"); 
    }
}

