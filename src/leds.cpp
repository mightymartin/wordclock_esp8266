#include "leds.h"

static Ticker LedTimer(LedUpdate, LED_MAX_FADE_DURATION/LED_MAX_FADE_STEPS);
static NeoPixelBus<LED_PIXEL_TYP, LED_PIXEL_METHOD> neoPixelStrip(LED_COUNT, LED_PIXEL_PIN);

static uint8    uiDirty = 0;
static uint16   brightnessStep = LED_MAX_BRIGHTNESS_STEPS-1; //TODO aus config

static LedObject ledObjects[LED_COUNT];

#if (LED_MAX_FADE_STEPS==32)
    uint8_t pwm_table[LED_MAX_FADE_STEPS] = {
                                                        0,   1,   3,   4,   5,   6,   7,   8,
                                                        9,  10,  12,  14,  16,  18,  21,  24,
                                                        28,  32,  37,  42,  48,  55,  63,  72,
                                                        83,  96, 111, 129, 153, 182, 216, 255
                                                    };
#else
    #error unknown pwm step size
#endif

void LedInit(){    
    LedClear(1); 

    neoPixelStrip.Begin();    
    neoPixelStrip.Show();
    
    LedTimer.start();
}

void LedTick(){
    LedTimer.update();
}

void LedUpdate(){
    if(LedIsDirty()){
        for(uint8 ledNum = 0; ledNum < LED_COUNT; ledNum++){
            uint16_t generalBrightness  = (uint16_t)pwm_table[brightnessStep];
            uint16 red = (generalBrightness * ledObjects[ledNum].r) / 255;
            uint16 green = (generalBrightness * ledObjects[ledNum].g) / 255;
            uint16 blue = (generalBrightness * ledObjects[ledNum].b) / 255;

            // uint16_t ldrBrightness  = (uint16_t)pwm_table[LED_MAX_BRIGHTNESS_STEPS-1]; //TODO getLDRValue z.b.
            // red = (ldrBrightness * red) / 255;
            // green = (ldrBrightness * green) / 255;
            // blue = (ldrBrightness * blue) / 255;
    
            if(ledObjects[ledNum].status == LED_STATIS_ON){
                //LED ist AN
                //Wird mit aktueller Farbe in der aktuellen Helligkeit geschrieben                
            }else if(ledObjects[ledNum].status == LED_STATIS_OFF){
                //Led ist AUS
                red = 0;
                green = 0;
                blue = 0;
            }else if(ledObjects[ledNum].status == LED_STATIS_FADEIN){
                uint16_t fadeBrightness  = (uint16_t)pwm_table[ledObjects[ledNum].fadeState]; 
                red = (fadeBrightness * red) / 255;
                green = (fadeBrightness * green) / 255;
                blue = (fadeBrightness * blue) / 255;

                if(ledObjects[ledNum].fadeState < LED_MAX_FADE_STEPS-1){
                    ledObjects[ledNum].fadeState++;
                }else{
                    ledObjects[ledNum].status = LED_STATIS_ON;
                }
            }else if(ledObjects[ledNum].status == LED_STATIS_FADEOUT){
                uint16_t fadeBrightness  = (uint16_t)pwm_table[ledObjects[ledNum].fadeState]; 
                red = (fadeBrightness * red) / 255;
                green = (fadeBrightness * green) / 255;
                blue = (fadeBrightness * blue) / 255;

                if(ledObjects[ledNum].fadeState > 0){
                    ledObjects[ledNum].fadeState--;
                }else{
                    ledObjects[ledNum].status = LED_STATIS_OFF;
                }
            }
            
            RgbColor color = RgbColor(red, green, blue);
            neoPixelStrip.SetPixelColor(ledNum, color);
        }    
        neoPixelStrip.Show();
    }

    LedUnsetDirty();
}

void LedClear(uint8 hard){    
    for(uint8 ledNum = 0; ledNum < LED_COUNT; ledNum++){
        if(hard){
            LedSetStatus(ledNum, LED_STATIS_OFF);
        }else{
            LedSetStatus(ledNum, LED_STATIS_FADEOUT);
        }        
    }
}

uint8 LedMXtoNum(uint8 row, uint8 col){
    if(row < LED_MATRIX_ROWS && col < LED_MATRIX_COLS){
        return matrixIndex[row][col];
    }
    return 0;
}

void LedSetColor(uint8 ledNum, uint8 r, uint8 g, uint8 b){
    if(ledNum < LED_COUNT){
        if( ledObjects[ledNum].r != r ||
            ledObjects[ledNum].g != g ||
            ledObjects[ledNum].b != b ){
            LedSetDirty();
        }

        ledObjects[ledNum].r = r;
        ledObjects[ledNum].g = g;
        ledObjects[ledNum].b = b;
    }
}

void LedSetColorMatrix(uint8 row, uint8 col, uint8 r, uint8 g, uint8 b){
    if(row < LED_MATRIX_ROWS && col < LED_MATRIX_COLS){
        uint8 ledNum = LedMXtoNum(row,col);
        LedSetColor(ledNum, r, g, b);
    }
}

void LedSetColorMinute(uint8 min, uint8 r, uint8 g, uint8 b){
    if(min < LED_DOTS){
        uint8 ledNum = dotsIndex[min];
        LedSetColor(ledNum, r, g, b);
    }
}

void LedSetStatus(uint8 ledNum, uint8 status){
    if(ledNum < LED_COUNT){
        if(status == LED_STATIS_OFF){
            ledObjects[ledNum].fadeState = 0;
        }
        if(status == LED_STATIS_ON){
            ledObjects[ledNum].fadeState = LED_MAX_FADE_STEPS-1;
        }

        if(ledObjects[ledNum].status != status){
            LedSetDirty();
        }

        ledObjects[ledNum].status = status;        
    }    
}

void LedSetStatusMatrix(uint8 row, uint8 col, uint8 status){
    if(row < LED_MATRIX_ROWS && col < LED_MATRIX_COLS){
        uint8 ledNum = LedMXtoNum(row,col);
        LedSetStatus(ledNum, status);
    }
}

void LedSetStatusMinute(uint8 min, uint8 status){
    if(min < LED_DOTS){
        uint8 ledNum = dotsIndex[min];
        LedSetStatus(ledNum, status);
    }
}

uint8 LedGetStatus(uint8 ledNum){
    if(ledNum < LED_COUNT){
        return ledObjects[ledNum].status;
    }
    return LED_STATIS_UNKNOWN;
}


uint8 LedGetStatusMatrix(uint8 row, uint8 col){
    if(row < LED_MATRIX_ROWS && col < LED_MATRIX_COLS){
        uint8 ledNum = LedMXtoNum(row,col);
        return LedGetStatus(ledNum);
    }
    return LED_STATIS_UNKNOWN;
}


void LedUnsetDirty(){
    uiDirty = 0;
}

void LedSetDirty(){
    uiDirty = 1;
}


uint8 LedIsDirty(){
    if(uiDirty){
        return uiDirty;
    }else{
        uint8 loopDirty = 0;
        for(uint8 ledNum = 0; ledNum < LED_COUNT; ledNum++){
            if(loopDirty == 1){
                continue;
            }

            if(ledObjects[ledNum].status == LED_STATIS_FADEIN || ledObjects[ledNum].status == LED_STATIS_FADEOUT) {
                loopDirty = 1;
            } 
        }
        return loopDirty;
    }
    //TODO general brigthness && ldr change
}

