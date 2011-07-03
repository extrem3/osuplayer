#include "mousemaster.h"

MouseMaster::MouseMaster(QObject *parent, int fps):
    QObject(parent),
    fps_(fps)
{
    dx_ = 0;
    dy_ = 0;
    final_x_ = 0;
    final_y_ = 0;
    fps_times_ = 0;
}
int MouseMaster::GetPositionX()
{
    GetCursorPos(&cursorPos_);
    return cursorPos_.x;
}
int MouseMaster::GetPositionY()
{
    GetCursorPos(&cursorPos_);
    return cursorPos_.y;
}

void MouseMaster::SetPosition(int x, int y)
{
    SetCursorPos(x, y);
}

void MouseMaster::Click()
{
    GetCursorPos(&cursorPos_);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, cursorPos_.x, cursorPos_.y, 0, 0);
}
void MouseMaster::Click(int x, int y)
{
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}

void MouseMaster::PressButton1()
{
    GetCursorPos(&cursorPos_);
    mouse_event(MOUSEEVENTF_LEFTDOWN, cursorPos_.x, cursorPos_.y, 0, 0);
}
void MouseMaster::PressButton1(int x, int y)
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
}
void MouseMaster::ReleaseButton1()
{
    GetCursorPos(&cursorPos_);
    mouse_event(MOUSEEVENTF_LEFTUP, cursorPos_.x, cursorPos_.y, 0, 0);
}
void MouseMaster::ReleaseButton1(int x, int y)
{
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}

void MouseMaster::MoveTo(int x, int y, int time)
{
    //if mover is doing something, dont move mouse.
    if(fps_times_ != 0)
        return;
    fps_times_ = time / (1000 / fps_);
    final_x_ = x;
    final_y_ = y;
    Mover();
}

void MouseMaster::Mover()
{
    --fps_times_;
    if (fps_times_ > 0)
    {
        dx_ = (final_x_ - GetPositionX()) / fps_times_;
        dy_ = (final_y_ - GetPositionY()) / fps_times_;
        SetPosition(GetPositionX() + dx_, GetPositionY() + dy_);
        QTimer::singleShot(1000/fps_, this, SLOT(Mover()));
    }else
    {
        SetPosition(final_x_, final_y_);
    }
}
