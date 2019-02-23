#include "settings.h"
#include "logging.h"

Settings_t settings;

uint8 doRestart = 0;

void    SettingsInit(){
    SettingsRead();
    if(!String(settings.version).equals(FW_VERSION)){
        WebLogInfo("Settings Version mismatch!");   
        settings = {};     
        SettingsClear();        
        SettingsSetDefaults();
        SettingsWrite();
    }else{
        WebLogInfo("Done");        
    }
}

void SettingsSetDefaults(){
    strcpy(settings.version,FW_VERSION); 
    settings.u_LDR                   = 1;
    settings.u_MQTT                  = 0;
    settings.u_TEMP                  = 1;
    settings.u_MDNS                  = 1;
    settings.u_LOGGING               = 2;
    settings.u_DISPLAYON             = 1;
    settings.n_ntpinterval           = 60000;    
    strcpy(settings.n_ntpserver,"de.pool.ntp.org");    
    strcpy(settings.n_hostname ,"Wordclock");
    settings.m_port                  = 1883;    
    settings.c_mode                  = 2;
    settings.c_hue_rotate_rb         = 1;
    settings.c_hue_rotate_duration   = 300000;
    settings.c_plain_red             = 255;
    settings.c_plain_green           = 255;
    settings.c_plain_blue            = 0;
    settings.c_brightness            = MAX_FADE_STEPS-1;     
    settings.l_min_bright            = 4;     
    settings.l_treshold[0]           = 100;
    settings.l_treshold[1]           = 300;
    settings.l_treshold[2]           = 400;
    settings.l_treshold[3]           = 500;
    settings.l_treshold[4]           = 600;
    settings.l_treshold[5]           = 700;
    settings.l_treshold[6]           = 750;
    settings.l_treshold[7]           = 800;
    settings.l_treshold[8]           = 850;
    settings.l_treshold[9]           = 900;
    settings.d_mode                  = 0;
    settings.d_clk_region            = 2;
    settings.d_clk_itis_mode         = 1;
    settings.d_clk_fade              = 1;
}

void    SettingsWrite(){    
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.put(EEPROM_START_ADDRESS,settings);
    delay(200);
    EEPROM.commit();
    EEPROM.end();
    WebLogInfo("Wrote Settings Version: " + String(settings.version));
}

void    SettingsRead(){
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.get(EEPROM_START_ADDRESS,settings);
    delay(200);
    EEPROM.end();
    WebLogInfo("Read Settings Version: " + String(settings.version));
}

void    SettingsClear(){    
    EEPROM.begin(EEPROM_SIZE);
    for (int i = EEPROM_START_ADDRESS ; i < EEPROM_SIZE ; i++) {
        EEPROM.write(i, 0);
    }
    delay(200);
    EEPROM.commit();
    EEPROM.end();
    WebLogInfo("EEPROM Cleared");
}

