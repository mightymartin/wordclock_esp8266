##Wordclock based on an ESP8266 / WS2812
![front](img/front_an.jpg)

###Hardware:
- LDR with voltagedevider on A0 
- WS2866 via levelshifter on RXD0 

![wiring1](img/schematics.jpg)
![wiring1](img/drahtverhau.jpg)

###Features:
- defineable hardware layout (leds.h)
- word fading
- display hour and minutes
- display seconds
- display temperature
- 8 different color modes with HUE rotate
- wifimanger
- Webserver http://deviceip:80
- OTA
- mdns
- NTP time client
- MQTT Sub: ON/OFF && BRIGHTNESS && COLORMODE && DISPLAYMODE (Non persistent)
- MQTT Pub: current config as JSON to broker
- LDR driven brightness


##Todos befor V1.0:
###Addons
- tempsensor implementation
###Bugfixing

##Images
![img1](img/front_blank.jpg)
![img1](img/front.jpg)
![img1](img/menu1.jpg)
![img1](img/menu2_2.jpg)
![img1](img/menu2_2.jpg)
![img1](img/menu3.jpg)
![img1](img/menu4.jpg)
![img1](img/menu5.jpg)







