#ifndef LDR_H_
#define LDR_H_

#include <Ticker.h>

#define LDR_MEASURE_COUNT  5
#define LDR_MEASURE_PIN    A0

extern void LDRInit();
extern void LDRTick();
extern void LDRUpdate();
extern uint16 LDRgetValue();
extern uint8  LDRgetBrightness();   

#endif