void    SettingsWifiReset(){    
    //Erase Wifi
    WiFi.persistent(false);     
    WiFi.disconnect(true);
    WiFi.persistent(true);

    //Erase Config
    ESP.eraseConfig();
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

void    SettingsSetValue(String key, String value){
    if(key.equals(U_LDR_TAG)){
        settings.u_LDR = (uint8)value.toInt();
    }else if(key.equals(U_MQTT_TAG)){
        settings.u_MQTT = (uint8)value.toInt();
    }else if(key.equals(U_TEMP_TAG)){
        settings.u_TEMP = (uint8)value.toInt();
    }else if(key.equals(U_MDNS_TAG)){
        settings.u_MDNS = (uint8)value.toInt();
    }else if(key.equals(U_LOGG_TAG)){
        settings.u_LOGGING = (uint8)value.toInt();
    }else if(key.equals(U_ONOFF_TAG)){
        settings.u_DISPLAYON = (uint8)value.toInt();
    }else if(key.equals(N_NTPINTERVAL_TAG)){    
        settings.n_ntpinterval = (uint32)value.toInt();
    }else if(key.equals(N_NTPSERVER_TAG)){    
        strcpy(settings.n_ntpserver, value.c_str());
    }else if(key.equals(N_HOSTNAME_TAG)){    
        strcpy(settings.n_hostname, value.c_str());
    }else if(key.equals(M_PORT_TAG)){
        settings.m_port = (uint16)value.toInt();
    }else if(key.equals(M_HOST_TAG)){    
        strcpy(settings.m_host, value.c_str());
    }else if(key.equals(M_CLIENT_ID_TAG)){    
        strcpy(settings.m_client_id, value.c_str());
    }else if(key.equals(M_USER_TAG)){    
        strcpy(settings.m_user, value.c_str());
    }else if(key.equals(M_PASS_TAG)){    
        strcpy(settings.m_pass, value.c_str());
    }else if(key.equals(M_TOPIC_TAG)){
        strcpy(settings.m_topic, value.c_str());
    }else if(key.equals(M_FULLTOPIC_TAG)){
        strcpy(settings.m_fulltopic, value.c_str());
    }else if(key.equals(C_MODE_TAG)){    
        settings.c_mode = (uint8)value.toInt();
    }else if(key.equals(C_HUE_ROTATE_RB_TAG)){    
        settings.c_hue_rotate_rb = (uint8)value.toInt();
    }else if(key.equals(C_HUE_ROTATE_DURATION_TAG)){    
        settings.c_hue_rotate_duration = (uint8)value.toInt();
    }else if(key.equals(C_PLAIN_RED_TAG)){            
        settings.c_plain_red = (uint8)value.toInt();
    }else if(key.equals(C_PLAIN_GREEN_TAG)){    
        settings.c_plain_green = (uint8)value.toInt();
    }else if(key.equals(C_PLAIN_BLUE_TAG)){    
        settings.c_plain_blue = (uint8)value.toInt();
    }else if(key.equals(C_BRIGHTNESS_TAG)){ 
        settings.c_brightness = (uint8)value.toInt();
    }else if(key.equals(L_MIN_BRIGHT_TAG)){    
        settings.l_min_bright = (uint8)value.toInt();        
    }else if(key.startsWith(L_TRESHOLD_TAG)){  
        char    c = key.charAt(key.length()-1);
        uint8 idx = c - '0'; // die postion von null abziehen ergibt den zahlenwert        
        if(idx >= 0 && idx < sizeof(settings.l_treshold)/2 ){   //geteilt durch 2 wegen uint16
            settings.l_treshold[idx] = (uint16)value.toInt();         
        }        
    }else if(key.equals(D_MODE_TAG)){    
        settings.d_mode = (uint8)value.toInt();
    }else if(key.equals(D_CLK_REGION_TAG)){ 
        settings.d_clk_region = (uint8)value.toInt();
    }else if(key.equals(D_CLK_ITIS_MODE_TAG)){    
        settings.d_clk_itis_mode = (uint8)value.toInt();
    }else if(key.equals(D_CLK_FADE_TAG)){    
        settings.d_clk_fade = (uint8)value.toInt();
    }        
}

//TODO move settingstojson to mqtt part
const char PROP_STR[]    PROGMEM    = QUOTE( "{key}":"{val}", );
const char PROP_INT[]    PROGMEM    = QUOTE( "{key}":{val}, );

String  getPropInt(String key, uint32 val){
    String ret = FPSTR(PROP_INT);
    ret.replace("{key}", key);
    ret.replace("{val}", String(val) );
    return ret;
}  

String  getPropStr(String key, String val){
    String ret = FPSTR(PROP_STR);
    ret.replace("{key}", key);
    ret.replace("{val}", val );
    return ret;
}

String    SettingsToJson(){ 
    String jsonDest = "{";   
    jsonDest += getPropInt(U_ONOFF_TAG,                 settings.u_DISPLAYON);

    jsonDest += getPropInt(C_MODE_TAG,                  settings.c_mode);
    jsonDest += getPropInt(C_HUE_ROTATE_RB_TAG,         settings.c_hue_rotate_rb);
    jsonDest += getPropInt(C_HUE_ROTATE_DURATION_TAG,   settings.c_hue_rotate_duration);
    jsonDest += getPropInt(C_PLAIN_RED_TAG,             settings.c_plain_red);
    jsonDest += getPropInt(C_PLAIN_GREEN_TAG,           settings.c_plain_green);
    jsonDest += getPropInt(C_PLAIN_BLUE_TAG,            settings.c_plain_blue);
    jsonDest += getPropInt(C_BRIGHTNESS_TAG,            settings.c_brightness);

    jsonDest += getPropInt(L_MIN_BRIGHT_TAG,            settings.l_min_bright);    
    for(uint8 idx = 0; idx < sizeof(settings.l_treshold)/2 ; idx++){   //geteilt durch 2 wegen uint16
        jsonDest += getPropInt(L_TRESHOLD_TAG + String(idx), settings.l_treshold[idx]);
    }
    
    jsonDest += getPropInt(D_MODE_TAG,                  settings.d_mode);
    jsonDest += getPropInt(D_CLK_REGION_TAG,            settings.d_clk_region);
    jsonDest += getPropInt(D_CLK_ITIS_MODE_TAG,         settings.d_clk_itis_mode);
    jsonDest += getPropInt(D_CLK_FADE_TAG,              settings.d_clk_fade); 

    jsonDest += getPropStr(N_HOSTNAME_TAG,              String(settings.n_hostname));
    jsonDest += getPropStr(G_VERSION,                   String(settings.version));
    jsonDest += getPropStr(G_TIME,                      "HH:MM:SS");

    jsonDest.remove(jsonDest.length()-1);   

    jsonDest += "}";

    return jsonDest;
}

//##############
//### Restart 
//##############
void    SettingsSoftRestart(){
    doRestart = 1;
}

void    SettingsTick(){
    if(doRestart){
        doRestart = 0;
        ESP.reset();
    }
}