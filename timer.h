#ifndef TIMER_H
#define TIMER_H

#include <QDebug>
#include <windows.h>

class AccurateTimer
{
    double pc_frequency_;
    __int64 counter_;
public:
    AccurateTimer();
    void Start();
    int GetMiliseconds();
    void Stop();
};

#endif // TIMER_H
