#include "color.h"

static uint16 colorCirclePosition    = 0;

static uint8  colorMode              = COLOR_MODE_RAINBOW_VERTI; //TODO aus config
static uint8  colorRainbowRotate     = 1;      //TODO aus config
static uint32 colorCircleDuration    = 60000; //TODO aus config (seconds 60-600) 
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
    if(colorCirclePosition > COLOR_CIRCLE_STEPS - 1){
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
        uint16 locColorCircle = (colorRainbowRotate == 1) ? colorCirclePosition : 0;
        for(uint8 ledNum = 0; ledNum < LED_COUNT; ledNum++){
            locColorCircle = locColorCircle + (COLOR_CIRCLE_STEPS / (LED_COUNT - 1));
            if(locColorCircle > COLOR_CIRCLE_STEPS - 1){
                locColorCircle = locColorCircle - COLOR_CIRCLE_STEPS;
            }
            ColorObject rgb = hsv_to_rgb(locColorCircle,255,255);
            LedSetColor(ledNum, rgb.r, rgb.g, rgb.b);
        }
    } 

    if(colorMode == COLOR_MODE_RAINBOW_HORI || colorMode == COLOR_MODE_RAINBOW_HORI_I){
        uint16 locColorCircle = (colorRainbowRotate == 1) ? colorCirclePosition : 0;
        for(uint8 col = 0; col < LED_MATRIX_COLS; col++){
            locColorCircle = locColorCircle + (COLOR_CIRCLE_STEPS / (LED_MATRIX_COLS - 1));
            if(locColorCircle > COLOR_CIRCLE_STEPS - 1){
                locColorCircle = locColorCircle - COLOR_CIRCLE_STEPS;
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
        uint16 locColorCircle = (colorRainbowRotate == 1) ? colorCirclePosition : 0;
        for(uint8 row = 0; row < LED_MATRIX_ROWS; row++){                
            locColorCircle = locColorCircle + (COLOR_CIRCLE_STEPS / (LED_MATRIX_ROWS - 1));
            if(locColorCircle > COLOR_CIRCLE_STEPS - 1){
                locColorCircle = locColorCircle - COLOR_CIRCLE_STEPS;
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





ColorObject hsv_to_rgb(uint16 hue, uint16 sat, uint16 val) {
    /* 
     convert hue, saturation and brightness ( HSB/HSV ) to RGB         
    */

    uint16 r =val;
    uint16 g =val;
    uint16 b =val;
    uint16 base = ((255 - sat) * val)>>8;

    if (sat != 0) { // Acromatic color (gray). Hue doesn't mind.
        
        switch(hue/60) {
            case 0:
                r = val;
                g = (((val-base)*hue)/60)+base;
                b = base;
            break;

            case 1:
                r = (((val-base)*(60-(hue%60)))/60)+base;
                g = val;
                b = base;
            break;

            case 2:
                r = base;
                g = val;
                b = (((val-base)*(hue%60))/60)+base;
            break;

            case 3:
                r = base;
                g = (((val-base)*(60-(hue%60)))/60)+base;
                b = val;
            break;

            case 4:
                r = (((val-base)*(hue%60))/60)+base;
                g = base;
                b = val;
            break;

            case 5:
                r = val;
                g = base;
                b = (((val-base)*(60-(hue%60)))/60)+base;
            break;
        }
    }
    ColorObject color;
        
    color.r = r;
    color.g = g;
    color.b = b;

    return color; 
}