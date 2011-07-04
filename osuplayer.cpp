#include "osuplayer.h"

OsuPlayer::OsuPlayer(QObject *parent) :
    QObject(parent)
{
    current_song_progress_ = 0;
    mouseMaster = new MouseMaster(this, 100);
    fileParser = new OsuFileParser();
    delay_ = 570;
}
OsuPlayer::~OsuPlayer()
{
    delete mouseMaster;
    delete fileParser;
}

void OsuPlayer::SetHwnd(HWND osu_hwnd)
{
    osu_window_hwnd_ = osu_hwnd;
}

void OsuPlayer::SetWindowSize(WindowDimensions osu_window_dimensions)
{
    osu_window_dimensions_ = osu_window_dimensions;
}
void OsuPlayer::SetDelay(int delay)
{
    delay_ = delay;
}

void OsuPlayer::ProcessSong(QString song_location)
{
    fileParser->ParseFile(song_location);
    song_ = fileParser->GetParsedFile();
    fileParser->TraceVector(song_);
}

void OsuPlayer::Play()
{
    current_song_progress_ = 0;
    BringWindowToTop(osu_window_hwnd_);
    mouseMaster->SetPosition(osu_window_dimensions_.x + osu_window_dimensions_.width + 100,
                        osu_window_dimensions_.y + osu_window_dimensions_.height + 50);
    QTimer::singleShot(150, mouseMaster, SLOT(Click()));
    song_started_timer_ = new QTimer(this);
    connect(song_started_timer_, SIGNAL(timeout()), this, SLOT(RealSongStart()));
    song_started_timer_->start(10);
}
void OsuPlayer::RealSongStart()
{
    // song has to be loaded, so we have to keep on checking if it's loaded.
    // the title of window changes in when the song is loaded.
    TCHAR  window_title[11];
    if (GetWindowText(osu_window_hwnd_, window_title, 10) == 9)
    {
        song_started_timer_->stop();
        delete song_started_timer_;

        SetUpTimers();
    }
}

void OsuPlayer::SetUpTimers()
{
    current_object_=  0;
    std::vector<HitPointDetails>::iterator i = song_.begin();
    for (int j = 0; i != song_.end() && j < 300; ++i, ++j)
    {
        QTimer::singleShot((*i).time + delay_, this, SLOT(HitObjectTime()));
    }
}

void OsuPlayer::HitObjectTime()
{
    // make sure you have in-game sensitivity set to 1x
    int new_x = ((song_[current_object_].x) * osu_window_dimensions_.width) + osu_window_dimensions_.x;
    int new_y = ((song_[current_object_].y) * osu_window_dimensions_.height) + osu_window_dimensions_.y;
    mouseMaster->SetPosition(new_x, new_y);
    if (song_[current_object_].type == 1)
    {
        mouseMaster->Click();
    }else if (song_[current_object_].type == 2)
    {
        mouseMaster->PressButton1();
    }else
    {
        mouseMaster->ReleaseButton1();
    }
    current_object_ ++;
}
