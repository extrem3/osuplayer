#include "osuplayer.h"

OsuPlayer::OsuPlayer(QObject *parent) :
    QObject(parent)
{
    current_song_progress_ = 0;
    mouseMaster = new MouseMaster(this, 100);
    fileParser = new OsuFileParser();
}
OsuPlayer::~OsuPlayer()
{
    delete mouseMaster;
    delete fileParser;
}

void OsuPlayer::SetHwnd(HWND osu_hwnd)
{
    osu_window_hwnd_ = osu_hwnd;
    //mouseMaster->MoveTo(15, 15, 2000);
}

void OsuPlayer::SetWindowSize(WindowDimensions osu_window_dimensions)
{
    osu_window_dimensions_ = osu_window_dimensions;
}

void OsuPlayer::ProcessSong(QString song_location)
{
    fileParser->ParseFile(song_location);
    song_ = fileParser->GetParsedFile();
    //fileParser->TraceVector(song_);
}

void OsuPlayer::Play()
{
    current_song_progress_ = 0;
    BringWindowToTop(osu_window_hwnd_);
    mouseMaster->MoveTo(osu_window_dimensions_.x + osu_window_dimensions_.width - 10,
                        osu_window_dimensions_.y + osu_window_dimensions_.height - 10,
                        100);
    QTimer::singleShot(150, mouseMaster, SLOT(PressButton1()));
    song_started_timer_ = new QTimer(this);
    connect(song_started_timer_, SIGNAL(timeout()), this, SLOT(RealSongStart()));
    song_started_timer_->start(50);
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

        mouseMaster->MoveTo(100, 100, 200);
    }
}
