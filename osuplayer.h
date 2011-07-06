#ifndef OSUPLAYER_H
#define OSUPLAYER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <windows.h>
#include "mousemaster.h"
#include "osufileparser.h"


class OsuPlayer : public QObject
{
    Q_OBJECT
    MouseMaster *mouseMaster;
    OsuFileParser *fileParser;
    QTimer *real_song_timer_;
    HWND osu_window_hwnd_;
    WindowDimensions osu_window_dimensions_;
    int delay_;
    int current_song_progress_;
    std::vector< HitPointDetails > song_;
    bool song_started_;
    QTimer *song_started_timer_;
    int current_object_;
public:
    explicit OsuPlayer(QObject *parent = 0);
    ~OsuPlayer();
    void SetHwnd(HWND osu_hwnd);
    void SetWindowSize(WindowDimensions osu_window_dimensions);
    void SetDelay(int delay);
    void ProcessSong(QString song_location);
    void Play();
private slots:
    void RealSongStart();
    void SetUpTimers();
    void HitObjectTime();
};

#endif // OSUPLAYER_H
