#ifndef TIMENTP_H_
#define TIMENTP_H_

#include <WiFiUdp.h>
#include <NTP.h>


extern void TimeInit();
extern void TimeTick();

uint8    TimeSeconds();
uint8    TimeMinutes();
uint8    TimeHours();
uint8    TimeDay();
uint8    TimeMonth();
uint16   TimeYear();

#endif