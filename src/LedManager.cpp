#include "LedManager.h"

LedManager::LedManager(Adafruit_AW9523* controller) : aw(controller) {
    // this->aw = controller; same as : aw(controller)
}

void LedManager::turnOnLight(int goalNum, uint8_t brightness) {
    aw->analogWrite(GOALS[goalNum].ledPin, brightness);
    this->led[goalNum] = brightness > LED_MIN;
}

void LedManager::turnOffLight(int goalNum) {
    if (!this->led[goalNum]) {
        return;
    }
    this->turnOnLight(goalNum, LED_MIN);
}

void LedManager::setAllLightsBrightness(uint8_t brightness) {
    for (int i = 0; i < GOAL_COUNT; i++) {
        this->turnOnLight(i, brightness);
    }
}

void LedManager::setTwinkle(int goalNum, bool value) {
    this->twinkles[goalNum] = value;
}

void LedManager::twinkle(int goalNum) {
    int t = random(LED_TWINKLE_MIN, LED_TWINKLE_MAX);
    this->turnOnLight(goalNum, t);
}

void LedManager::doTwinkles() {
    for (int i = 0; i < GOAL_COUNT; i++) {
        if (!this->led[i]) {
            continue;
        }
        if (random(0, 100) < 75) {
            continue;
        }
        this->twinkle(i);
    }
}

void LedManager::fadeAllOut(float seconds) {
    Serial.println("fadeAllOut");
    this->setAllLightsBrightness(LED_MAX);
    unsigned long start = millis();
    unsigned long end = start + (seconds * 1000);
    unsigned long total = end - start;
    unsigned long now = millis();
    do {
        float pct = (float)(end - now) / (float)total;
        int val = (LED_MAX * pct);
        this->setAllLightsBrightness(val);
        now = millis();
    } while (now < end);
}

void LedManager::fadeAllIn(float seconds) {
    Serial.println("fadeAllIn");
    this->setAllLightsBrightness(LED_MIN);
    unsigned long start = millis();
    unsigned long end = start + (seconds * 1000);
    unsigned long total = end - start;
    unsigned long now = millis();
    do {
        float pct = (float)(end - now) / (float)total;
        int val = LED_MAX - (LED_MAX * pct);
        this->setAllLightsBrightness(val);
        now = millis();
    } while (now < end);
}

int LedManager::spin(float seconds, int startGoalNum, float spinDelay, int stopGoalNum) {
    Serial.println("spin");
    unsigned long start = millis();
    unsigned long end = start + (seconds * 1000);
    unsigned long total = end - start;
    unsigned long now = millis();
    int goalNum = startGoalNum;
    do {
        for (int i = 0; i < GOAL_COUNT; i++) {
            if (i != goalNum) {
                this->turnOffLight(i);
                continue;
            }
            this->turnOnLight(goalNum, LED_MAX);
        }
        delay(1000 * spinDelay);
        if (goalNum == stopGoalNum) {
            break;
        }
        goalNum++;
        if (goalNum >= GOAL_COUNT) {
            goalNum = 0;
        }
        now = millis();
    } while (now < end);
    return goalNum;
}

void LedManager::doCalAnimation(int goalNum) {
    Serial.println("Cal animation start");
    this->fadeAllOut(3);
    this->fadeAllIn(2.5);
    this->fadeAllOut(2);
    this->fadeAllIn(1.5);
    this->fadeAllOut(1);
    this->fadeAllIn(0.5);
    this->fadeAllOut(0.5);
    this->fadeAllIn(0.5);
    this->fadeAllOut(0.25);
    this->fadeAllIn(0.25);
    this->fadeAllOut(0.25);
    this->fadeAllIn(0.25);
    this->fadeAllOut(0.25);
    this->fadeAllOut(0.25);
    this->fadeAllIn(0.10);
    this->fadeAllOut(0.10);
    this->fadeAllIn(0.10);
    this->fadeAllOut(0.10);
    this->fadeAllIn(0.10);
    this->fadeAllOut(0.10);
    this->fadeAllIn(0.10);
    this->fadeAllOut(0.10);
    this->fadeAllIn(0.10);
    this->fadeAllOut(0.10);
    this->fadeAllIn(0.10);
    this->fadeAllOut(0.10);
    this->fadeAllIn(0.10);
    this->fadeAllOut(0.10);
    this->fadeAllIn(0.10);
    this->fadeAllOut(0.10);
    this->setAllLightsBrightness(LED_MIN);
    delay(1);
    int spinNum = this->spin(2, 0, 0.2);
    spinNum = this->spin(2, spinNum, 0.1);
    spinNum = this->spin(2, spinNum, 0.075);
    spinNum = this->spin(2, spinNum, 0.050);
    spinNum = this->spin(2, spinNum, 0.025);
    spinNum = this->spin(10, spinNum, 0.025, goalNum);
    delay(5000);
    this->setAllLightsBrightness(LED_MIN);
    Serial.println("Cal animation end");
}