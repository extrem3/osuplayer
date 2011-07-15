#include "osuplayer.h"

OsuPlayer::OsuPlayer(QObject *parent) :
    QObject(parent)
{
    current_song_progress_ = 0;
    mouseMaster = new MouseMaster(this, 100);
    fileParser = new OsuFileParser();
    delay_ = 30;
    real_song_timer_ = new QTimer(this);
    connect(real_song_timer_, SIGNAL(timeout()), this, SLOT(HitObjectTime()));
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
    fileParser->SetWindowSize(osu_window_dimensions);
}
void OsuPlayer::SetDelay(int delay)
{
    delay_ = delay + fileParser->GetAudioDelay();
}

void OsuPlayer::ProcessSong(QString song_location)
{
    fileParser->ParseFile(song_location);
    song_ = fileParser->GetParsedFile();
}

void OsuPlayer::Play()
{
    current_song_progress_ = 0;
    BringWindowToTop(osu_window_hwnd_);
    mouseMaster->SetPosition(osu_window_dimensions_.x + osu_window_dimensions_.width + 100,
                             osu_window_dimensions_.y + osu_window_dimensions_.height + 50);
    QTimer::singleShot(150, mouseMaster, SLOT(Click()));
    QTimer::singleShot(170, this, SLOT(RealSongStart()));
}
void OsuPlayer::RealSongStart()
{
    // song has to be loaded, so we have to keep on checking if it's loaded.
    // the title of window changes in when the song is loaded.
    current_object_ = 0;
    TCHAR window_title_[11];
    for ( ; ; )
    {
        if (GetWindowText(osu_window_hwnd_, window_title_, 10) == 9)
        {
            break;
        }
    }
    HitObjectTime();
}

void OsuPlayer::SetUpTimers()
{
    current_object_ = 0;
    //QTimer::singleShot(0, this, SLOT(HitObjectTime()));

}

void OsuPlayer::HitObjectTime()
{
    //qDebug() << "starting";
    song_playing_time_ = new AccurateTimer();

    TCHAR window_title_[101];
    for ( ; ; )
    {
        if (song_playing_time_->GetMiliseconds() >= song_[current_object_].time + delay_)
        {
            //qDebug() << song_playing_time_->GetMiliseconds() << " x " << song_[current_object_].time + delay_;
            // make sure you have in-game sensitivity set to 1x
            mouseMaster->SetPosition(song_[current_object_].x, song_[current_object_].y);
            if (song_[current_object_].type == 1)
            {
                mouseMaster->Click();
            }else if (song_[current_object_].type == 2)
            {
                //mouseMaster->PressButton1();
            }else
            {
                //mouseMaster->ReleaseButton1();
            }
            ++current_object_;
            if (current_object_ >= song_.size())
            {
                break;
            }
            GetWindowText(osu_window_hwnd_, window_title_, 100);
            for (int i = 0; i < 100; ++i)
            {
                if (window_title_[i + 1] == '\0')
                {
                    break;
                }
                if (window_title_[i] == 'F' && window_title_[i + 1] == 'a')
                {
                    return;
                }
            }
        }
    }
}
