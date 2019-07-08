#ifndef LEDS_RADIG_H_
#define LEDS_RADIG_H_

#include "leds.h"

//###############
//## THX to DVoss @ www.ulrichradig.de/forum/  2019-06-01 
//##
//## ES_IST_FÜNF
//## ZEHNZWANZIG
//## DREIVIERTEL
//## __NACHVOR__  
//## HALB_ZWÖLF_
//## ZWEINSIEBEN
//## _DREI__FÜNF
//## ELFNEUNVIER
//## _ACHTZEHN__
//## _SECHS_UHR_
//###############

#define LED_MATRIX_ROWS 10
#define LED_MATRIX_COLS 11
#define LED_DOTS 4
#define LED_COUNT (LED_MATRIX_ROWS * LED_MATRIX_COLS) + LED_DOTS

const uint8 matrixIndex[LED_MATRIX_ROWS][LED_MATRIX_COLS] =         {
                                                                        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                                                        {21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11},
                                                                        {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32},
                                                                        {43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33},
                                                                        {44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54},
                                                                        {65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55},
                                                                        {66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76},
                                                                        {87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77},
                                                                        {88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98},
                                                                        {109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99}
                                                                    };

const uint8 dotsIndex[LED_DOTS] =           {
                                                110, 111, 112, 113
                                            };

//##############################
//## Define Methods
//##############################

//#### Fill Words
static inline void LedSetEsIst(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    //Es
    LedSetStatusMatrix(0, 0, mode);
    LedSetStatusMatrix(0, 1, mode);

    //Ist
    LedSetStatusMatrix(0, 3, mode);
    LedSetStatusMatrix(0, 4, mode);
    LedSetStatusMatrix(0, 5, mode);
}

static inline void LedSetUhr(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(9, 7, mode);
    LedSetStatusMatrix(9, 8, mode);
    LedSetStatusMatrix(9, 9, mode);
}

static inline void LedSetVor(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(3, 6, mode);
    LedSetStatusMatrix(3, 7, mode);
    LedSetStatusMatrix(3, 8, mode);
}

static inline void LedSetNach(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(3, 2, mode);
    LedSetStatusMatrix(3, 3, mode);
    LedSetStatusMatrix(3, 4, mode);
    LedSetStatusMatrix(3, 5, mode);
}

static inline void LedSetFunk(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(3, 0, mode);
    LedSetStatusMatrix(3, 1, mode);
    LedSetStatusMatrix(3, 9, mode);
    LedSetStatusMatrix(3, 10, mode);
}

//#### Minutes Words
static inline void LedSetFuenfMin(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(0, 7, mode);
    LedSetStatusMatrix(0, 8, mode);
    LedSetStatusMatrix(0, 9, mode);
    LedSetStatusMatrix(0, 10, mode);
}

static inline void LedSetZehnMin(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(1, 0, mode);
    LedSetStatusMatrix(1, 1, mode);
    LedSetStatusMatrix(1, 2, mode);
    LedSetStatusMatrix(1, 3, mode);
}

static inline void LedSetZwanzigMin(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(1, 4, mode);
    LedSetStatusMatrix(1, 5, mode);
    LedSetStatusMatrix(1, 6, mode);
    LedSetStatusMatrix(1, 7, mode);
    LedSetStatusMatrix(1, 8, mode);
    LedSetStatusMatrix(1, 9, mode);
    LedSetStatusMatrix(1, 10, mode);
}

static inline void LedSetViertelMin(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(2, 4, mode);
    LedSetStatusMatrix(2, 5, mode);
    LedSetStatusMatrix(2, 6, mode);
    LedSetStatusMatrix(2, 7, mode);
    LedSetStatusMatrix(2, 8, mode);
    LedSetStatusMatrix(2, 9, mode);
    LedSetStatusMatrix(2, 10, mode);
}

static inline void LedSetDreiviertelMin(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(2, 0, mode);
    LedSetStatusMatrix(2, 1, mode);
    LedSetStatusMatrix(2, 2, mode);
    LedSetStatusMatrix(2, 3, mode);
    LedSetViertelMin(hard);
}

static inline void LedSetHalbMin(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(4, 0, mode);
    LedSetStatusMatrix(4, 1, mode);
    LedSetStatusMatrix(4, 2, mode);
    LedSetStatusMatrix(4, 3, mode);
}

static inline void LedSetMinDot(uint8 dot, uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMinute(dot, mode);
}

//#### Hours Words
static inline void LedSetEinHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(5, 2, mode);
    LedSetStatusMatrix(5, 3, mode);
    LedSetStatusMatrix(5, 4, mode);
}

static inline void LedSetEinsHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetEinHour(mode);
    //s
    LedSetStatusMatrix(5, 5, mode);
}

static inline void LedSetZweiHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(5, 0, mode);
    LedSetStatusMatrix(5, 1, mode);
    LedSetStatusMatrix(5, 2, mode);
    LedSetStatusMatrix(5, 3, mode);
}

static inline void LedSetDreiHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(6, 1, mode);
    LedSetStatusMatrix(6, 2, mode);
    LedSetStatusMatrix(6, 3, mode);
    LedSetStatusMatrix(6, 4, mode);
}

static inline void LedSetVierHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(7, 7, mode);
    LedSetStatusMatrix(7, 8, mode);
    LedSetStatusMatrix(7, 9, mode);
    LedSetStatusMatrix(7, 10, mode);
}

static inline void LedSetFuenfHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(6, 7, mode);
    LedSetStatusMatrix(6, 8, mode);
    LedSetStatusMatrix(6, 9, mode);
    LedSetStatusMatrix(6, 10, mode);
}

static inline void LedSetSechsHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(9, 1, mode);
    LedSetStatusMatrix(9, 2, mode);
    LedSetStatusMatrix(9, 3, mode);
    LedSetStatusMatrix(9, 4, mode);
    LedSetStatusMatrix(9, 5, mode);
}

static inline void LedSetSiebenHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(5, 5, mode);
    LedSetStatusMatrix(5, 6, mode);
    LedSetStatusMatrix(5, 7, mode);
    LedSetStatusMatrix(5, 8, mode);
    LedSetStatusMatrix(5, 9, mode);
    LedSetStatusMatrix(5, 10, mode);
}

static inline void LedSetAchtHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(8, 1, mode);
    LedSetStatusMatrix(8, 2, mode);
    LedSetStatusMatrix(8, 3, mode);
    LedSetStatusMatrix(8, 4, mode);
}

static inline void LedSetNeunHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(7, 3, mode);
    LedSetStatusMatrix(7, 4, mode);
    LedSetStatusMatrix(7, 5, mode);
    LedSetStatusMatrix(7, 6, mode);
}

static inline void LedSetZehnHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(8, 5, mode);
    LedSetStatusMatrix(8, 6, mode);
    LedSetStatusMatrix(8, 7, mode);
    LedSetStatusMatrix(8, 8, mode);
}

static inline void LedSetElfHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(7, 0, mode);
    LedSetStatusMatrix(7, 1, mode);
    LedSetStatusMatrix(7, 2, mode);
}

static inline void LedSetZwoelfHour(uint8 hard){
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    LedSetStatusMatrix(4, 5, mode);
    LedSetStatusMatrix(4, 6, mode);
    LedSetStatusMatrix(4, 7, mode);
    LedSetStatusMatrix(4, 8, mode);
    LedSetStatusMatrix(4, 9, mode);
}
#endif