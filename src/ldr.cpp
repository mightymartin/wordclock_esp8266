#include "ldr.h"

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
    return 0;
}
    
    // void doLDRLogic() {   
    // if(millis() >= waitUntilLDR) {
    //     waitUntilLDR = millis();
    //     int temp = analogRead(A0);
    //     temp = temp - G.ldrCal;
    //     if (temp >= 900 ) temp = 900;
    //     if (temp <= 1 ) temp = 1;
    //     ldrVal = map(temp, 1, 900, 1, 100);
    //     waitUntilLDR += oneseconddelay;
    // }
    // }