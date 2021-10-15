#include "fork.h"

using namespace std;

int Fork::getId()
{
    return id;
}

void Fork::setId(int forkID)
{
    this->id = forkID;
}

void Fork::setBusy(bool busy, int philID)
{
    if (busy)
    {
        mutexLock.lock();
        this->philID = philID;
        this->busy = true;
    }
    else
    {
        mutexLock.unlock();
        this->philID = -1;
        this->busy = false;
    }
}

string Fork::getPhilID()
{
    if (busy)
        return "Filozof " + to_string(philID);
    else
        return "Wolny";
}
