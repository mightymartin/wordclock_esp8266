#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "FS.h"

#define CONF_WEBSERVER_PORT     80
#define CONF_UPDATESERVER_PORT  81
#define CONF_SERIAL_BAUD        115200
#define CONF_DEBUG              1

#define MAX_FADE_STEPS	            32
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


#define U_LDR_TAG                   "ULDR"   
#define U_MQTT_TAG                  "UMQTT" 
#define U_TEMP_TAG                  "UTEMP" 
#define N_NTPINTERVAL_TAG           "NNTPI" 
#define N_NTPSERVER_TAG             "NNTPS"
#define N_HOSTNAME_TAG              "NHOST"
#define N_AP_SSID_TAG               "NSSID"
#define N_AP_PASS_TAG               "NPASS"
#define M_PORT_TAG                  "MPORT"
#define M_HOST_TAG                  "MBROK"
#define M_CLIENT_ID_TAG             "MCLID"
#define M_USER_TAG                  "MUSER"
#define M_PASS_TAG                  "MPASS" 
#define M_TOPIC_TAG                 "MTOP"
#define M_FULLTOPIC_TAG             "MFTOP"
#define C_MODE_TAG                  "CMODE"
#define C_HUE_ROTATE_RB_TAG         "CROT"
#define C_HUE_ROTATE_DURATION_TAG   "CROTD"
#define C_PLAIN_RED_TAG             "CRED"
#define C_PLAIN_GREEN_TAG           "CGREE"
#define C_PLAIN_BLUE_TAG            "CBLUE"
#define C_BRIGHTNESs_TAG            "CBRIG"
#define C_LDR_TRESHHOLD_TAG         "LDRT"

#define D_MODE_TAG                  "DMODE"
#define D_CLK_REGION_TAG            "DREGI"
#define D_CLK_ITIS_MODE_TAG         "DITIS"
#define D_CLK_FADE_TAG              "DFADE" 



struct Settings_t{
    //General
    uint8     version                 = 2;
    uint8     u_LDR                   = 1;
    uint8     u_MQTT                  = 0;
    uint8     u_TEMP                  = 1;

    //network
    uint32_t    n_ntpinterval           = 60000;
    char        n_ntpserver[32]         = "de.pool.ntp.org";    
    char        n_hostname[32]          = "Wordclock";
    char        n_ap_ssid[32]           = "Wordclock"; //??
    char        n_ap_pass[32]           = "";

    //MQTT
    uint16_t    m_port                  = 1883;
    char        m_host[32]              = "";    
    char        m_client_id[32]         = "";
    char        m_user[32]              = "";
    char        m_pass[32]              = "";
    char        m_topic[32]             = "";
    char        m_fulltopic[32]         = "";

    //Color
    uint8       c_mode                  = 2;
    uint8       c_hue_rotate_rb         = 1;
    uint32_t    c_hue_rotate_duration   = 300000;
    uint8       c_plain_red             = 255;
    uint8       c_plain_green           = 255;
    uint8       c_plain_blue            = 0;
    
    uint8       c_brightness            = MAX_FADE_STEPS-1;     
    uint16      c_ldrTreshhold[8]       = {200,300,400,500,600,700,800,900};

    //Draw
    uint8       d_mode                   = 0;
    uint8       d_clk_region             = 2;
    uint8       d_clk_itis_mode          = 1;
    uint8       d_clk_fade               = 1;

    
}  __attribute__((packed));

extern Settings_t settings;

extern uint32_t SettingsGetChecksum();
extern void     SettingsSetValue(String key, String value);
extern void     SettingsToJson(String *jsonDest);
extern void     SettingsWrite();
extern void     SettingsRead();
extern void     SettingsFactoryReset();

#endif