#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>

struct Settings_t{
    //General
    uint8     version                 = 1;
    uint8     u_LDR                   = 0;
    uint8     u_MQTT                  = 0;
    uint8     u_NTP                   = 1;

    //network
    char        n_ntpserver[32]         = "de.pool.ntp.org";
    uint32_t    n_ntpinterval           = 60000;
    char        n_hostname[32]          = "Wordclock";
    char        n_ap_ssid[32]           = "Wordclock"; //??
    char        n_ap_pass[32]           = "";

    //MQTT
    char        m_host[32]              = "";
    uint16_t    m_port                  = 1883;
    char        m_client_id[32]         = "";
    char        m_user[32]              = "";
    char        m_pass[32]              = "";
    char        m_topic[32]             = "";
    char        m_fulltopic[32]         = "";

    //Color
    uint8       c_mode                  = 0;
    uint8       c_hue_rotate_rb         = 1;
    uint32_t    c_hue_rotate_duration   = 300000;
    uint8       c_plain_red             = 255;
    uint8       c_plain_green           = 255;
    uint8       c_plain_blue            = 0;
  
    //Draw
    uint8       d_mode                   = 0;
    uint8       d_clk_region             = 2;
    uint8       d_clk_itis_mode          = 1;
    uint8       d_clk_fade               = 1;

    
}  __attribute__((packed));

extern Settings_t settings;

extern void     SettingsToJson();
extern uint32   SettingsGetChecksum();

extern void     SettingsWrite();
extern void     SettingsRead();

extern void     SettingsInit();

#endif