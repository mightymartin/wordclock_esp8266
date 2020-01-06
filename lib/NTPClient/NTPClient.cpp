/**
 * Copyright (c) 2015 by Fabrice Weinberg (The MIT License (MIT))
 * altered with Copyright (c) 2019 by Martin Krämer (under the given project Copyright)
 */

#include "NTPClient.h"

NTPClient::NTPClient(UDP& udp) {
  this->_udp            = &udp;  
}

NTPClient::NTPClient(UDP& udp, long timeOffset) {
  this->_udp            = &udp;
  this->_timeOffset     = timeOffset;  
}

NTPClient::NTPClient(UDP& udp, const char* poolServerName) {
  this->_udp            = &udp;
  this->_poolServerName = poolServerName;  
}

NTPClient::NTPClient(UDP& udp, const char* poolServerName, long timeOffset) {
  this->_udp            = &udp;
  this->_timeOffset     = timeOffset;
  this->_poolServerName = poolServerName;  
}

NTPClient::NTPClient(UDP& udp, const char* poolServerName, long timeOffset, unsigned long updateInterval) {
  this->_udp            = &udp;
  this->_timeOffset     = timeOffset;
  this->_poolServerName = poolServerName;
  this->_updateInterval = updateInterval;  
}

void NTPClient::begin() {
  this->begin(NTP_DEFAULT_LOCAL_PORT);
}

void NTPClient::begin(int port) {
  this->_port = port;
  this->_udp->begin(this->_port);
  this->_udpSetup = true;
}

time_t NTPClient::decodeNtpMessage (byte *messageBuffer) {
    unsigned long secsSince1900;
    // convert four bytes starting at location 40 to a long integer
    unsigned long highWord = word(messageBuffer[40], messageBuffer[41]);
    unsigned long lowWord  = word(messageBuffer[42], messageBuffer[43]);

    secsSince1900 = highWord << 16 | lowWord;

    if (secsSince1900 == 0) {    
        return 0;
    }

    time_t timeTemp = secsSince1900 - SEVENZYYEARS;

    return timeTemp;
}

bool NTPClient::forceUpdate() {
    if(this->_updateInProcess == false){ 
        this->_updateInProcess = true;   
        #ifdef DEBUG_NTPClient
            Serial.println("Update from NTP Server");
        #endif

        this->sendNTPPacket();

        // Wait till data is there or timeout...
        uint8_t timeout = 0;
        uint8_t result = 0;        
        while (result == 0 && timeout <= 150 ){
            delay (10);            
            result = this->_udp->parsePacket();            
            timeout++;
        } 

        if(result >=  NTP_PACKET_SIZE){
            this->_udp->read(this->_packetBuffer, NTP_PACKET_SIZE);
            
            time_t timeValue = decodeNtpMessage (this->_packetBuffer);    
            if(timeValue != 0){        
                this->_currentEpoc = timeValue;                                
                this->_lastUpdate = millis() - (10 * (timeout + 1));
            }

            #ifdef DEBUG_NTPClient 
                Serial.print("millis:");
                Serial.println(millis());
                Serial.print("lastupd:");
                Serial.println(this->_lastUpdate);
                Serial.print("epoc:");
                Serial.println(this->_currentEpoc);
                Serial.print("interval:");
                Serial.println(this->_updateInterval);
                Serial.print("drift:");
                Serial.println(((millis() - this->_lastUpdate) / 1000));
            #endif
        }else{
            if(this->_lastUpdate != 0){
              //if ther has been an update, the interval has to be respected
              this->_currentEpoc = this->getEpochTime();                                
              this->_lastUpdate = millis() - (10 * (timeout + 1));
            }

            #ifdef DEBUG_NTPClient
              Serial.println("No Valid Data");
              Serial.println(result);
            #endif
        }
                
        this->_updateInProcess = false;
    }

    return true;
}

bool NTPClient::update() {
    if ((millis() - this->_lastUpdate >= this->_updateInterval) || this->_lastUpdate == 0) {
        if (!this->_udpSetup){
            this->begin();                         // setup the UDP client if needed
        } 
        return this->forceUpdate();
    }
    return false;
}

unsigned long NTPClient::getEpochTime() const {
  return this->_timeOffset + // User offset
         this->_currentEpoc + // Epoc returned by the NTP server
         ((millis() - this->_lastUpdate) / 1000); // Time since last update
}

void NTPClient::end() {
  this->_udp->stop();

  this->_udpSetup = false;
}

void NTPClient::setTimeOffset(int timeOffset) {
  this->_timeOffset     = timeOffset;
}

void NTPClient::setUpdateInterval(unsigned long updateInterval) {
  this->_updateInterval = updateInterval;
}

void NTPClient::setPoolServerName(const char* poolServerName) {
    this->_poolServerName = poolServerName;
}

void NTPClient::sendNTPPacket() {
  // set all bytes in the buffer to 0
  memset(this->_packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  this->_packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  this->_packetBuffer[1] = 0;     // Stratum, or type of clock
  this->_packetBuffer[2] = 6;     // Polling Interval
  this->_packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  this->_packetBuffer[12]  = 49;
  this->_packetBuffer[13]  = 0x4E;
  this->_packetBuffer[14]  = 49;
  this->_packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  this->_udp->beginPacket(this->_poolServerName, 123); //NTP requests are to port 123
  this->_udp->write(this->_packetBuffer, NTP_PACKET_SIZE);
  this->_udp->endPacket();
}
