#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <cmath>
#include <thread>
#include <memory>
#include <vector>

#include "globs.h"
#include "philosopher.h"
#include "fork.h"

using namespace std;

bool continuing;

void startPh(Philosopher *ph)
{
    ph->live();
}

int main(int argc, char *argv[])
{
    continuing = true;
    int noPhilosophers = atoi(argv[1]);
    int sleepTime = atoi(argv[2]);
    int eatingTime = atoi(argv[3]);
    vector<string> message(noPhilosophers);

    srand(time(0));
    sleepTime *= 1000;
    eatingTime *= 1000;
    chrono::milliseconds stime(sleepTime);
    chrono::milliseconds etime(eatingTime);
    stime = stime + (chrono::milliseconds)(rand() % 41 - 20) * sleepTime / 100;
    etime = etime + (chrono::milliseconds)(rand() % 41 - 20) * eatingTime / 100;

    shared_ptr<Fork[]> forkArray(new Fork[noPhilosophers]);
    vector<Philosopher> phArray;
    vector<thread> threadArray;

    for (int i = 0; i < noPhilosophers; i++)
    {
        forkArray[i].setId(i);

        if (i != 0)
        {
            phArray.push_back(Philosopher(i, stime, etime, &forkArray[i], &forkArray[i - 1], &message[i]));
        }
        else
        {
            phArray.push_back(Philosopher(i, stime, etime, &forkArray[i], &forkArray[noPhilosophers - 1], &message[i]));
        }
    }
    for (int i = 0; i < noPhilosophers; i++)
    {
        threadArray.push_back(thread(&startPh, &phArray[i]));
    }

    do
    {
        cout << "\033c"; //clear console ESC C
        cout << "Tablica aktualizuje się po wciśnięciu dowolnego przycisku, q- kończy program" << endl
             << endl;
        cout << "Czas spania[ms]: " << stime.count() << endl;
        cout << "Czas jedzenia[ms]: " << etime.count() << endl
             << endl;
        for (int i = 0; i < noPhilosophers; i++)
        {
            cout << "Filozof " << phArray[i].getId() << ": " << phArray[i].getState() << ", jadł: " << phArray[i].getEatCount() << " krotnie" << endl;
        }
        cout << endl;
        for (int i = 0; i < noPhilosophers; i++)
        {
            cout << "Widelec " << forkArray[i].getId() << ": " << forkArray[i].getPhilID() << endl;
        }

    } while (cin.get() != 'q');

    continuing = false;
    cout << "Kończenie pracy programu\n"
         << endl;

    for (int i = 0; i < noPhilosophers; i++)
    {
        threadArray[i].join();
    }
    cout << "**********PODSUMOWANIE**********" << endl;
    for (int i = 0; i < noPhilosophers; i++)
    {
        cout << message[i] << endl;
    }
    return 0;
}
