#ifndef WEBSITE_H
#define WEBSITE_H

#include <ESP8266WebServer.h>
#include "settings.h"
#include "logging.h"
#include "timeNTP.h"
#include "color.h"
#include "draw.h"
#include "mqtt.h"

#define REQ_START           "/"
#define REQ_MODES           "/mod"

#define REQ_INFO            "/inf"
#define REQ_FACTORY_RESET   "/fcr"
#define REQ_OTA             "/ota"

#define REQ_CONFIG          "/cnf"
#define REQ_CONF_MODES      "/cmo"
#define REQ_CONF_NETWORK    "/cne"
#define REQ_CONF_MQTT       "/cmq"
#define REQ_CONF_MISC       "/cmi"
#define REQ_CONF_LDR        "/cld"

#define REQ_CONSOLE         "/con"
#define REQ_OTA_SELECT      "/otasel"



const char SITE_HEAD[]          PROGMEM = QUOTE(    <html>
                                                        <head>
                                                            <meta charset="utf-8">
                                                            <meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no">                                                            
                                                            <title>{ptit}</title>
                                                            <style>
                                                                div,fieldset,input,select{
                                                                    padding:5px;font-size:1em;
                                                                }
                                                                input{
                                                                    width:100%;
                                                                    box-sizing:border-box;
                                                                    -webkit-box-sizing:border-box;
                                                                    -moz-box-sizing:border-box;
                                                                }
                                                                select{
                                                                    width:100%;
                                                                }
                                                                form{
                                                                    margin-bottom: 0px;
                                                                }
                                                                textarea{
                                                                    resize:none;
                                                                    width:100%;
                                                                    height:318px;
                                                                    padding:5px;
                                                                    overflow:auto;
                                                                }
                                                                body{
                                                                    text-align:center;
                                                                    font-family:verdana;
                                                                }
                                                                td{
                                                                    padding:0px;
                                                                }
                                                                button{
                                                                    border:0;
                                                                    border-radius:0.3rem;
                                                                    background-color:#1fa3ec;
                                                                    color:#fff;
                                                                    line-height:2.4rem;
                                                                    font-size:1.2rem;
                                                                    width:100%;
                                                                    -webkit-transition-duration:0.4s;
                                                                    transition-duration:0.4s;
                                                                    cursor:pointer;
                                                                    margin-top: 10px;
                                                                }
                                                                button:hover{
                                                                    background-color:#0e70a4;
                                                                }
                                                                .bred{
                                                                    background-color:#d43535;
                                                                }
                                                                .bred:hover{
                                                                    background-color:#931f1f;
                                                                }
                                                                .bgrn{
                                                                    background-color:#47c266;
                                                                }
                                                                .bgrn:hover{
                                                                    background-color:#5aaf6f;
                                                                }
                                                                a{
                                                                    text-decoration:none;
                                                                }
                                                                .p{
                                                                    float:left;
                                                                    text-align:left;
                                                                }
                                                                .q{
                                                                    float:right;
                                                                    text-align:right;
                                                                }
                                                            </style>
                                                        </head>);

const char SITE_BGN[]           PROGMEM    =  QUOTE(    <body>
                                                            <div style="text-align:left;display:inline-block;min-width:340px;">
                                                                <div style="text-align:center;">                                                            
                                                                    <h2>{phead}</h2>
                                                                </div>
                                                                <fieldset>
                                                                    <legend>
                                                                        <b>{pcat}</b>
                                                                    </legend>);
const char SITE_END[]           PROGMEM    = QUOTE(             </fieldset>
                                                            </div>
                                                        </body>
                                                    </html>);

const char SITE_BGN_FULL[]      PROGMEM    =  QUOTE(    <body>
                                                            <div style="text-align:left;display:inline-block;min-width:340px;">
                                                                <div style="text-align:center;">                                                            
                                                                    <h2>{phead}</h2>
                                                                </div>);
const char SITE_END_FULL[]      PROGMEM    = QUOTE(         </div>
                                                        </body>
                                                    </html>);

const char SITE_FORM_BGN[]      PROGMEM    = QUOTE( <form method="post" action="{dest}">);
const char SITE_FORM_END[]      PROGMEM    = QUOTE( </form>);

const char SITE_DL_BGN[]        PROGMEM    = QUOTE( <dl>);
const char SITE_DL_END[]        PROGMEM    = QUOTE( </dl>);

