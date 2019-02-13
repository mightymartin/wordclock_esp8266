#include "ldr.h"
#include "settings.h"

static Ticker LDRTimer(LDRUpdate, 1000); 

static uint16 measureBuffer[LDR_MEASURE_COUNT];

void LDRInit(){
    LDRTimer.start();
    LDRUpdate();
}

void LDRTick(){
    LDRTimer.update();
}

void LDRUpdate(){
    //move the last measurements in buffer
    for(uint8 i = 0; i < LDR_MEASURE_COUNT-1; i++){
        measureBuffer[i] = measureBuffer[i+1];
    }
    measureBuffer[LDR_MEASURE_COUNT-1] = analogRead(LDR_MEASURE_PIN); 
    
    Serial.println(LDRgetValue());   
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
    //TODO umsetzung nach user defined treshhold table
    if(settings.u_LDR){
        return 0;
    }else{
        return 255;
    }    
}
