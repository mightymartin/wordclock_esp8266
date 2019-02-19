#include "ldr.h"
#include "settings.h"

static Ticker LDRTimer(LDRUpdate, 10000); 

static uint16 measureBuffer[LDR_MEASURE_COUNT];
static uint8 currentVal = MAX_FADE_STEPS-1;
static uint8 targetVal  = MAX_FADE_STEPS-1;

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
    uint8 minStep = settings.l_min_bright;
    uint8 thCount = sizeof(settings.l_treshold) / 2; //geteilt durch 2 wegen uint16
    uint8 thStep = round((MAX_FADE_STEPS-minStep) / thCount);    
    targetVal = thStep-1;    

    if(settings.u_LDR){        
        for(uint8 i=0; i < thCount; i++){
            if(LDRgetValue() >= settings.l_treshold[i]){                 
                targetVal = minStep + (thStep*(i+1)) - 1;                
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
    //Serial.println(LDRgetValue());   
    //Serial.println(LDRgetBrightness());       
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
