#include "settings.h"

Settings_t settings;
StaticJsonBuffer<2048> jsonBuffer;

void SettingsFromJson(const char *filename){
    File configFile = SPIFFS.open(filename, "r");
    if (!configFile) {
        Serial.println("Failed to open config file");
        return;
    }

    JsonObject &jObj = jsonBuffer.parseObject(filename);
    
    //global
    settings.u_LDR = jObj[U_LDR_TAG];
    settings.u_MQTT = jObj[U_MQTT_TAG];
    settings.u_NTP = jObj[U_NTP_TAG];
    
    //Netzwerk
    settings.n_ntpinterval = jObj[N_NTPINTERVAL_TAG];
    strlcpy(settings.n_ntpserver , jObj[N_NTPSERVER_TAG], sizeof(settings.n_ntpserver));    
    strlcpy(settings.n_hostname, jObj[N_HOSTNAME_TAG], sizeof(settings.n_hostname));
    strlcpy(settings.n_ap_ssid, jObj[N_AP_SSID_TAG], sizeof(settings.n_ap_ssid));
    strlcpy(settings.n_ap_pass, jObj[N_AP_PASS_TAG], sizeof(settings.n_ap_pass));

    //MQTT
    settings.m_port = jObj[M_PORT_TAG];
    strlcpy(settings.m_host, jObj[M_HOST_TAG], sizeof(settings.m_host));    
    strlcpy(settings.m_client_id, jObj[M_CLIENT_ID_TAG], sizeof(settings.m_client_id));
    strlcpy(settings.m_user, jObj[M_USER_TAG], sizeof(settings.m_user));
    strlcpy(settings.m_pass, jObj[M_PASS_TAG], sizeof(settings.m_pass));
    strlcpy(settings.m_topic, jObj[M_TOPIC_TAG], sizeof(settings.m_topic));
    strlcpy(settings.m_fulltopic, jObj[M_FULLTOPIC_TAG], sizeof(settings.m_fulltopic));

    //Color
    settings.c_mode = jObj[C_MODE_TAG];
    settings.c_hue_rotate_rb = jObj[C_HUE_ROTATE_RB_TAG];
    settings.c_hue_rotate_duration = jObj[C_HUE_ROTATE_DURATION_TAG];
    settings.c_plain_red = jObj[C_PLAIN_RED_TAG];
    settings.c_plain_green = jObj[C_PLAIN_GREEN_TAG];
    settings.c_plain_blue = jObj[C_PLAIN_BLUE_TAG];

    //Draw
    settings.d_mode = jObj[D_MODE_TAG];
    settings.d_clk_region = jObj[D_CLK_REGION_TAG] ;
    settings.d_clk_itis_mode = jObj[D_CLK_ITIS_MODE_TAG];
    settings.d_clk_fade = jObj[D_CLK_FADE_TAG] ;
}

void SettingsToJson(){
    JsonObject &jObj = jsonBuffer.createObject();
    //global
    jObj["vers"]  = settings.version;
    jObj[U_LDR_TAG]  = settings.u_LDR;
    jObj[U_MQTT_TAG] = settings.u_MQTT;
    jObj[U_NTP_TAG]  = settings.u_NTP;
    
    //Netzwerk
    jObj[N_NTPINTERVAL_TAG]  = settings.n_ntpinterval;
    jObj[N_NTPSERVER_TAG]  = settings.n_ntpserver;    
    jObj[N_HOSTNAME_TAG]  = settings.n_hostname;
    jObj[N_AP_SSID_TAG]  = settings.n_ap_ssid;
    jObj[N_AP_PASS_TAG]  = settings.n_ap_pass;

    //MQTT
    jObj[M_PORT_TAG]  = settings.m_port;
    jObj[M_HOST_TAG]  = settings.m_host;    
    jObj[M_CLIENT_ID_TAG]  = settings.m_client_id;
    jObj[M_USER_TAG]  = settings.m_user;
    jObj[M_PASS_TAG]  = settings.m_pass;
    jObj[M_TOPIC_TAG]  = settings.m_topic;
    jObj[M_FULLTOPIC_TAG] = settings.m_fulltopic;

    //Color
    jObj[C_MODE_TAG]  = settings.c_mode;
    jObj[C_HUE_ROTATE_RB_TAG]  = settings.c_hue_rotate_rb;
    jObj[C_HUE_ROTATE_DURATION_TAG]  = settings.c_hue_rotate_duration;
    jObj[C_PLAIN_RED_TAG]   = settings.c_plain_red;
    jObj[C_PLAIN_GREEN_TAG] = settings.c_plain_green;
    jObj[C_PLAIN_BLUE_TAG]  = settings.c_plain_blue;

    //Draw
    jObj[D_MODE_TAG]  = settings.d_mode;
    jObj[D_CLK_REGION_TAG]  = settings.d_clk_region;
    jObj[D_CLK_ITIS_MODE_TAG]  = settings.d_clk_itis_mode;
    jObj[D_CLK_FADE_TAG]  = settings.d_clk_fade;
}


uint32_t SettingsGetChecksum(){
    uint32_t checksum = 0;
    uint8_t bufferP[sizeof(settings)];
    memcpy(bufferP, &settings, sizeof(settings));

    for (unsigned int i=0; i<sizeof(bufferP); i++){
        checksum += bufferP[i];
    }     
    return checksum;
}


void     SettingsWrite(){

}

void     SettingsRead(){

}

void     SettingsInit(){

}