#include "website.h"

ESP8266WebServer *_server;

void WebsiteInit(ESP8266WebServer *server){
    _server = server;
    _server->on(REQ_START, WebsiteStartPage);
    _server->on(REQ_CONFIG, WebsiteConfigPage);    
    _server->on(REQ_CONF_NETWORK, WebsiteNetworkConfigPage);    
    _server->on(REQ_CONF_MQTT, WebsiteMQTTConfigPage);    
    _server->on(REQ_CONF_MISC, WebsiteMiscConfigPage);    
    _server->on(REQ_COLOR, WebsiteColorPage);    
    _server->on(REQ_DRAW, WebsiteDrawPage);    
}

void WebsiteAction(){
    /*if (_server->hasArg("plain")== false){ //Check if body received
        _server->send(200, "text/plain", "Body not received");
        return;
    }
 
    String message = "Body received:\n";
           message += _server->arg("plain");
           message += "\n";
 
    _server->send(200, "text/plain", message);    */
}

void WebsiteStartPage(){
    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Home"));

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Color mode"));
    page.replace("{dest}", REQ_COLOR);

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Display mode"));
    page.replace("{dest}", REQ_DRAW);

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Config"));
    page.replace("{dest}", REQ_CONFIG);

    page += FPSTR(SITE_END); 
    
    WebsiteSend(page);    
}

void WebsiteDrawPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Display Settings"));
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_DRAW);

    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("Display mode"));
    page.replace("{id}",  F(D_MODE_TAG)); 
    page.replace("{val}",  String(settings.d_mode));     
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Clock"));
    page.replace("{oval}", String(DRAW_MODE_CLOCK));
    page.replace("{osel}", (settings.d_mode == DRAW_MODE_CLOCK) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Seconds"));
    page.replace("{oval}", String(DRAW_MODE_SECONDS));
    page.replace("{osel}", (settings.d_mode == DRAW_MODE_SECONDS) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Temperature"));
    page.replace("{oval}", String(DRAW_MODE_TEMP));
    page.replace("{osel}", (settings.d_mode == DRAW_MODE_TEMP) ? F("selected") : F(""));    
    page += FPSTR(SITE_INP_CBX_END); 

    if(settings.d_mode == DRAW_MODE_CLOCK){
        page += FPSTR(SITE_INP_CBX_BGN);  
        page.replace("{tit}", F("Region"));
        page.replace("{id}",  F(D_CLK_REGION_TAG)); 
        page.replace("{val}",  String(settings.d_clk_region));     
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("West Germany"));
        page.replace("{oval}", String(DRAW_CLOCK_REGION_WEST));
        page.replace("{osel}", (settings.d_clk_region == DRAW_CLOCK_REGION_WEST) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("East Germany"));
        page.replace("{oval}", String(DRAW_CLOCK_REGION_OST));
        page.replace("{osel}", (settings.d_clk_region == DRAW_CLOCK_REGION_OST) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("Rhine-Ruhr"));
        page.replace("{oval}", String(DRAW_CLOCK_REGION_POTT));
        page.replace("{osel}", (settings.d_clk_region == DRAW_CLOCK_REGION_POTT) ? F("selected") : F(""));    
        page += FPSTR(SITE_INP_CBX_END); 

        page += FPSTR(SITE_INP_CBX_BGN);  
        page.replace("{tit}", F("IT IS mode"));
        page.replace("{id}",  F(D_CLK_ITIS_MODE_TAG)); 
        page.replace("{val}",  String(settings.d_clk_itis_mode)); 
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("always off"));
        page.replace("{oval}", String(DRAW_CLOCK_ITIS_OFF));
        page.replace("{osel}", (settings.d_clk_itis_mode == DRAW_CLOCK_ITIS_OFF) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("full/half hour"));
        page.replace("{oval}", String(DRAW_CLOCK_ITIS_HOURNHALF));
        page.replace("{osel}", (settings.d_clk_itis_mode == DRAW_CLOCK_ITIS_HOURNHALF) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("always on"));
        page.replace("{oval}", String(DRAW_CLOCK_ITIS_PERMA));
        page.replace("{osel}", (settings.d_clk_itis_mode == DRAW_CLOCK_ITIS_PERMA) ? F("selected") : F(""));    
        page += FPSTR(SITE_INP_CBX_END); 

        page += FPSTR(SITE_INP_CBX_BGN);  
        page.replace("{tit}", F("Pixel fading"));
        page.replace("{id}",  F(D_CLK_FADE_TAG)); 
        page.replace("{val}",  String(settings.d_clk_fade)); 
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("yes"));
        page.replace("{oval}", F("1"));
        page.replace("{osel}", (settings.d_clk_fade == 1) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("no"));
        page.replace("{oval}", F("0"));
        page.replace("{osel}", (settings.d_clk_fade == 0) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_END); 
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

void WebsiteColorPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Color Settings"));
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_COLOR);

    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("Colormode"));
    page.replace("{id}",  F(C_MODE_TAG)); 
    page.replace("{val}",  String(settings.c_mode));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Plain"));
    page.replace("{oval}", String(COLOR_MODE_PLAIN));
    page.replace("{osel}", (settings.c_mode == COLOR_MODE_PLAIN) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Rainbow Serpentine"));
    page.replace("{oval}", String(COLOR_MODE_RAINBOW_SERPENTINE));
    page.replace("{osel}", (settings.c_mode == COLOR_MODE_RAINBOW_SERPENTINE) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Rainbow N->S"));
    page.replace("{oval}", String(COLOR_MODE_RAINBOW_VERTI));
    page.replace("{osel}", (settings.c_mode == COLOR_MODE_RAINBOW_VERTI) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Rainbow S->N"));
    page.replace("{oval}", String(COLOR_MODE_RAINBOW_VERTI_I));
    page.replace("{osel}", (settings.c_mode == COLOR_MODE_RAINBOW_VERTI_I) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Rainbow E->W"));
    page.replace("{oval}", String(COLOR_MODE_RAINBOW_HORI));
    page.replace("{osel}", (settings.c_mode == COLOR_MODE_RAINBOW_HORI) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Rainbow W->E"));
    page.replace("{oval}", String(COLOR_MODE_RAINBOW_HORI_I));
    page.replace("{osel}", (settings.c_mode == COLOR_MODE_RAINBOW_HORI_I) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("Color Change"));
    page.replace("{oval}", String(COLOR_MODE_COLOR_CHANGE));
    page.replace("{osel}", (settings.c_mode == COLOR_MODE_COLOR_CHANGE) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_END);  

    if( settings.c_mode != COLOR_MODE_COLOR_CHANGE && settings.c_mode != COLOR_MODE_PLAIN ){
        page += FPSTR(SITE_INP_CBX_BGN);  
        page.replace("{tit}", F("Color Rotate"));
        page.replace("{id}",  F(C_HUE_ROTATE_RB_TAG)); 
        page.replace("{val}",  String(settings.c_hue_rotate_rb));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("yes"));
        page.replace("{oval}", F("1"));
        page.replace("{osel}", (settings.c_hue_rotate_rb == 1) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_OPT);  
        page.replace("{otit}", F("no"));
        page.replace("{oval}", F("0"));
        page.replace("{osel}", (settings.c_hue_rotate_rb == 0) ? F("selected") : F(""));
        page += FPSTR(SITE_INP_CBX_END); 
    }

    if( settings.c_mode == COLOR_MODE_COLOR_CHANGE || (settings.c_mode != COLOR_MODE_COLOR_CHANGE && settings.c_mode != COLOR_MODE_PLAIN && settings.c_hue_rotate_rb == 1) ){
        page += FPSTR(SITE_INP_N);  
        page.replace("{tit}", F("Rotate Duration (s)"));
        page.replace("{id}",  F(C_HUE_ROTATE_DURATION_TAG)); 
        page.replace("{val}", String(settings.c_hue_rotate_duration));
        page.replace("{min}", F("30000"));
        page.replace("{max}", F("600000"));
        page.replace("{step}", F("1000"));
    }

    if( settings.c_mode == COLOR_MODE_PLAIN){
        page += FPSTR(SITE_INP_NR);  
        page.replace("{tit}", F("Red Color"));
        page.replace("{id}",  F(C_PLAIN_RED_TAG)); 
        page.replace("{val}", String(settings.c_plain_red));
        page.replace("{min}", F("0"));
        page.replace("{max}", F("255"));
        page.replace("{step}", F("1"));

        page += FPSTR(SITE_INP_NR);  
        page.replace("{tit}", F("Green Color"));
        page.replace("{id}",  F(C_PLAIN_GREEN_TAG)); 
        page.replace("{val}", String(settings.c_plain_green));
        page.replace("{min}", F("0"));
        page.replace("{max}", F("255"));
        page.replace("{step}", F("1"));

        page += FPSTR(SITE_INP_NR);  
        page.replace("{tit}", F("Blue Color"));
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


void WebsiteConfigPage(){
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

    page += FPSTR(SITE_HREF);  
    page.replace("{tit}", F("Misc. Config"));
    page.replace("{dest}", REQ_CONF_MISC);

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

    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("AP SSID Prefix"));
    page.replace("{id}",  F(N_AP_SSID_TAG)); 
    page.replace("{val}", String(settings.n_ap_ssid) + String(ESP.getChipId()));
    page.replace("{len}", F("32"));

    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("AP Password"));
    page.replace("{id}",  F(N_AP_PASS_TAG)); 
    page.replace("{val}", String(settings.n_ap_pass));
    page.replace("{len}", F("32"));

    if(settings.u_NTP > 0){
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
    }

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
    page.replace("{tit}", F("Topic"));
    page.replace("{id}",  F(M_TOPIC_TAG)); 
    page.replace("{val}", String(settings.m_topic));
    page.replace("{len}", F("32"));

    page += FPSTR(SITE_INP_T);  
    page.replace("{tit}", F("Fulltopic"));
    page.replace("{id}",  F(M_FULLTOPIC_TAG)); 
    page.replace("{val}", String(settings.m_fulltopic));
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

void WebsiteMiscConfigPage(){
    WebsiteAction();

    String page = FPSTR(SITE_HEAD);    
    page += FPSTR(SITE_BGN);  
    page.replace("{pcat}" , F("Misc. Config"));
    
    page += FPSTR(SITE_FORM_BGN);  
    page.replace("{dest}", REQ_CONF_MISC);

    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("use MQTT"));
    page.replace("{id}",  F(U_MQTT_TAG)); 
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("yes"));
    page.replace("{oval}", F("1"));
    page.replace("{osel}", (settings.u_MQTT == 1) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("no"));
    page.replace("{oval}", F("0"));
    page.replace("{osel}", (settings.u_MQTT == 0) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_END);  

    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("use NTP"));
    page.replace("{id}",  F(U_NTP_TAG)); 
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("yes"));
    page.replace("{oval}", F("1"));
    page.replace("{osel}", (settings.u_NTP == 1) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("no"));
    page.replace("{oval}", F("0"));
    page.replace("{osel}", (settings.u_NTP == 0) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_END);  
    
    page += FPSTR(SITE_INP_CBX_BGN);  
    page.replace("{tit}", F("use LDR"));
    page.replace("{id}",  F(U_LDR_TAG)); 
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("yes"));
    page.replace("{oval}", F("1"));
    page.replace("{osel}", (settings.u_LDR == 1) ? F("selected") : F(""));
    page += FPSTR(SITE_INP_CBX_OPT);  
    page.replace("{otit}", F("no"));
    page.replace("{oval}", F("0"));
    page.replace("{osel}", (settings.u_LDR == 0) ? F("selected") : F(""));
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
