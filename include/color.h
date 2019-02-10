#ifndef COLOR_EFFECTS_H_
#define COLOR_EFFECTS_H_

#include <Ticker.h>
#include "leds.h"

struct ColorObject {
    uint8 r = 0;
    uint8 g = 0;
    uint8 b = 0;    
};

#define COLOR_CIRCLE_MAX               360

#define COLOR_MODE_PLAIN               0
#define COLOR_MODE_RAINBOW_SERPENTINE  1
#define COLOR_MODE_RAINBOW_VERTI       2
#define COLOR_MODE_RAINBOW_VERTI_I     3
#define COLOR_MODE_RAINBOW_HORI        4
#define COLOR_MODE_RAINBOW_HORI_I      5
#define COLOR_MODE_COLOR_CHANGE        6

extern void ColorInit();

extern void ColorTick();

extern void ColorUpdate();

extern void ColorSetMode(uint8 mode);

extern ColorObject hsv_to_rgb (uint8 h,uint8 s,uint8 v);

 

#endif