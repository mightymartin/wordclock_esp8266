#ifndef DRAW_H_
#define DRAW_H_

#include <Ticker.h>
#include "timeNTP.h"
#include "font.h"
#include "leds.h"

extern void DrawInit();

extern void DrawTick();

extern void DrawUpdate();

extern void DrawUpdateClock(uint8 hour,uint8 minutes);

extern void DrawUpdateSeconds(uint8 seconds);
extern void DrawUpdateTemp(uint8 temperature);

#endif