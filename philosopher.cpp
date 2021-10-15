#include "philosopher.h"
#include <thread>
#include "globs.h"

using namespace std;

Philosopher::Philosopher(int x, chrono::milliseconds stime, chrono::milliseconds etime, Fork *rfork, Fork *lfork, string *mesge)
{
    this->id = x;
    this->eatTime = etime;
    this->sleepTime = stime;
    this->rightFork = rfork;
    this->leftFork = lfork;
    this->message = mesge;
}

int Philosopher::getId()
{
    return this->id;
}

int Philosopher::getEatCount()
{
    return this->eatCount;
}

void Philosopher::changeState()
{
    *message = "Filozof " + to_string(this->id + 1) + ": " + this->state + ", " + "jadł: " + to_string(this->eatCount) + " krotnie ";
}

string Philosopher::getState()
{
    return this->state;
}

void Philosopher::sleep()
{
    this->state = "śpi";
    changeState();
    this_thread::sleep_for(this->sleepTime);
}

void Philosopher::eat()
{
    if (this->rightFork->getId() != 0)
    {
        this->leftFork->setBusy(true, this->id);
        this->rightFork->setBusy(true, this->id);
    }
    else
    {
        this->rightFork->setBusy(true, this->id);
        this->leftFork->setBusy(true, this->id);
    }
    this->state = "je";
    this->eatCount++;
    changeState();
    this_thread::sleep_for(this->eatTime);

    this->rightFork->setBusy(false, this->id);
    this->leftFork->setBusy(false, this->id);
}

void Philosopher::live()
{
    this->state = "żyje";
    while (true)
    {
        sleep();
        if (continuing)
            eat();
        else
            break;
    }
}
