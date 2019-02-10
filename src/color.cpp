#include "color.h"

static uint16 colorCirclePosition    = 0;

static uint8  colorMode              = COLOR_MODE_RAINBOW_VERTI; //TODO aus config
static uint8  colorRaimbowRotate     = 1;      //TODO aus config
static uint32 colorCircleDuration    = 600000; //TODO aus config (seconds 60-600) 
static uint8  colorPlainRed          = 128;    //TODO aus config
static uint8  colorPlainGreen        = 255;    //TODO aus config
static uint8  colorPlainBlue         = 0;      //TODO aus config

static Ticker ColorTimer(ColorUpdate, colorCircleDuration / 360); 

void ColorInit(){ 
    ColorTimer.start();
    ColorUpdate();
}

void ColorTick(){
    ColorTimer.update();
}

void ColorUpdate(){
    //Farbrad weiter drehen
    colorCirclePosition++;
    if(colorCirclePosition > COLOR_CIRCLE_MAX){
        colorCirclePosition = 0;
    }

    if(colorMode == COLOR_MODE_PLAIN){
        for(uint8 ledNum = 0; ledNum < LED_COUNT; ledNum++){            
            LedSetColor(ledNum, colorPlainRed, colorPlainGreen, colorPlainBlue);
        }
    }

    if(colorMode == COLOR_MODE_COLOR_CHANGE){
        // Fullscreen color change
        for(uint8 ledNum = 0; ledNum < LED_COUNT; ledNum++){
            ColorObject rgb = hsv_to_rgb(colorCirclePosition,255,255);
            LedSetColor(ledNum, rgb.r, rgb.g, rgb.b);
        }
    }

    if(colorMode == COLOR_MODE_RAINBOW_SERPENTINE){
        uint16 locColorCircle = (colorRaimbowRotate == 1) ? colorCirclePosition : 0;
        for(uint8 ledNum = 0; ledNum < LED_COUNT; ledNum++){
            locColorCircle = locColorCircle + (COLOR_CIRCLE_MAX / (LED_COUNT - 1));
            if(locColorCircle > COLOR_CIRCLE_MAX){
                locColorCircle = locColorCircle - COLOR_CIRCLE_MAX;
            }
            ColorObject rgb = hsv_to_rgb(locColorCircle,255,255);
            LedSetColor(ledNum, rgb.r, rgb.g, rgb.b);
        }
    } 

    if(colorMode == COLOR_MODE_RAINBOW_HORI || colorMode == COLOR_MODE_RAINBOW_HORI_I){
        uint16 locColorCircle = (colorRaimbowRotate == 1) ? colorCirclePosition : 0;
        for(uint8 col = 0; col < LED_MATRIX_COLS; col++){
            locColorCircle = locColorCircle + (COLOR_CIRCLE_MAX / (LED_MATRIX_COLS - 1));
            if(locColorCircle > COLOR_CIRCLE_MAX){
                locColorCircle = locColorCircle - COLOR_CIRCLE_MAX;
            }

            ColorObject rgb = hsv_to_rgb(locColorCircle,255,255);
            for(uint8 row = 0; row < LED_MATRIX_ROWS; row++){                
                if(colorMode == COLOR_MODE_RAINBOW_HORI_I){
                    LedSetColorMatrix(row,(LED_MATRIX_COLS-1) - col,rgb.r, rgb.g, rgb.b);    
                }else{
                    LedSetColorMatrix(row,col,rgb.r, rgb.g, rgb.b);
                }
            }
        }
        LedSetColorMinute(0,255,255,255);
        LedSetColorMinute(1,255,255,255);
        LedSetColorMinute(2,255,255,255);
        LedSetColorMinute(3,255,255,255);
    }
    
    if(colorMode == COLOR_MODE_RAINBOW_VERTI || colorMode == COLOR_MODE_RAINBOW_VERTI_I){
        uint16 locColorCircle = (colorRaimbowRotate == 1) ? colorCirclePosition : 0;
        for(uint8 row = 0; row < LED_MATRIX_ROWS; row++){                
            locColorCircle = locColorCircle + (COLOR_CIRCLE_MAX / (LED_MATRIX_ROWS - 1));
            if(locColorCircle > COLOR_CIRCLE_MAX){
                locColorCircle = locColorCircle - COLOR_CIRCLE_MAX;
            }

            ColorObject rgb = hsv_to_rgb(locColorCircle,255,255);
            for(uint8 col = 0; col < LED_MATRIX_COLS; col++){
                if(colorMode == COLOR_MODE_RAINBOW_VERTI_I){
                    LedSetColorMatrix((LED_MATRIX_ROWS-1) - row,col,rgb.r, rgb.g, rgb.b);    
                }else{
                    LedSetColorMatrix(row,col,rgb.r, rgb.g, rgb.b);
                }
            }
        }
        LedSetColorMinute(0,255,255,255);
        LedSetColorMinute(1,255,255,255);
        LedSetColorMinute(2,255,255,255);
        LedSetColorMinute(3,255,255,255);
    }
}

void ColorSetMode(uint8 mode){
    colorMode = mode;
}

ColorObject hsv_to_rgb (uint8 h,uint8 s,uint8 v){
    unsigned char diff;
    uint16 r = 0, g = 0 ,b = 0;
    
    //Winkel im Farbkeis 0 - 360 in 1 Grad Schritten
    //h = (englisch hue) Farbwert
    //1 Grad Schrittweite, 4.25 Steigung pro Schritt bei 60 Grad

    if(h<61){
        r = 255;
        b = 0;
        g = (425 * h) / 100;
    }else if(h < 121){
        g = 255;
        b = 0;
        r = 255 - ((425 * (h-60))/100);
    }else if(h < 181){
        r = 0;
        g = 255;
        b = (425 * (h-120))/100;
    }else if(h < 241){
        r = 0;
        b = 255;
        g = 255 - ((425 * (h-180))/100);
    }else if(h < 301){
        g = 0;
        b = 255;
        r = (425 * (h-240))/100;
    }else if(h< 361){
        r = 255;
        g = 0;
        b = 255 - ((425 * (h-300))/100);
    }   
        
    //Berechnung der Farbsättigung
    //s = (englisch saturation) Farbsättigung
    s = 255 - s; //Kehrwert berechnen
    diff = ((255 - r) * s)/255;
    r = r + diff;
    diff = ((255 - g) * s)/255;
    g = g + diff;
    diff = ((255 - b) * s)/255;
    b = b + diff;
        
    //Berechnung der Dunkelstufe
    //v = (englisch value) Wert Dunkelstufe einfacher Dreisatz 0..100%
    r = (r * v)/255;   
    g = (g * v)/255;     
    b = (b * v)/255;   

    ColorObject color;
    
    color.r = r;
    color.g = g;
    color.b = b;

    return color;  
}