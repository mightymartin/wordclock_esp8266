#ifndef WEBSITE_H
#define WEBSITE_H

#include <ESP8266WebServer.h>
#include "settings.h"
#include "timeNTP.h"
#include "color.h"
#include "draw.h"

#define QUOTE(...) #__VA_ARGS__

#define REQ_START           "/"
#define REQ_MODES           "/mod"
#define REQ_CONFIG          "/cnf"

#define REQ_CONF_DRAW       "/cdr"
#define REQ_CONF_COLOR      "/cco"

#define REQ_CONF_NETWORK    "/cne"
#define REQ_CONF_MQTT       "/cmq"
#define REQ_CONF_MISC       "/cmi"
#define REQ_CONF_LDR        "/cld"

#define REQ_INFO           "/inf"

const char SITE_HEAD[]          PROGMEM = QUOTE(    <html>
                                                        <head>
                                                            <meta charset="utf-8">
                                                            <meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no">
                                                            {emeta}
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
                                                                    width:98%;
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
const char SITE_RELOAD_WAIT[]      PROGMEM    = QUOTE( <meta http-equiv="refresh" content="6; url={dest}"> );



extern void WebsiteInit(ESP8266WebServer *server);
extern void WebsiteStartPage();

extern void WebsiteModesPage ();
extern void WebsiteDrawConfPage ();
extern void WebsiteColorConfPage();

extern void WebsiteConfigPage();
extern void WebsiteNetworkConfigPage();
extern void WebsiteMQTTConfigPage();
extern void WebsiteLDRConfigPage();
extern void WebsiteMiscConfigPage();
extern void WebsiteInfoPage();

extern void WebsiteRebootPage();
extern void WebsiteResetPage();

extern void WebsiteActionPage();

extern void WebsiteSend(String page);

#endif