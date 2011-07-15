#include "timer.h"

AccurateTimer::AccurateTimer()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        qDebug() << "QueryPerformanceFrequency failed!\n";

    pc_frequency_ = static_cast<double>(li.QuadPart)/1000.0;
    QueryPerformanceCounter(&li);
    counter_ = li.QuadPart;
}

void AccurateTimer::Start()
{
}
void AccurateTimer::Stop()
{
}
int AccurateTimer::GetMiliseconds()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return static_cast<double>(li.QuadPart - counter_)/pc_frequency_;
}
