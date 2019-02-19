#include "settings.h"

Settings_t settings;

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
    }else if(key.equals(N_NTPINTERVAL_TAG)){    
        settings.n_ntpinterval = (uint32)value.toInt();
    }else if(key.equals(N_NTPSERVER_TAG)){    
        strcpy(settings.n_ntpserver, value.c_str());
    }else if(key.equals(N_HOSTNAME_TAG)){    
        strcpy(settings.n_hostname, value.c_str());
    }else if(key.equals(N_AP_SSID_TAG)){    
        strcpy(settings.n_ap_ssid, value.c_str());
    }else if(key.equals(N_AP_PASS_TAG)){
        strcpy(settings.n_ap_pass, value.c_str());
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

                  
         
   
             
           
            
            
         
                  
            
         
                 
        

        // settings.u_LDR = key.toInt()
        
}

void    SettingsToJson(String *jsonDest){
    
}

void    SettingsWrite(){

}

void    SettingsRead(){

}

void    SettingsFactoryReset(){

}