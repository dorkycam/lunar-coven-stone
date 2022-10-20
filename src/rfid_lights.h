
#ifndef RFID_LIGHTS_H
#define RFID_LIGHTS_H 1

#include <Arduino.h>

#define GOAL_COUNT 8
#define CAL_COUNT 8

extern uint8_t reset[10];

struct Goal {
    uint8_t rfid[10];
    int ledPin;
};

extern Goal GOALS[GOAL_COUNT];

// CAULDRON NFC TAGS
struct Cauldron {
    uint8_t rfid[10];
};

extern Cauldron CALS[CAL_COUNT];

#endif
