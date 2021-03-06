#include "draw.h"
#include "settings.h"


//Worker Vars
static uint32 lastSettingsChecksum       = 0;

static uint8 drawClockLastSeconds       = 0;
static uint8 drawClockLastMinutes       = 0;
static uint8 drawClockLastHour          = 0;

static uint8 drawLastTimoutCounter      = 0;

static uint8 drawTextCurrChar           = 0;
static int8  drawTextCurrPixel          = 0;

static uint8 drawLastDrawMode           = 0;


static Ticker DrawTimer(DrawUpdate, 1000);  

void DrawInit(){
    DrawTimer.start();        
    DrawUpdate();

    //Initital LED drawing
    drawFontAt('W',DRAW_FONT_XPOS_CENTER,DRAW_FONT_YPOS_CENTER,1);    
    LedSetMinDot(0,1);
    LedSetMinDot(1,1);
    LedSetMinDot(2,1);
    LedSetMinDot(3,1);

    LedUpdate();
}

void DrawTick(){
    DrawTimer.update();
}

void DrawUpdate(){
    uint8_t forceUpdate = 0;
    if(lastSettingsChecksum != SettingsGetChecksum()){
        forceUpdate = 1;
        lastSettingsChecksum = SettingsGetChecksum();
    }

    if(settings.d_mode == DRAW_MODE_CLOCK){
        DrawTimer.interval(1000);
        drawLastDrawMode = settings.d_mode;
        if(TimeHours() != drawClockLastHour || TimeMinutes() != drawClockLastMinutes || forceUpdate == 1){   
            WebLogDebug("TIME: " + String(TimeHours()) + ":" + String(TimeMinutes()));              
            DrawUpdateClock(TimeHours(), TimeMinutes());
        }
    } else if(settings.d_mode == DRAW_MODE_SECONDS){
        DrawTimer.interval(1000);
        drawLastDrawMode = settings.d_mode;
        if(TimeSeconds() != drawClockLastSeconds || forceUpdate == 1){
            WebLogDebug("SEC: " + String(TimeSeconds()));
            DrawUpdateSeconds(TimeSeconds());
        }
    } else if(settings.d_mode == DRAW_MODE_TEMP){
        DrawTimer.interval(1000);
        
        if(drawLastTimoutCounter <= settings.d_text_timeout){            
            DrawUpdateTemp(settings.d_temperatur);
            drawLastTimoutCounter++;
        }else{
            WebLogDebug("TEMP SHOW DONE");              
            settings.d_mode = drawLastDrawMode;            
            drawLastTimoutCounter = 0;
        }        
    } else if(settings.d_mode == DRAW_MODE_TEXT){
        DrawTimer.interval(settings.d_text_speed * 50);
        
        String text = String(settings.d_text);
        uint8_t charCount = text.length();        

        if(drawTextCurrChar + 2 < charCount){
            //####### more than 2 chars will be scrolled
            uint8_t char1 = text.charAt(drawTextCurrChar);
            uint8_t char2 = text.charAt(drawTextCurrChar + 1); 
            uint8_t char3 = text.charAt(drawTextCurrChar + 2);
            
            LedClear(1);            
            drawFontAt(char1,drawTextCurrPixel                          ,DRAW_FONT_YPOS_CENTER,1);     
            drawFontAt(char2,drawTextCurrPixel + DRAW_FONT_WIDTH + 1    ,DRAW_FONT_YPOS_CENTER,1); 
            drawFontAt(char3,drawTextCurrPixel + (2*(DRAW_FONT_WIDTH + 1)),DRAW_FONT_YPOS_CENTER,1); 

            //one char width 
            uint8_t charWidth = DRAW_FONT_WIDTH;
            if(drawTextCurrChar + 2 == charCount - 1){
                //last char needs extra pixel at the end
                charWidth++;
            }

            if(drawTextCurrPixel + charWidth == 0){ // shift to left until width is reached than jump to next char anf go on
                drawTextCurrPixel = 0;
                drawTextCurrChar++;
            }else{
                drawTextCurrPixel--;
            }
        }else{
            //####### Done scrolling or text is shorter or equal to 2 chars
            if(charCount > 0 && charCount == 1){
                LedClear(1);
                drawFontAt(text.charAt(0) ,DRAW_FONT_XPOS_CENTER, DRAW_FONT_YPOS_CENTER,1);     
            }
            if(charCount > 0 && charCount == 2){
                LedClear(1);
                drawFontAt(text.charAt(0) ,DRAW_FONT_XPOS1, DRAW_FONT_YPOS_CENTER,1);     
                drawFontAt(text.charAt(1) ,DRAW_FONT_XPOS2, DRAW_FONT_YPOS_CENTER,1);     
            }
            //clear text and counter
            SettingsSetValue(D_TEXT_TAG,"");
            drawTextCurrChar = 0;   
            drawTextCurrPixel = 0;

            //set intervall to wait for timeout            
            DrawTimer.interval(settings.d_text_timeout * 1000);
            
            //switch back to last mode
            settings.d_mode = drawLastDrawMode;            
                     
            WebLogDebug("TEXT SHOW DONE");  
        }
    } else {
        //drawmode not valid set default:
        settings.d_mode = DRAW_MODE_CLOCK;
    }
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
void drawFontAt(uint8 character, int8 atCol, int8 atRow, uint8 hard){    
    uint8 mode = hard ? LED_STATIS_ON : LED_STATIS_FADEIN;
    for(uint8 fontCol=0; fontCol < DRAW_FONT_WIDTH;fontCol++){
        for(uint8 fontRow=0; fontRow < DRAW_FONT_HEIGTH; fontRow++){
            int8 row = atRow + fontRow;
            int8 col = atCol + fontCol;
            if(row >= 0 && col >= 0){
                if (font_7x5[character][fontCol] & (1 << fontRow)) {                  
                    LedSetStatusMatrix(row,col,mode);                
                }
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

void DrawUpdateTemp(int8 temperature){
    if(temperature < -99){
        temperature = -99;
    }
    if(temperature > 99){
        temperature = 99;        
    }

    LedClear(1);    
    if(temperature < 0){
        temperature = (temperature * -1);
        //minus 
        LedSetStatusMatrix(1, 0, 1);
        LedSetStatusMatrix(1, 1, 1);
        LedSetStatusMatrix(1, 2, 1);
        LedSetStatusMatrix(1, 3, 1);
    }
    
    if (temperature < 10){
        uint8 char1 = temperature + 48;        
        drawFontAt(char1,DRAW_FONT_XPOS_CENTER,DRAW_FONT_YPOS_BOTTOM,1);
    } else {
        uint8 char1 = temperature / 10;
        uint8 char2 = temperature % 10;
        drawFontAt(char1+48,DRAW_FONT_XPOS1,DRAW_FONT_YPOS_BOTTOM,1);
        drawFontAt(char2+48,DRAW_FONT_XPOS2,DRAW_FONT_YPOS_BOTTOM,1); 
    }

    //celsius Punkt
    LedSetMinDot(0,1);
}
