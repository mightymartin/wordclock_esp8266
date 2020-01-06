#include "website.h"

ESP8266WebServer *_server;

void WebsiteInit(ESP8266WebServer *server){
    _server = server;
    _server->on(REQ_START, WebsiteStartPage);
    _server->on(REQ_CONFIG, WebsiteConfigPage);    
    _server->on(REQ_CONF_NETWORK, WebsiteNetworkConfigPage);    
    _server->on(REQ_CONF_MQTT, WebsiteMQTTConfigPage);    
    _server->on(REQ_CONF_LDR, WebsiteLDRConfigPage);  
    _server->on(REQ_CONF_MISC, WebsiteMiscConfigPage);    
    _server->on(REQ_MODES, WebsiteModesPage);    
    _server->on(REQ_CONF_MODES, WebsiteModesConfPage);      
    _server->on(REQ_CONF_DISPLAY, WebsiteDisplayConfPage);   
    _server->on(REQ_ACTIONS, WebsiteUserActionPage);          
    _server->on(REQ_INFO, WebsiteInfoPage);
    _server->on(REQ_FACTORY_RESET, WebsiteFactoryResetPage);  
    _server->on(REQ_OTA_SELECT, WebsiteFirmwareUpdate);  
    _server->on(REQ_CONSOLE, WebsiteConsolePage);      
}

void WebsideApplyArgs(){
    for (int i = 0; i < _server->args(); i++) {
        SettingsSetValue(_server->argName(i),_server->arg(i));
    }
}

void WebsiteAction(){
    if (_server->hasArg("ACTION") == true){
        String message = "";
        uint8 reqReboot = 0;
        if(_server->arg("ACTION").equalsIgnoreCase("ONOFF")){
            SettingsSetValue(U_ONOFF_TAG,String(!settings.u_DISPLAYON));
        } else if(_server->arg("ACTION").equalsIgnoreCase("SETTEXT")){            
            WebsideApplyArgs();             
            SettingsSetValue(D_MODE_TAG,String(DRAW_MODE_TEXT)); 
        } else if(_server->arg("ACTION").equalsIgnoreCase("SETTEMP")){
            WebsideApplyArgs();
            SettingsSetValue(D_MODE_TAG,String(DRAW_MODE_TEMP)); 
        } else if(_server->arg("ACTION").equalsIgnoreCase("SAVE")){
            WebsideApplyArgs();
            SettingsWrite();  
        } else if(_server->arg("ACTION").equalsIgnoreCase("SAVER")){
            WebsideApplyArgs();
            SettingsWrite();            
            reqReboot = 1;
            message = "Settings saved -> Reboot";
        } else if(_server->arg("ACTION").equalsIgnoreCase("APPLY")){
            WebsideApplyArgs();            
        } else if(_server->arg("ACTION").equalsIgnoreCase("REBOOT")){            
            reqReboot = 1;
            message = "Manual Reboot";
        } else if(_server->arg("ACTION").equalsIgnoreCase("RESETS")){
            SettingsClear();                  
            reqReboot = 1;
            message = "Settings Reset";
        } else if(_server->arg("ACTION").equalsIgnoreCase("RESETW")){
            SettingsWifiReset();                  
            reqReboot = 1;
            message = "Wifi Reset; Wifimanager enabled";
        }

        if(reqReboot > 0 ){
            //Seite muss neu geladen werden. Nach X sekunden wird redirected
            String page = FPSTR(SITE_HEAD);    
            page += FPSTR(SITE_BGN); 

            page.replace("{phead}", message);    
            page.replace("{pcat}" , "Restarting...");
    
            page += FPSTR(SITE_RELOAD_WAIT); 
            page += FPSTR(SITE_END); 

            WebsiteSend(page);  
            
            SettingsSoftRestart();           
        }
    }
}

void WebsiteStartPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Home"));

    if(settings.u_DISPLAYON){
        page += FPSTR(SITE_HREF_EXT);  
        page.replace("{tit}", F("ON"));
        page.replace("{id}",  F("ACTION"));
        page.replace("{val}", F("ONOFF"));
        page.replace("{col}", F("bgrn"));
        page.replace("{dest}", REQ_START);
    }else{
        page += FPSTR(SITE_HREF_EXT);  
        page.replace("{tit}", F("OFF"));
        page.replace("{id}",  F("ACTION"));
        page.replace("{val}", F("ONOFF"));
        page.replace("{col}", F("bred"));
        page.replace("{dest}", REQ_START);
    }

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Modes"));
    page.replace("{dest}", REQ_MODES);

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Modes Settings"));
    page.replace("{dest}", REQ_CONF_MODES);

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Display Settings"));
    page.replace("{dest}", REQ_CONF_DISPLAY);

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Actions"));
    page.replace("{dest}", REQ_ACTIONS);

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Infos"));
    page.replace("{dest}", REQ_INFO);
    
    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Console"));
    page.replace("{dest}", REQ_CONSOLE);

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Config"));
    page.replace("{dest}", REQ_CONFIG);

    page += FPSTR(SITE_END); 
    
    WebsiteSend(page);    
}

void WebsiteConsolePage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN_FULL); 
    page.replace("{phead}", "Console");    

    page += FPSTR(SITE_CONSOLE);
    
    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_START);

    page += FPSTR(SITE_END_FULL); 

    WebsiteSend(page);  
}

void WebsiteFirmwareUpdate(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Fimrwareupdate"));

    page += FPSTR(SITE_UPDATE_FORM);
    page.replace("{dest}" , REQ_OTA);

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_CONFIG);

    page += FPSTR(SITE_END); 
    
    WebsiteSend(page); 
    
}

void WebsiteFactoryResetPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Factory Reset"));

    page += FPSTR(SITE_FORM_BGN);
    page.replace("{dest}", REQ_CONFIG);

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Abort"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F(""));
    page.replace("{col}", F("bgrn"));

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Reset Settings"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("RESETS"));
    page.replace("{col}", F("bred"));

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Reset WiFi"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("RESETW"));
    page.replace("{col}", F("bred"));

    page += FPSTR(SITE_FORM_END);

    page += FPSTR(SITE_END); 
    
    WebsiteSend(page);  
}

void WebsiteInfoPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Infos"));

    page += FPSTR(SITE_DL_BGN);  

    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("Firmware Version"));
    page.replace("{val}", String(settings.version) );

    page += F("<br/>"); 
    page += F("<br/>"); 

    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("Chip ID"));
    page.replace("{val}", String(ESP.getChipId()) );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("Flash Chip ID"));
    page.replace("{val}", String(ESP.getFlashChipId()) );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("IDE Flash Size"));
    page.replace("{val}", String(ESP.getFlashChipSize() / 1024)+F("kB"));
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("Real Flash Size"));
    page.replace("{val}", String(ESP.getFlashChipRealSize() / 1024)+F("kB") );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("Program Size"));
    page.replace("{val}", String(ESP.getSketchSize() / 1024)+F("kB") );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("Free Program Space"));
    page.replace("{val}", String(ESP.getFreeSketchSpace() / 1024)+F("kB") );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("Free Memory"));
    page.replace("{val}", String(ESP.getFreeHeap() / 1024)+F("kB") );

    if(settings.u_MQTT){
        page += F("<br/>");  
    
        page += FPSTR(SITE_DL_LINE);  
        page.replace("{tit}", F("MQTT Status"));
        page.replace("{val}", MQTTStatus()  );

        page += FPSTR(SITE_DL_LINE);  
        page.replace("{tit}", F("MQTT state topic"));
        page.replace("{val}", stateTopic );

        page += FPSTR(SITE_DL_LINE);  
        page.replace("{tit}", F("MQTT cmd topic"));
        page.replace("{val}", cmdTopic );    
    }
    

    page += F("<br/>");  

    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("CPU Freq"));
    page.replace("{val}", String(ESP.getCpuFreqMHz())+F("Mhz")  );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("Restart Reason"));
    page.replace("{val}", ESP.getResetReason() );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("Core"));
    page.replace("{val}", ESP.getCoreVersion() );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("SDK"));
    page.replace("{val}", ESP.getSdkVersion() );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("Time"));
    page.replace("{val}", String(TimeformatedDateTime()) );
    
    page += F("<br/>");  

    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("IP"));
    page.replace("{val}", WiFi.localIP().toString() );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("MASK"));
    page.replace("{val}", WiFi.subnetMask().toString() );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("GATEWAY"));
    page.replace("{val}", WiFi.gatewayIP().toString() );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("DNS"));
    page.replace("{val}", WiFi.dnsIP().toString() );
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("MAC"));
    page.replace("{val}", WiFi.macAddress());
    page += FPSTR(SITE_DL_LINE);  
    page.replace("{tit}", F("SSID"));
    page.replace("{val}", WiFi.SSID());
    
    page += FPSTR(SITE_DL_END);  
    
    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_START);

    page += FPSTR(SITE_END); 
    
    WebsiteSend(page);    
}

void WebsiteModesPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Modes"));
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_MODES);

    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("Display Mode"));
    page.replace("{id}",  F(D_MODE_TAG)); 
    page.replace("{val}",  String(settings.d_mode));     
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Clock"));
    page.replace("{oval}", String(DRAW_MODE_CLOCK));
    page.replace("{oopt}", (settings.d_mode == DRAW_MODE_CLOCK) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Seconds"));
    page.replace("{oval}", String(DRAW_MODE_SECONDS));
    page.replace("{oopt}", (settings.d_mode == DRAW_MODE_SECONDS) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Temperature"));
    page.replace("{oval}", String(DRAW_MODE_TEMP));
    page.replace("{oopt}", (settings.d_mode == DRAW_MODE_TEMP) ? F("selected disabled") : F("disabled"));    
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Text"));
    page.replace("{oval}", String(DRAW_MODE_TEXT));
    page.replace("{oopt}", (settings.d_mode == DRAW_MODE_TEXT) ? F("selected disabled") : F("disabled"));    

    page += FPSTR(SITE_INP_CBX_END); 

    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("Colormode"));
    page.replace("{id}",  F(C_MODE_TAG)); 
    page.replace("{val}",  String(settings.c_mode));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Plain"));
    page.replace("{oval}", String(COLOR_MODE_PLAIN));
    page.replace("{oopt}", (settings.c_mode == COLOR_MODE_PLAIN) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Rainbow Serpentine"));
    page.replace("{oval}", String(COLOR_MODE_RAINBOW_SERPENTINE));
    page.replace("{oopt}", (settings.c_mode == COLOR_MODE_RAINBOW_SERPENTINE) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Rainbow N->S"));
    page.replace("{oval}", String(COLOR_MODE_RAINBOW_VERTI));
    page.replace("{oopt}", (settings.c_mode == COLOR_MODE_RAINBOW_VERTI) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Rainbow S->N"));
    page.replace("{oval}", String(COLOR_MODE_RAINBOW_VERTI_I));
    page.replace("{oopt}", (settings.c_mode == COLOR_MODE_RAINBOW_VERTI_I) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Rainbow E->W"));
    page.replace("{oval}", String(COLOR_MODE_RAINBOW_HORI));
    page.replace("{oopt}", (settings.c_mode == COLOR_MODE_RAINBOW_HORI) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Rainbow W->E"));
    page.replace("{oval}", String(COLOR_MODE_RAINBOW_HORI_I));
    page.replace("{oopt}", (settings.c_mode == COLOR_MODE_RAINBOW_HORI_I) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Color Change"));
    page.replace("{oval}", String(COLOR_MODE_COLOR_CHANGE));
    page.replace("{oopt}", (settings.c_mode == COLOR_MODE_COLOR_CHANGE) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_END);

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Apply"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("APPLY"));
    page.replace("{col}", F("bgrn"));

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Save & Apply"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("SAVE"));
    page.replace("{col}", F("bred"));

    page += FPSTR(SITE_FORM_END); 

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_START);

    page += FPSTR(SITE_END); 
     
    WebsiteSend(page); 
}

void WebsiteModesConfPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Modes Settings"));
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_CONF_MODES);

    if(settings.d_mode == DRAW_MODE_CLOCK){
        page += FPSTR(SITE_INP_CBX_BGN);  
        page.replace("{tit}", F("Clock - Region"));
        page.replace("{id}",  F(D_CLK_REGION_TAG)); 
        page.replace("{val}",  String(settings.d_clk_region));     
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("West Germany"));
        page.replace("{oval}", String(DRAW_CLOCK_REGION_WEST));
        page.replace("{oopt}", (settings.d_clk_region == DRAW_CLOCK_REGION_WEST) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("East Germany"));
        page.replace("{oval}", String(DRAW_CLOCK_REGION_OST));
        page.replace("{oopt}", (settings.d_clk_region == DRAW_CLOCK_REGION_OST) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("Rhine-Ruhr"));
        page.replace("{oval}", String(DRAW_CLOCK_REGION_POTT));
        page.replace("{oopt}", (settings.d_clk_region == DRAW_CLOCK_REGION_POTT) ? F("selected") : F(""));    
        page += FPSTR(SITE_INP_CBX_END); 

        page += FPSTR(SITE_INP_CBX_BGN);  
        page.replace("{tit}", F("Clock - IT IS mode"));
        page.replace("{id}",  F(D_CLK_ITIS_MODE_TAG)); 
        page.replace("{val}",  String(settings.d_clk_itis_mode)); 
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("always off"));
        page.replace("{oval}", String(DRAW_CLOCK_ITIS_OFF));
        page.replace("{oopt}", (settings.d_clk_itis_mode == DRAW_CLOCK_ITIS_OFF) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("full/half hour"));
        page.replace("{oval}", String(DRAW_CLOCK_ITIS_HOURNHALF));
        page.replace("{oopt}", (settings.d_clk_itis_mode == DRAW_CLOCK_ITIS_HOURNHALF) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("always on"));
        page.replace("{oval}", String(DRAW_CLOCK_ITIS_PERMA));
        page.replace("{oopt}", (settings.d_clk_itis_mode == DRAW_CLOCK_ITIS_PERMA) ? F("selected") : F(""));    
        page += FPSTR(SITE_INP_CBX_END); 

        page += FPSTR(SITE_INP_CBX_BGN);  
        page.replace("{tit}", F("Clock - Pixel fading"));
        page.replace("{id}",  F(D_CLK_FADE_TAG)); 
        page.replace("{val}",  String(settings.d_clk_fade)); 
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("yes"));
        page.replace("{oval}", F("1"));
        page.replace("{oopt}", (settings.d_clk_fade == 1) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("no"));
        page.replace("{oval}", F("0"));
        page.replace("{oopt}", (settings.d_clk_fade == 0) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_END); 

        page += F("<br/>");  
    }

    if( settings.c_mode != COLOR_MODE_COLOR_CHANGE && settings.c_mode != COLOR_MODE_PLAIN ){
        page += FPSTR(SITE_INP_CBX_BGN);  
        page.replace("{tit}", F("Color - Rotate"));
        page.replace("{id}",  F(C_HUE_ROTATE_RB_TAG)); 
        page.replace("{val}",  String(settings.c_hue_rotate_rb));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("yes"));
        page.replace("{oval}", F("1"));
        page.replace("{oopt}", (settings.c_hue_rotate_rb == 1) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("no"));
        page.replace("{oval}", F("0"));
        page.replace("{oopt}", (settings.c_hue_rotate_rb == 0) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_END); 
    }

    if( settings.c_mode == COLOR_MODE_COLOR_CHANGE || (settings.c_mode != COLOR_MODE_COLOR_CHANGE && settings.c_mode != COLOR_MODE_PLAIN && settings.c_hue_rotate_rb == 1) ){
        page += FPSTR(SITE_INP_N);  
        page.replace("{tit}", F("Color - Rotate Duration (s)"));
        page.replace("{id}",  F(C_HUE_ROTATE_DURATION_TAG)); 
        page.replace("{val}", String(settings.c_hue_rotate_duration));
        page.replace("{min}", F("30000"));
        page.replace("{max}", F("600000"));
        page.replace("{step}", F("1000"));
    }

    if( settings.c_mode == COLOR_MODE_PLAIN){
        page += FPSTR(SITE_INP_NR);  
        page.replace("{tit}", F("Color - Red"));
        page.replace("{id}",  F(C_PLAIN_RED_TAG)); 
        page.replace("{val}", String(settings.c_plain_red));
        page.replace("{min}", F("0"));
        page.replace("{max}", F("255"));
        page.replace("{step}", F("1"));

        page += FPSTR(SITE_INP_NR);  
        page.replace("{tit}", F("Color - Green"));
        page.replace("{id}",  F(C_PLAIN_GREEN_TAG)); 
        page.replace("{val}", String(settings.c_plain_green));
        page.replace("{min}", F("0"));
        page.replace("{max}", F("255"));
        page.replace("{step}", F("1"));

        page += FPSTR(SITE_INP_NR);  
        page.replace("{tit}", F("Color - Blue"));
        page.replace("{id}",  F(C_PLAIN_BLUE_TAG)); 
        page.replace("{val}", String(settings.c_plain_blue));
        page.replace("{min}", F("0"));
        page.replace("{max}", F("255"));
        page.replace("{step}", F("1"));
    }

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Apply"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("APPLY"));
    page.replace("{col}", F("bgrn"));

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Save & Apply"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("SAVE"));
    page.replace("{col}", F("bred"));

    page += FPSTR(SITE_FORM_END); 

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_START);

    page += FPSTR(SITE_END); 
     
    WebsiteSend(page); 
}

void WebsiteDisplayConfPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Display Settings"));
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_CONF_DISPLAY);

    page += FPSTR(SITE_INP_NR);  
    page.replace("{tit}", F("Textspeed (x50ms)"));
    page.replace("{id}",  F(D_TEXT_SPEED_TAG)); 
    page.replace("{val}", String(settings.d_text_speed));
    page.replace("{min}", F("1"));
    page.replace("{max}", F("10"));
    page.replace("{step}", F("1"));

    page += FPSTR(SITE_INP_NR);  
    page.replace("{tit}", F("Text Timeout (s)"));
    page.replace("{id}",  F(D_TEXT_TIMEOUT_TAG)); 
    page.replace("{val}", String(settings.d_text_timeout));
    page.replace("{min}", F("1"));
    page.replace("{max}", F("10"));
    page.replace("{step}", F("1"));

    page += FPSTR(SITE_INP_NR);  
    page.replace("{tit}", F("Overall Brightness"));
    page.replace("{id}",  F(C_BRIGHTNESS_TAG)); 
    page.replace("{val}", String(settings.c_brightness));
    page.replace("{min}", F("0"));
    page.replace("{max}", F("31"));
    page.replace("{step}", F("1"));

    page += F("<br/>");  
    
    page += FPSTR(SITE_INP_N);  
    page.replace("{tit}", F("Auto OFF hour"));
    page.replace("{id}",  F(U_AUTOOFF_TAG)); 
    page.replace("{val}", String(settings.u_AUTO_OFF));
    page.replace("{min}", F("0"));
    page.replace("{max}", F("23"));
    page.replace("{step}", F("1"));

    page += FPSTR(SITE_INP_N);  
    page.replace("{tit}", F("Auto ON hour"));
    page.replace("{id}",  F(U_AUTOON_TAG)); 
    page.replace("{val}", String(settings.u_AUTO_ON));
    page.replace("{min}", F("0"));
    page.replace("{max}", F("23"));
    page.replace("{step}", F("1"));

    page += F("<br/>");  

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Apply"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("APPLY"));
    page.replace("{col}", F("bgrn"));

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Save & Apply"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("SAVE"));
    page.replace("{col}", F("bred"));

    page += FPSTR(SITE_FORM_END); 

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_START);

    page += FPSTR(SITE_END); 
     
    WebsiteSend(page); 
}

void WebsiteUserActionPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Actions"));
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_START);

    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("Text"));
    page.replace("{id}",  F(D_TEXT_TAG)); 
    page.replace("{val}", String(settings.d_text));
    page.replace("{len}", F("255"));

    page += FPSTR(SITE_INP_N);  
    page.replace("{tit}", F("Temperature"));
    page.replace("{id}",  F(D_TEMP_TAG)); 
    page.replace("{val}", String(settings.d_temperatur));
    page.replace("{min}", F("-9"));
    page.replace("{max}", F("99"));
    page.replace("{step}", F("1"));

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Display Text"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("SETTEXT"));
    page.replace("{col}", F("bgrn"));

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Display Temperature"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("SETTEMP"));
    page.replace("{col}", F("bgrn"));

    page += FPSTR(SITE_FORM_END); 

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_START);

    page += FPSTR(SITE_END); 
     
    WebsiteSend(page); 
}



void WebsiteConfigPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);   
    page.replace("{pcat}" , F("Config"));

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Network Config"));
    page.replace("{dest}", REQ_CONF_NETWORK);

    if(settings.u_MQTT > 0){
        page += FPSTR(SITE_HREF);  
        page.replace("{tit}", F("MQTT Config"));
        page.replace("{dest}", REQ_CONF_MQTT);
    }

    if(settings.u_LDR > 0){
        page += FPSTR(SITE_HREF);  
        page.replace("{tit}", F("LDR Config"));
        page.replace("{dest}", REQ_CONF_LDR);
    }

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Misc. Config"));
    page.replace("{dest}", REQ_CONF_MISC);

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Firmware Update"));
    page.replace("{dest}", REQ_OTA_SELECT);

    page += FPSTR(SITE_HREF_EXT);  
    page.replace("{tit}", F("Restart"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("REBOOT"));
    page.replace("{col}", F("bred"));
    page.replace("{dest}", REQ_START);

    page += FPSTR(SITE_HREF_EXT);  
    page.replace("{tit}", F("Factory Reset"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F(""));
    page.replace("{col}", F("bred"));
    page.replace("{dest}", REQ_FACTORY_RESET);

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Home"));
    page.replace("{dest}", REQ_START);
   
    page += FPSTR(SITE_END); 

    WebsiteSend(page); 
}

void WebsiteNetworkConfigPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Network Config"));
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_CONF_NETWORK);
    
    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("Hostname"));
    page.replace("{id}",  F(N_HOSTNAME_TAG)); 
    page.replace("{val}", String(settings.n_hostname));
    page.replace("{len}", F("32"));

    page += FPSTR(SITE_INP_N);  
    page.replace("{tit}", F("NTP Interval"));
    page.replace("{id}",  F(N_NTPINTERVAL_TAG)); 
    page.replace("{val}", String(settings.n_ntpinterval));
    page.replace("{min}", F("10000"));
    page.replace("{max}", F("60000"));
    page.replace("{step}", F("1000"));
    
    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("NTP Server"));
    page.replace("{id}",  F(N_NTPSERVER_TAG)); 
    page.replace("{val}", String(settings.n_ntpserver));
    page.replace("{len}", F("32"));
    

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Save & Restart"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("SAVER"));
    page.replace("{col}", F("bred"));

    page += FPSTR(SITE_FORM_END);  
    
    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_CONFIG);

    page += FPSTR(SITE_END); 
     
    WebsiteSend(page); 
}

void WebsiteMQTTConfigPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("MQTT Config"));
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_CONF_MQTT);
    
    page += FPSTR(SITE_INP_N);  
    page.replace("{tit}", F("Port"));
    page.replace("{id}",  F(M_PORT_TAG)); 
    page.replace("{val}", String(settings.m_port));
    page.replace("{min}", F("1"));
    page.replace("{max}", F("60000"));
    page.replace("{step}", F("1"));

    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("Broker"));
    page.replace("{id}",  F(M_HOST_TAG)); 
    page.replace("{val}", String(settings.m_host));
    page.replace("{len}", F("32"));

    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("Client ID"));
    page.replace("{id}",  F(M_CLIENT_ID_TAG)); 
    page.replace("{val}", String(settings.m_client_id ));
    page.replace("{len}", F("32"));

    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("User"));
    page.replace("{id}",  F(M_USER_TAG)); 
    page.replace("{val}", String(settings.m_user));
    page.replace("{len}", F("32"));

    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("Password"));
    page.replace("{id}",  F(M_PASS_TAG)); 
    page.replace("{val}", String(settings.m_pass));
    page.replace("{len}", F("32"));
    
    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("Topic unique part"));
    page.replace("{id}",  F(M_TOPIC_TAG)); 
    page.replace("{val}", String(settings.m_topic));
    page.replace("{len}", F("32"));

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Save & Restart"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("SAVER"));
    page.replace("{col}", F("bred"));

    page += FPSTR(SITE_FORM_END); 

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_CONFIG);

    page += FPSTR(SITE_END); 
     
    WebsiteSend(page); 
}

void WebsiteLDRConfigPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , "LDR Config (av: " + String(LDRgetValue()) + ")");
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_CONF_LDR);

    page += FPSTR(SITE_INP_NR);  
    page.replace("{tit}", F("min. PWM Level"));
    page.replace("{id}",  F(L_MIN_BRIGHT_TAG)); 
    page.replace("{val}", String(settings.l_min_bright));
    page.replace("{min}", F("0"));
    page.replace("{max}", F("31"));
    page.replace("{step}", F("1"));

    for(uint8 i=0; i < sizeof(settings.l_treshold) / 2 ; i++){   //geteilt durch 2 wegen uint16
        page += FPSTR(SITE_INP_N);  
        page.replace("{tit}", "LDR Treshold" + String(i+1)); 
        page.replace("{id}",  L_TRESHOLD_TAG + String(i)); 
        page.replace("{val}", String(settings.l_treshold[i]));        
    }
    page.replace("{min}", F("0"));
    page.replace("{max}", F("1023"));
    page.replace("{step}", F("1"));

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Apply"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("APPLY"));
    page.replace("{col}", F("bgrn"));

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Save & Apply"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("SAVE"));
    page.replace("{col}", F("bred"));

    page += FPSTR(SITE_FORM_END); 

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_CONFIG);

    page += FPSTR(SITE_END); 
     
    WebsiteSend(page); 
}

void WebsiteMiscConfigPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Misc. Config"));
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_CONF_MISC);

    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("use MQTT"));
    page.replace("{val}", String(settings.u_MQTT));
    page.replace("{id}",  F(U_MQTT_TAG)); 
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("yes"));
    page.replace("{oval}", F("1"));
    page.replace("{oopt}", (settings.u_MQTT == 1) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("no"));
    page.replace("{oval}", F("0"));
    page.replace("{oopt}", (settings.u_MQTT == 0) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_END);  
    
    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("use LDR"));
    page.replace("{val}", String(settings.u_LDR));
    page.replace("{id}",  F(U_LDR_TAG)); 
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("yes"));
    page.replace("{oval}", F("1"));
    page.replace("{oopt}", (settings.u_LDR == 1) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("no"));
    page.replace("{oval}", F("0"));
    page.replace("{oopt}", (settings.u_LDR == 0) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_END);  
    
    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("use MDNS"));
    page.replace("{val}", String(settings.u_MDNS));
    page.replace("{id}",  F(U_MDNS_TAG)); 
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("yes"));
    page.replace("{oval}", F("1"));
    page.replace("{oopt}", (settings.u_MDNS == 1) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("no"));
    page.replace("{oval}", F("0"));
    page.replace("{oopt}", (settings.u_MDNS == 0) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_END);  

    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("Log Level"));
    page.replace("{id}",  F(U_LOGG_TAG)); 
    page.replace("{val}",  String(settings.u_LOGGING)); 
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("off"));
    page.replace("{oval}", String(LOGLEVEL_OFF));
    page.replace("{oopt}", (settings.u_LOGGING == LOGLEVEL_OFF) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("error"));
    page.replace("{oval}", String(LOGLEVEL_ERR));
    page.replace("{oopt}", (settings.u_LOGGING == LOGLEVEL_ERR) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("info"));
    page.replace("{oval}", String(LOGLEVEL_INF));
    page.replace("{oopt}", (settings.u_LOGGING == LOGLEVEL_INF) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("debug"));
    page.replace("{oval}", String(LOGLEVEL_DBG));
    page.replace("{oopt}", (settings.u_LOGGING == LOGLEVEL_DBG) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_END); 

    page += FPSTR(SITE_BUTTON);  
    page.replace("{tit}", F("Save & Restart"));
    page.replace("{id}",  F("ACTION"));
    page.replace("{val}", F("SAVER"));
    page.replace("{col}", F("bred"));

    page += FPSTR(SITE_FORM_END); 

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Back"));
    page.replace("{dest}", REQ_CONFIG);

    page += FPSTR(SITE_END); 
     
    WebsiteSend(page); 
}

void WebsiteSend(String page){
    page.replace("{phead}", settings.n_hostname);    
    page.replace("{ptit}" , settings.n_hostname);
    
    _server->sendHeader("Content-Length", String(page.length()));
    _server->send(200, "text/html", page); 

}
