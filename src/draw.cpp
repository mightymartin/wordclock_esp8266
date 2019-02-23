#include "draw.h"
#include "settings.h"


//Worker Vars
static uint8 drawLastMode               = 255;

static uint8 drawClockLastSeconds       = 0;
static uint8 drawClockLastMinutes       = 0;
static uint8 drawClockLastHour          = 0;

static uint8 drawLastTemp               = 0;

static Ticker DrawTimer(DrawUpdate, 1000);  //TODO Fraktal for faster draw?

void DrawInit(){
    DrawTimer.start();
    DrawUpdate();
}

void DrawTick(){
    DrawTimer.update();
}

void DrawUpdate(){
    if(settings.d_mode == DRAW_MODE_CLOCK){
        if(TimeHours() != drawClockLastHour || TimeMinutes() != drawClockLastMinutes || settings.d_mode != drawLastMode){   
            WebLogDebug("TIME: " + String(TimeHours()) + ":" + String(TimeMinutes()));  
            
            WebLogDebug(SettingsToJson());

            DrawUpdateClock(TimeHours(), TimeMinutes());
        }
    } else if(settings.d_mode == DRAW_MODE_SECONDS){
        if(TimeSeconds() != drawClockLastSeconds || settings.d_mode != drawLastMode){
            WebLogDebug("SEC: " + String(TimeSeconds()));
            DrawUpdateSeconds(TimeSeconds());
        }
    } else if(settings.d_mode == DRAW_MODE_TEMP){
        if(21 != drawLastTemp || settings.d_mode != drawLastMode){            
            DrawUpdateTemp(21);
        }
    } else {
        //drawmode not valid set default:
        settings.d_mode = DRAW_MODE_CLOCK;
    }

    drawLastMode = settings.d_mode;
}

//#################
//## Uhr functions
//#################
void DrawUpdateClock(uint8 hour,uint8 minutes){
    drawClockLastHour  = hour;
    drawClockLastMinutes= minutes;
    uint8 onMode = !settings.d_clk_fade;
    
    //### 12H Mod
    if(hour>12) hour = hour - 12;
    if(hour==0) hour = 12;

    //### Clear
    LedClear(onMode);

    //### Startdraw
    if( (settings.d_clk_itis_mode == DRAW_CLOCK_ITIS_PERMA) || 
        (settings.d_clk_itis_mode == DRAW_CLOCK_ITIS_HOURNHALF && minutes >= 0 && minutes < 5) ||
        (settings.d_clk_itis_mode == DRAW_CLOCK_ITIS_HOURNHALF && minutes >= 30 && minutes < 35) ){
        LedSetEsIst(onMode);
    }

    if(minutes < 5){
        LedSetUhr(onMode);
    }else if(minutes < 10){
        LedSetFuenfMin(onMode);
        LedSetNach(onMode);
    }else if(minutes < 15){
        LedSetZehnMin(onMode);
        LedSetNach(onMode);
    }else if(minutes < 20){        
        LedSetViertelMin(onMode);        
        if(settings.d_clk_region != DRAW_CLOCK_REGION_OST){
            LedSetNach(onMode);
        }
    }else if(minutes < 25){
        if(settings.d_clk_region == DRAW_CLOCK_REGION_POTT){
            LedSetZwanzigMin(onMode);
            LedSetNach(onMode);
        }else{
            LedSetZehnMin(onMode);
            LedSetVor(onMode);
            LedSetHalbMin(onMode);
        }
    }else if(minutes < 30){
        LedSetFuenfMin(onMode);
        LedSetVor(onMode);
        LedSetHalbMin(onMode);
    }else if(minutes < 35){
        LedSetHalbMin(onMode);
    }else if(minutes < 40){
        LedSetFuenfMin(onMode);
        LedSetNach(onMode);
        LedSetHalbMin(onMode);
    }else if(minutes < 45){
        if(settings.d_clk_region == DRAW_CLOCK_REGION_POTT){
            LedSetZwanzigMin(onMode);
            LedSetVor(onMode);
        }else{
            LedSetZehnMin(onMode);
            LedSetNach(onMode);
            LedSetHalbMin(onMode);
        }
    }else if(minutes < 50){           
        if(settings.d_clk_region == DRAW_CLOCK_REGION_OST){
            LedSetDreiviertelMin(onMode);
        }else{
            LedSetViertelMin(onMode);     
            LedSetVor(onMode);
        }
    }else if(minutes < 55){
        LedSetZehnMin(onMode);
        LedSetVor(onMode);
    }else if(minutes < 60){
        LedSetFuenfMin(onMode);
        LedSetVor(onMode);
    }

    uint8 minuteDots = minutes % 5;
    for(uint8 i = 0; i < minuteDots; i++){
        LedSetMinDot(i,onMode);
    }

    //Stunden Shift je nach Regionslayout
    if(
        (settings.d_clk_region == DRAW_CLOCK_REGION_POTT && minutes >= 25)||
        (settings.d_clk_region == DRAW_CLOCK_REGION_WEST && minutes >= 20)||
        (settings.d_clk_region == DRAW_CLOCK_REGION_OST  && minutes >= 15)
      ){
        hour++;
        if(hour > 12){
            hour = 1;
        }
    }

    if(hour == 1){
        if(minutes < 5){
            LedSetEinHour(onMode);
        }else{
            LedSetEinsHour(onMode);
        }
    } else if(hour == 2){
        LedSetZweiHour(onMode);
    } else if(hour == 3){
        LedSetDreiHour(onMode);
    } else if(hour == 4){
        LedSetVierHour(onMode);
    } else if(hour == 5){
        LedSetFuenfHour(onMode);
    } else if(hour == 6){
        LedSetSechsHour(onMode);
    } else if(hour == 7){
        LedSetSiebenHour(onMode);
    } else if(hour == 8){
        LedSetAchtHour(onMode);
    } else if(hour == 9){
        LedSetNeunHour(onMode);
    } else if(hour == 10){
        LedSetZehnHour(onMode);
    } else if(hour == 11){
        LedSetElfHour(onMode);
    } else if(hour == 12){
        LedSetZwoelfHour(onMode);
    } 
}

//#################
//## text functions
//#################
void drawFontAt(uint8 character, uint8 atCol, uint8 atRow, uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    for(uint8 fontCol=0; fontCol < DRAW_FONT_WIDTH;fontCol++){
        for(uint8 fontRow=0; fontRow < DRAW_FONT_HEIGTH; fontRow++){
            uint8 row = atRow + fontRow;
            uint8 col = atCol + fontCol;
            if (font_7x5[character][fontCol] & (1 << fontRow)) {                  
                LedSetStatusMatrix(row,col,mode);                
            }
        }
    }
}

void DrawUpdateSeconds(uint8 seconds){
    drawClockLastSeconds = seconds;

    uint8 char1 = seconds / 10;
    uint8 char2 = seconds % 10;

    LedClear(1);

    drawFontAt(char1+48,DRAW_FONT_XPOS1,DRAW_FONT_YPOS_CENTER,1);
    drawFontAt(char2+48,DRAW_FONT_XPOS2,DRAW_FONT_YPOS_CENTER,1);        
} 

void DrawUpdateTemp(uint8 temperature){
    uint8 char1 = temperature / 10;
    uint8 char2 = temperature % 10;
    
    LedClear(1);

    drawFontAt(char1+48,DRAW_FONT_XPOS1,DRAW_FONT_YPOS_CENTER,1);
    drawFontAt(char2+48,DRAW_FONT_XPOS2,DRAW_FONT_YPOS_CENTER,1); 

    //celsius Punkt
    LedSetMinDot(0,1);
}
