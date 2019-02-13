#include "settings.h"

Settings_t settings;

void SettingsToJson(){

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