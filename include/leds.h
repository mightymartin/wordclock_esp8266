#ifndef LEDS_H_
#define LEDS_H_

#include <NeoPixelBus.h>
#include <Ticker.h>
#include "ldr.h"
#include "settings.h"

#define LED_PIXEL_PIN       2
#define LED_PIXEL_TYP       NeoGrbFeature //(NeoBrgFeature,NeoRgbFeature,NeoRbgFeature,NeoGrbFeature)
#define LED_PIXEL_METHOD    NeoEsp8266Dma800KbpsMethod

#define LED_STATIS_OFF      0
#define LED_STATIS_ON       1
#define LED_STATIS_FADEIN   2
#define LED_STATIS_FADEOUT  3
#define LED_STATIS_UNKNOWN  4

#define LED_MAX_FADE_DURATION    2000
#define LED_MAX_BRIGHTNESS_STEPS MAX_FADE_STEPS

#define LED_MATRIX_ROWS	10
#define LED_MATRIX_COLS	11
#define LED_DOTS	    4
#define LED_COUNT       (LED_MATRIX_ROWS*LED_MATRIX_COLS)+LED_DOTS

struct LedObject {
    uint8 r = 0;
    uint8 g = 0;
    uint8 b = 0;
    uint8 fadeState = 0;
    uint8 status = 0;
};

const uint8 matrixIndex[LED_MATRIX_ROWS][LED_MATRIX_COLS] =         {                              
                                                                        {99,100,101,102,103,104,105,106,107,108,109},
                                                                        {98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88},
                                                                        {77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87},
                                                                        {76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66},
                                                                        {55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65},
                                                                        {54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44},
                                                                        {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43},
                                                                        {32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22},
                                                                        {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
                                                                        {10  ,9,  8,  7,  6,  5,  4,  3,  2,  1,  0}
                                                                    };

const uint8 dotsIndex[LED_DOTS] =           {
                                                111,110,113,112
                                            };

//##############################
//## Declare Methods
//##############################


extern void         LedInit();
extern void         LedTick();
extern void         LedUpdate();

extern void         LedClear(uint8 hard);

extern uint8 LedMXtoNum(uint8 row, uint8 col);

extern void         LedSetColor(uint8 ledNum, uint8 r, uint8 g, uint8 b);
extern void         LedSetColorMatrix(uint8 row, uint8 col, uint8 r, uint8 g, uint8 b);
extern void         LedSetColorMinute(uint8 min, uint8 r, uint8 g, uint8 b);

extern void         LedSetStatus(uint8 ledNum, uint8 status);
extern void         LedSetStatusMatrix(uint8 row, uint8 col, uint8 status); 
extern void         LedSetStatusMinute(uint8 min, uint8 status);

extern uint8 LedGetStatus(uint8 ledNum);
extern uint8 LedGetStatusMatrix(uint8 row, uint8 col);

extern void         LedUnsetDirty();
extern void         LedSetDirty();
extern uint8 LedIsDirty();

//##############################
//## Define Methods
//##############################

//#### Fill Words
static inline void LedSetEsIst(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    //Es
    LedSetStatusMatrix(0,0,mode);
    LedSetStatusMatrix(0,1,mode);

    //Ist
    LedSetStatusMatrix(0,3,mode);
    LedSetStatusMatrix(0,4,mode);
    LedSetStatusMatrix(0,5,mode);
}

static inline void LedSetUhr(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(9,8,mode);
    LedSetStatusMatrix(9,9,mode);
    LedSetStatusMatrix(9,10,mode);
}

static inline void LedSetVor(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(3,0,mode);
    LedSetStatusMatrix(3,1,mode);
    LedSetStatusMatrix(3,2,mode);
}

static inline void LedSetNach(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(3,7,mode);
    LedSetStatusMatrix(3,8,mode);
    LedSetStatusMatrix(3,9,mode);
    LedSetStatusMatrix(3,10,mode);
}

static inline void LedSetFunk(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(3,3,mode);
    LedSetStatusMatrix(3,4,mode);
    LedSetStatusMatrix(3,5,mode);
    LedSetStatusMatrix(3,6,mode);
}

//#### Minutes Words
static inline void LedSetFuenfMin(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(0,7,mode);
    LedSetStatusMatrix(0,8,mode);
    LedSetStatusMatrix(0,9,mode);
    LedSetStatusMatrix(0,10,mode);
}

static inline void LedSetZehnMin(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(1,0,mode);
    LedSetStatusMatrix(1,1,mode);
    LedSetStatusMatrix(1,2,mode);
    LedSetStatusMatrix(1,3,mode);
}

static inline void LedSetZwanzigMin(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(1,4,mode);
    LedSetStatusMatrix(1,5,mode);
    LedSetStatusMatrix(1,6,mode);
    LedSetStatusMatrix(1,7,mode);
    LedSetStatusMatrix(1,8,mode);
    LedSetStatusMatrix(1,9,mode);
    LedSetStatusMatrix(1,10,mode);
}

static inline void LedSetViertelMin(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(2,4,mode);
    LedSetStatusMatrix(2,5,mode);
    LedSetStatusMatrix(2,6,mode);
    LedSetStatusMatrix(2,7,mode);
    LedSetStatusMatrix(2,8,mode);
    LedSetStatusMatrix(2,9,mode);
    LedSetStatusMatrix(2,10,mode);
}

static inline void LedSetDreiviertelMin(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(2,0,mode);
    LedSetStatusMatrix(2,1,mode);
    LedSetStatusMatrix(2,2,mode);
    LedSetStatusMatrix(2,3,mode);
    LedSetViertelMin(hard);
}

static inline void LedSetHalbMin(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(4,0,mode);
    LedSetStatusMatrix(4,1,mode);
    LedSetStatusMatrix(4,2,mode);
    LedSetStatusMatrix(4,3,mode);    
}

static inline void LedSetMinDot(uint8 dot, uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMinute(dot,mode);    
}

//#### Hours Words
static inline void LedSetEinHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(5,0,mode);
    LedSetStatusMatrix(5,1,mode);
    LedSetStatusMatrix(5,2,mode);      
}

