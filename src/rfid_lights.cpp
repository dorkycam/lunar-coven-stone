#include "rfid_lights.h"

uint8_t reset[10] = {0x04, 0x77, 0x42, 0x27, 0xDE, 0x7C, 0x70, 0x00, 0x00, 0x00};

Goal GOALS[GOAL_COUNT] = {
    {
        rfid : {0x04, 0x82, 0xE5, 0x05, 0x39, 0x6C, 0x80, 0x00, 0x00, 0x00},
        ledPin : 1
    },
    {
        rfid : {0x04, 0x84, 0xFD, 0x00, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00},
        ledPin : 2
    },
    {
        rfid : {0x04, 0x62, 0x98, 0x02, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00},
        ledPin : 3
    },
    {
        rfid : {0x04, 0x7A, 0xAB, 0x02, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00},
        ledPin : 4
    },
    {
        rfid : {0x04, 0x77, 0x42, 0xF9, 0x6E, 0x7C, 0x70, 0x00, 0x00, 0x00},
        ledPin : 5
    },
    {
        rfid : {0x04, 0xCD, 0x49, 0x06, 0x39, 0x6C, 0x80, 0x00, 0x00, 0x00},
        ledPin : 6
    },
    {
        rfid : {0x04, 0xE1, 0xF7, 0x06, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00},
        ledPin : 7
    },
    {
        rfid : {0x04, 0x77, 0x42, 0x22, 0xA0, 0x06, 0xC0, 0x00, 0x00, 0x00},
        ledPin : 12
    }};

Cauldron CALS[CAL_COUNT] = {
    {rfid : {0x04, 0x27, 0x44, 0x05, 0x39, 0x6C, 0x80, 0x00, 0x00, 0x00}},
    {rfid : {0x04, 0xDE, 0xB6, 0x06, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00}},
    {rfid : {0x04, 0x77, 0x42, 0x3A, 0x06, 0x7C, 0x70, 0x00, 0x00, 0x00}},
    {rfid : {0x04, 0x64, 0x1C, 0x06, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00}},
    {rfid : {0x04, 0x39, 0xE9, 0x04, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00}},
    {rfid : {0x04, 0x3D, 0x1C, 0x05, 0x39, 0x6C, 0x80, 0x00, 0x00, 0x00}},
    {rfid : {0x04, 0x5D, 0xB2, 0x05, 0x39, 0x6C, 0x80, 0x00, 0x00, 0x00}},
    {rfid : {0x04, 0x34, 0x3D, 0x05, 0x39, 0x6C, 0x80, 0x00, 0x00, 0x00}}};
