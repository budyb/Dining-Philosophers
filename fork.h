#include <mutex>

#ifndef FORK_H
#define FORK_H

class Fork
{
private:
    int id;
    int philID = -1;
    bool busy = false;
    std::mutex mutexLock;

public:
    int getId();
    void setId(int Forkid);
    void setBusy(bool occupied, int id);
    std::string getPhilID();
};

#endif