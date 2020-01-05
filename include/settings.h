#ifndef SETTINGS_H
#define SETTINGS_H

#include <ESP8266WiFi.h> 
#include <Arduino.h> 
#include <EEPROM.h>

#define QUOTE(...) #__VA_ARGS__

#define EEPROM_START_ADDRESS    0
#define EEPROM_SIZE             4095

#define FW_VERSION              "0.13"
#define CONF_WEBSERVER_PORT     80
#define CONF_WEBSOCKET_PORT     81
#define CONF_SERIAL_BAUD        115200
#define MAX_FADE_STEPS	        32

#if (MAX_FADE_STEPS==32)
    const uint8 pwm_table[MAX_FADE_STEPS] = {
                                                        0,   1,   3,   4,   5,   6,   7,   8,
                                                        9,  10,  12,  14,  16,  18,  21,  24,
                                                        28,  32,  37,  42,  48,  55,  63,  72,
                                                        83,  96, 111, 129, 153, 182, 216, 255
                                                    };
#else
    #error unknown pwm step size
#endif


#define G_VERSION                   "GVER"   
#define G_TIME                      "GTIME"   

#define U_LDR_TAG                   "ULDR"   
#define U_MQTT_TAG                  "UMQTT" 
#define U_MDNS_TAG                  "UMDNS" 
#define U_LOGG_TAG                  "ULOGG" 
#define U_ONOFF_TAG                 "UONOFF" 

#define N_NTPINTERVAL_TAG           "NNTPI" 
#define N_NTPSERVER_TAG             "NNTPS"
#define N_HOSTNAME_TAG              "NHOST"
#define M_PORT_TAG                  "MPORT"
#define M_HOST_TAG                  "MBROK"
#define M_CLIENT_ID_TAG             "MCLID"
#define M_USER_TAG                  "MUSER"
#define M_PASS_TAG                  "MPASS" 
#define M_TOPIC_TAG                 "MTOP"
#define C_MODE_TAG                  "CMODE"
#define C_HUE_ROTATE_RB_TAG         "CROT"
#define C_HUE_ROTATE_DURATION_TAG   "CROTD"
#define C_PLAIN_RED_TAG             "CRED"
#define C_PLAIN_GREEN_TAG           "CGREE"
#define C_PLAIN_BLUE_TAG            "CBLUE"
#define C_BRIGHTNESS_TAG            "CBRIG"

#define L_MIN_BRIGHT_TAG            "LDMI"
#define L_TRESHOLD_TAG              "LDTR"

#define D_MODE_TAG                  "DMODE"
#define D_CLK_REGION_TAG            "DREGI"
#define D_CLK_ITIS_MODE_TAG         "DITIS"
#define D_CLK_FADE_TAG              "DFADE" 

#define D_TEMP_TAG                  "DTEMP"
#define D_TEMP_TIMEOUT_TAG          "DTETI"
#define D_TEXT_TAG                  "DTEXT"
#define D_TEXT_SPEED_TAG            "DTESP" 


struct Settings_t{
    //General
    char      version[5]              ; 
    uint8     u_LDR                   ;
    uint8     u_MQTT                  ;
    uint8     u_MDNS                  ;
    uint8     u_LOGGING               ;
    uint8     u_DISPLAYON             ;

    //network
    uint32_t    n_ntpinterval           ;
    char        n_ntpserver[32]         ;    
    char        n_hostname[32]          ;

    //MQTT
    uint16_t    m_port                  ;
    char        m_host[32]              ;    
    char        m_client_id[32]         ;
    char        m_user[32]              ;
    char        m_pass[32]              ;
    char        m_topic[32]             ;

    //Color
    uint8       c_mode                  ;
    uint8       c_hue_rotate_rb         ;
    uint32_t    c_hue_rotate_duration   ;
    uint8       c_plain_red             ;
    uint8       c_plain_green           ;
    uint8       c_plain_blue            ;
    
    uint8       c_brightness            ;
    
    uint8       l_min_bright            ;    
    uint16      l_treshold[10]          ;
    
    //Draw
    uint8       d_mode                  ;
    uint8       d_clk_region            ;
    uint8       d_clk_itis_mode         ;
    uint8       d_clk_fade              ;
    uint8       d_temperatur            ;
    uint8       d_temperatur_timeout    ;
    uint8       d_text_speed            ;
    char        d_text[256]             ;
    
}  __attribute__((packed));

extern Settings_t settings;

extern uint8    doRestart;

extern void     SettingsInit();

extern void     SettingsSetDefaults();

extern uint32_t SettingsGetChecksum();
extern void     SettingsSetValue(String key, String value);
extern String   SettingsToJson();

extern void     SettingsWrite();
extern void     SettingsRead();
extern void     SettingsClear();

extern void     SettingsWifiReset();
extern void     SettingsSoftRestart();
extern void     SettingsTick();

#endif