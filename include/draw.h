#ifndef DRAW_H_
#define DRAW_H_

#include <Ticker.h>
#include "timeNTP.h"
#include "font.h"
#include "leds.h"

#define DRAW_MODE_CLOCK           0
#define DRAW_MODE_SECONDS         1
#define DRAW_MODE_TEMP            2

#define DRAW_FONT_HEIGTH          7
#define DRAW_FONT_WIDTH           5

#define DRAW_FONT_XPOS1           0
#define DRAW_FONT_XPOS2           LED_MATRIX_COLS - DRAW_FONT_WIDTH
    
#define DRAW_FONT_YPOS_TOP        0    
#define DRAW_FONT_YPOS_CENTER     (LED_MATRIX_ROWS - DRAW_FONT_HEIGTH) / 2    
#define DRAW_FONT_YPOS_BOTTOM     LED_MATRIX_ROWS - DRAW_FONT_HEIGTH    
    
#define DRAW_CLOCK_REGION_WEST    0
#define DRAW_CLOCK_REGION_OST     1
#define DRAW_CLOCK_REGION_POTT    2 

#define DRAW_CLOCK_ITIS_OFF       0
#define DRAW_CLOCK_ITIS_HOURNHALF 1
#define DRAW_CLOCK_ITIS_PERMA     2

extern void DrawInit();

extern void DrawTick();

extern void DrawUpdate();

extern void DrawUpdateClock(uint8 hour,uint8 minutes);

extern void DrawUpdateSeconds(uint8 seconds);
extern void DrawUpdateTemp(uint8 temperature);

#endif