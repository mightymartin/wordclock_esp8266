#include "ldr.h"
#include "settings.h"

static Ticker LDRTimer(LDRUpdate, 10000); 

static uint16 measureBuffer[LDR_MEASURE_COUNT];
static uint8  currentVal = MAX_FADE_STEPS-1;
static uint8  targetVal  = MAX_FADE_STEPS-1;

static uint8 bufferpos = 0;

void LDRInit(){
    for(uint8 i = 0; i < LDR_MEASURE_COUNT-1; i++){
        measureBuffer[i] = 1024;
    }
    LDRTimer.start();
    LDRUpdate();
}

void LDRTick(){
    LDRTimer.update();
}

void LDRUpdate(){
    //###################
    //## Messen
    //###################
    bufferpos++;
    if(bufferpos > LDR_MEASURE_COUNT-1){
        bufferpos = 0;
    }
    measureBuffer[bufferpos] = analogRead(LDR_MEASURE_PIN); 
    
    //###################
    //## Berechnen
    //###################
    #define     TH_COUNT (sizeof(settings.l_treshold) / 2)
        
    targetVal = settings.l_min_bright;    
    if(settings.u_LDR){        
        for(uint8 i=0; i < TH_COUNT; i++){
            if(LDRgetValue() >= settings.l_treshold[i]){                 
                targetVal = settings.l_min_bright + ( (MAX_FADE_STEPS-settings.l_min_bright) * (i+1) / TH_COUNT ) - 1;                
            }   
            if(targetVal > MAX_FADE_STEPS-1){
                targetVal = MAX_FADE_STEPS-1;
            } 
        }        
    }else{
        targetVal = MAX_FADE_STEPS-1;
    }

    //###################
    //## setzten
    //###################
    if(currentVal > targetVal){
        currentVal--;
    }

    if(currentVal < targetVal){
        currentVal++;
    }

    //###################
    //## Debug
    //###################
    WebLogDebug("LDRADC:" + String(LDRgetValue()));
    WebLogDebug("LDRPWM:" + String(LDRgetBrightness()));    
}

uint16 LDRgetValue(){
    uint16 avgVal = 0;
    for(uint8 i = 0; i < LDR_MEASURE_COUNT; i++){
        avgVal = avgVal + measureBuffer[i];
    }
    avgVal = avgVal / LDR_MEASURE_COUNT;
    return avgVal;
}
    
uint8 LDRgetBrightness(){    
    return currentVal;
}
