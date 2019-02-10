Wordclock based on an ESP8266 / WS2812

Hardware:
- LDR with voltagedevider on A0 
- WS2866 via levelshifter on RXD0 

Features:
- defineable hardware layout 
- word fading
- display hour and minutes
- display seconds
- display temperature
- wifimanger
- Webserver http://deviceip:80 (WIP)
- OTA http://deviceip:81/update
- NTP time client
- LDR driven brightness
- different color modes 


Todos befor V0:
- Config layer for persistent data in EEPROM / SPIFF
- Web GUIi to configure clock an save data

- MQTT Sub: ON/OFF && BRIGHTNESS && COLORMODE && DISPLAYMODE (Non persistent)
- MQTT Pub: current config as JSON to broker

Bug:
- Color HUE value at color rotate flips on overflow


