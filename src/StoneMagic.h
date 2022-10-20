#ifndef STONE_MAGIC_H
#define STONE_MAGIC_H

class StoneMagic {
   public:
    StoneMagic();                     // consturctor
    bool isGameStarted();             // is the game started
    void resetGame();                 // turns off all the lights
    bool scanGoal(int goalNum);       // turns on light for specific goal
    bool isGoalScanned(int goalNum);  // returns if the goal has been met
    bool scanCal();
    bool isGameFinished();
    bool isAllGoalsScanned();

   private:
    bool goals[8];
    bool calScanned;
};

#endif
