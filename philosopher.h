#include "fork.h"

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

class Philosopher
{
private:
    std::chrono::milliseconds eatTime;
    std::chrono::milliseconds sleepTime;
    std::string *message;
    void eat();
    void sleep();
    void changeState();
    std::string state;
    int eatCount = 0;
    Fork *leftFork;
    Fork *rightFork;
    int id;

public:
    Philosopher(int x, std::chrono::milliseconds stime, std::chrono::milliseconds etime, Fork *rfork, Fork *lfork, std::string *messgae);
    void live();
    int getId();
    int getEatCount();
    std::string getState();
};

#endif