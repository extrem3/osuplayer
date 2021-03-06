#ifndef MOUSEMASTER_H
#define MOUSEMASTER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <windows.h>
#include "timer.h"

class MouseMaster : public QObject
{
    Q_OBJECT
    POINT cursorPos_;
    int fps_;
    int final_x_;
    int final_y_;
    signed int dx_;
    signed int dy_;
    int fps_times_;
public:
    MouseMaster(QObject *parent, int fps);
    ~MouseMaster() {}

    int GetPositionX();
    int GetPositionY();
    void SetPosition(int x, int y);
    void Click(int x, int y);
    void PressButton1(int x, int y);
    void ReleaseButton1(int x, int y);
    void MoveTo(int x, int y, int time);
public slots:
    void Click();
    void PressButton1();
    void ReleaseButton1();
    void Mover();
};

#endif // MOUSEMASTER_H
