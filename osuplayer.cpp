#include "osuplayer.h"

OsuPlayer::OsuPlayer(QObject *parent) :
    QObject(parent)
{
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
    BringWindowToTop(osu_window_hwnd_);
    mouseMaster->MoveTo(15, 15, 200);
}

void OsuPlayer::ProcessSong(QString song_location)
{
    fileParser->ParseFile(song_location);
    song_ = fileParser->GetParsedFile();
    //fileParser->TraceVector(song_);
}
