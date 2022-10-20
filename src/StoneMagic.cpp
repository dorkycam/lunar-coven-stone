#include "StoneMagic.h"

#include "rfid_lights.h"

StoneMagic::StoneMagic() {
    this->resetGame();
}

bool StoneMagic::isGameStarted() {
    for (int i = 0; i < GOAL_COUNT; i++) {
        if (this->goals[i]) {
            return true;
        }
    }
    return false;
}

bool StoneMagic::isAllGoalsScanned() {
    for (int i = 0; i < GOAL_COUNT; i++) {
        if (!this->goals[i]) {
            return false;
        }
    }
    return true;
}

void StoneMagic::resetGame() {
    for (int i = 0; i < GOAL_COUNT; i++) {
        this->goals[i] = false;
    }
    this->calScanned = false;
}

bool StoneMagic::scanCal() {
    this->calScanned = true;
    return true;
}

bool StoneMagic::isGameFinished() {
    return this->calScanned;
}

bool StoneMagic::scanGoal(int goalNum) {
    if (this->goals[goalNum]) {
        return false;
    }
    this->goals[goalNum] = true;
    return true;
}

bool StoneMagic::isGoalScanned(int goalNum) {
    return this->goals[goalNum];
}
