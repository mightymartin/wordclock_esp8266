#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <Ticker.h>
#include "logging.h"
#include "settings.h"

#define MQTT_MAX_PACKET_SIZE  1024

#define MQTT_TOPIC_PREFIX   "tele/"
#define MQTT_CMD_TOPIC      "/CMD/+"
#define MQTT_STATE_TOPIC    "/STATE"

extern String cmdTopic, stateTopic;

extern void MQTTUpdate();
extern void MQTTSubCallback(char* topic, byte* payload, unsigned int length);
extern void MQTTPublish();
extern void MQTTInit();
extern void MQTTTick();
extern String MQTTStatus();

#endif