static inline void LedSetEinsHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetEinHour(mode);
    //s
    LedSetStatusMatrix(5,3,mode);    
}

static inline void LedSetZweiHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(5,7,mode);
    LedSetStatusMatrix(5,8,mode);
    LedSetStatusMatrix(5,9,mode);      
    LedSetStatusMatrix(5,10,mode);
}

static inline void LedSetDreiHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(6,0,mode);
    LedSetStatusMatrix(6,1,mode);
    LedSetStatusMatrix(6,2,mode);      
    LedSetStatusMatrix(6,3,mode);      
}

static inline void LedSetVierHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(6,7,mode);
    LedSetStatusMatrix(6,8,mode);
    LedSetStatusMatrix(6,9,mode);      
    LedSetStatusMatrix(6,10,mode);  
}

static inline void LedSetFuenfHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(4,7,mode);
    LedSetStatusMatrix(4,8,mode);
    LedSetStatusMatrix(4,9,mode);      
    LedSetStatusMatrix(4,10,mode);  
}

static inline void LedSetSechsHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(7,0,mode);
    LedSetStatusMatrix(7,1,mode);
    LedSetStatusMatrix(7,2,mode);      
    LedSetStatusMatrix(7,3,mode);  
    LedSetStatusMatrix(7,4,mode);  
}

static inline void LedSetSiebenHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(8,0,mode);
    LedSetStatusMatrix(8,1,mode);
    LedSetStatusMatrix(8,2,mode);      
    LedSetStatusMatrix(8,3,mode);  
    LedSetStatusMatrix(8,4,mode);  
    LedSetStatusMatrix(8,5,mode);  
}

static inline void LedSetAchtHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(7,7,mode);
    LedSetStatusMatrix(7,8,mode);
    LedSetStatusMatrix(7,9,mode);      
    LedSetStatusMatrix(7,10,mode);  
}

static inline void LedSetNeunHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(9,3,mode);
    LedSetStatusMatrix(9,4,mode);
    LedSetStatusMatrix(9,5,mode);      
    LedSetStatusMatrix(9,6,mode);  
}

static inline void LedSetZehnHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(9,0,mode);
    LedSetStatusMatrix(9,1,mode);
    LedSetStatusMatrix(9,2,mode);      
    LedSetStatusMatrix(9,3,mode);  
}

static inline void LedSetElfHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(4,5,mode);
    LedSetStatusMatrix(4,6,mode);
    LedSetStatusMatrix(4,7,mode);          
}

static inline void LedSetZwoelfHour(uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;    
    LedSetStatusMatrix(8,6,mode);
    LedSetStatusMatrix(8,7,mode);
    LedSetStatusMatrix(8,8,mode);      
    LedSetStatusMatrix(8,9,mode);  
    LedSetStatusMatrix(8,10,mode);  
}
#endif



