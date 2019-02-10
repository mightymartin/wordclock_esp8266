#ifndef SETTINGS_H
#define SETTINGS_H

#include <EEPROM.h>

typedef struct {
    //General
    uint8_t     version                 = 1;
    uint8_t     u_LDR                   = 0;
    uint8_t     u_MQTT                  = 0;
    uint8_t     u_NTP                   = 1;

    //network
    char        ntpserver[32]           = "de.pool.ntp.org";
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
    uint8_t     c_mode                  = 0;
    uint8_t     c_hue_rotate_rb         = 1;
    uint32_t    c_hue_rotate_duration   = 600000;
    uint8_t     c_plain_red             = 255;
    uint8_t     c_plain_green           = 255;
    uint8_t     c_plain_blue            = 0;
  
    //Draw
    uint8_t     d_mode                   = 0;
    uint8_t     d_clk_region             = 2;
    uint8_t     d_clk_itis_mode          = 1;
    uint8_t     d_clk_fade               = 1;

    
} Settings;


#endif