#ifndef TIMENTP_H_
#define TIMENTP_H_

#include <WiFiUdp.h>
#include <TimeLib.h>
#include <TimeZone.h>
#include "NTPClient.h"


extern void TimeInit();
extern void TimeTick();

extern uint8    TimeSeconds();
extern uint8    TimeMinutes();
extern uint8    TimeHours();
extern uint8    TimeDay();
extern uint8    TimeMonth();
extern uint16   TimeYear();

extern String TimeformatedDateTime();
extern String TimeformatedTime();

#endif