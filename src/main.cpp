
#include <Adafruit_AW9523.h>
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

#include "GoalManager.h"
#include "LedManager.h"
#include "StoneMagic.h"
#include "rfid_lights.h"

// for RFID scanner driver setup?
MFRC522 mfrc522(10, 9);

// for LED driver setup
Adafruit_AW9523 aw;

StoneMagic game;
LedManager ledManager(&aw);
GoalManager goalManager(&mfrc522);

void setup() {
    Serial.begin(9600);
    while (!Serial)
        delay(1);  // wait for serial port to open

    Serial.println("beginning");

    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("rfc works");

    // LED Driver (AW9523) stuff
    if (!aw.begin(0x58)) {
        Serial.println("AW9523 not found? Check wiring!");
        //    while (1) delay(10);  // halt forever
    }
    Serial.println("AW9523 found!");

    for (int i = 0; i < GOAL_COUNT; i++) {
        aw.pinMode(GOALS[i].ledPin, AW9523_LED_MODE);  // set to constant current drive!
    }

    // RFID scanner pin setup
    pinMode(7, OUTPUT);

    Serial.println("Setup complete! (but check for errors)");
}

void loop() {
    ledManager.doTwinkles();

    if (!goalManager.isNewNfcFound()) {
        return;
    }

    if (goalManager.isResetFound()) {
        game.resetGame();
        ledManager.setAllLightsBrightness(0);
        return;
    }

    if (game.isGameFinished()) {
        Serial.println("Game is finished");
        return;
    }

    int scannedGoal = goalManager.getFoundGoal();
    if (scannedGoal != -1) {
        if (!game.scanGoal(scannedGoal)) {
            Serial.println("Already scanned this goal");
            return;
        }

        ledManager.turnOnLight(scannedGoal);
        ledManager.setTwinkle(scannedGoal, true);

        Serial.println("Succesfully scanned goal");
        return;
    }

    int scannedCal = goalManager.getFoundCal();
    if (scannedCal != -1) {
        if (!game.isAllGoalsScanned()) {
            Serial.println("All goals are not scanned");
            return;
        }
        game.scanCal();
        ledManager.doCalAnimation(scannedCal);
        Serial.println("Succesfully scanned cal");
        game.resetGame();
        return;
    }

    // if (uidEqual(lastUid, LED1.rfid)) {
    //     Serial.println("Hello!");
    //     aw.analogWrite(LED1.ledPin, 255);
    // } else {
    //     //    digitalWrite(7, LOW);
    //     aw.analogWrite(5, 0);
    // }
}