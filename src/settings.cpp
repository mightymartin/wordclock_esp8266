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