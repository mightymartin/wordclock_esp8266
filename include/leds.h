#ifndef LEDS_H_
#define LEDS_H_

#include <NeoPixelBus.h>
#include <Ticker.h>
#include "ldr.h"
#include "settings.h"

#define LED_STATIS_OFF      0
#define LED_STATIS_ON       1
#define LED_STATIS_FADEIN   2
#define LED_STATIS_FADEOUT  3
#define LED_STATIS_UNKNOWN  4

#define LED_MAX_FADE_DURATION    2000
#define LED_MAX_BRIGHTNESS_STEPS MAX_FADE_STEPS

#define LED_PIXEL_PIN       2
#define LED_PIXEL_TYP       NeoGrbFeature //(NeoBrgFeature,NeoRgbFeature,NeoRbgFeature,NeoGrbFeature)
#define LED_PIXEL_METHOD    NeoEsp8266Dma800KbpsMethod

#define LED_LAYOUT          1  // 0: RADIG; 1: IKEAHACKER; 2: Mikrocontroller.net

struct LedObject {
    uint8 r = 0;
    uint8 g = 0;
    uint8 b = 0;
    uint8 fadeState = 0;
    uint8 status = 0;
};

//##############################
//## Declare Methods
//##############################
extern void         LedInit();
extern void         LedTick();
extern void         LedUpdate();

extern void         LedClear(uint8 hard);

extern uint8        LedMXtoNum(uint8 row, uint8 col);

extern void         LedSetColor(uint8 ledNum, uint8 r, uint8 g, uint8 b);
extern void         LedSetColorMatrix(uint8 row, uint8 col, uint8 r, uint8 g, uint8 b);
extern void         LedSetColorMinute(uint8 min, uint8 r, uint8 g, uint8 b);

extern void         LedSetStatus(uint8 ledNum, uint8 status);
extern void         LedSetStatusMatrix(uint8 row, uint8 col, uint8 status); 
extern void         LedSetStatusMinute(uint8 min, uint8 status);

extern uint8        LedGetStatus(uint8 ledNum);
extern uint8        LedGetStatusMatrix(uint8 row, uint8 col);

extern void         LedUnsetDirty();
extern void         LedSetDirty();
extern uint8        LedIsDirty();

#if LED_LAYOUT == 0 
    #include "leds_radig.h"
#elif LED_LAYOUT == 1
    #include "leds_ikeahackers.h"
#elif LED_LAYOUT == 2
    #include "leds_mikrocontroller.h"
#endif

#endif