const char SITE_DL_LINE[]       PROGMEM    = QUOTE( <dt><b>{tit}</b>:</dt>
                                                    <dd>{val}</dd>);

const char SITE_INP_T[]         PROGMEM    = QUOTE( <b>{tit}</b> [l:{len}] ({val})<br/>
					                                <input id="{id}" name="{id}" maxlength="{len}" value="{val}"><br/>
					                                <br/>);

const char SITE_INP_N[]         PROGMEM    = QUOTE( <b>{tit}</b> [{min}-{max}] ({val})<br/>
					                                <input type="number" id="{id}" name="{id}" min="{min}" max="{max}" step="{step}" value="{val}"><br/>
					                                <br/>);

const char SITE_INP_NR[]        PROGMEM    = QUOTE( <b>{tit}</b> [{min}-{max}] ({val})<br/>
					                                <input type="range" id="{id}" name="{id}" min="{min}" max="{max}" step="{step}" value="{val}"><br/>
					                                <br/>);

const char SITE_INP_CBX_BGN[]   PROGMEM    = QUOTE( <b>{tit}</b> ({val})<br/>
                                                    <select id="{id}" name="{id}"> );
const char SITE_INP_CBX_OPT[]   PROGMEM    = QUOTE(     <option {osel} value="{oval}">{otit}</option> );
const char SITE_INP_CBX_END[]   PROGMEM    = QUOTE( </select>
                                                    <br/>);                                                  

const char SITE_BUTTON[]        PROGMEM    = QUOTE( <button name="{id}" type="submit" value="{val}"  class="button {col}">{tit}</button>);

const char SITE_HREF[]          PROGMEM    = QUOTE( <form method="post" action="{dest}">
                                                        <button name="" type="submit" class="button">{tit}</button>
                                                    </form>);

const char SITE_HREF_EXT[]      PROGMEM    = QUOTE( <form method="post" action="{dest}">
                                                        <button name="{id}" type="submit" value="{val}" class="button {col}">{tit}</button>
                                                    </form>);

const char SITE_UPDATE_FORM[]   PROGMEM    = QUOTE( <form method='POST' action="{dest}" enctype='multipart/form-data'>
                                                        <input  name='update' type='file'>
                                                        <button type="submit" class="button bred" value='Update'>Update</button>                                                        
                                                    </form>);

const char SITE_RELOAD_WAIT[]   PROGMEM    = QUOTE( <div id="RLCOUNT"></div>
                                                    <script language="JavaScript" type="text/javascript">
                                                        var tickM = 10;
                                                        var tickC = 0;
                                                        function tTick(){	                                                                                                                    
                                                            if(tickM==tickC){
                                                                location.href='.';
                                                                return;
                                                            }                                                            
                                                            var tickL=tickM-tickC;
	                                                        document.getElementById('RLCOUNT').innerHTML="Reload Page in " + tickL + "s";
                                                            tickC++;
                                                            setTimeout(tTick,1000);
                                                        }                                                        
                                                        tTick();                                                                                                                 
                                                    </script>);

const char SITE_CONSOLE[]       PROGMEM    = QUOTE( <textarea readonly="" id="CONSOLE" name="CONSOLE" cols="340" wrap="off"></textarea>
                                                    <script language="JavaScript" type="text/javascript">                                                                                                                 
                                                        function startWS(){
                                                            Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
                                                            Socket.onmessage = function(evt){
                                                                var ta = document.getElementById('CONSOLE');
                                                                ta.value+=evt.data+"\n";
                                                                ta.scrollTop=99999;
                                                            };                
                                                        }                                                                                                             
                                                        startWS();                                                                                                                
                                                    </script>);                                                    



extern void WebsiteInit(ESP8266WebServer *server);
extern void WebsiteStartPage();

extern void WebsiteModesPage ();
extern void WebsiteModesConfPage ();

extern void WebsiteFirmwareUpdate();
extern void WebsiteFactoryResetPage();
extern void WebsiteConfigPage();
extern void WebsiteNetworkConfigPage();
extern void WebsiteMQTTConfigPage();
extern void WebsiteLDRConfigPage();
extern void WebsiteMiscConfigPage();
extern void WebsiteInfoPage();
extern void WebsiteConsolePage();

extern void WebsiteSend(String page);

#endif