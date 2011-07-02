#ifndef OSUPLAYER_H
#define OSUPLAYER_H

#include <QObject>
#include <QString>
#include <windows.h>
#include "mousemaster.h"
#include "osufileparser.h"

class OsuPlayer : public QObject
{
    Q_OBJECT
    MouseMaster *mouseMaster;
    OsuFileParser *fileParser;
    HWND osu_window_hwnd_;
    std::vector< HitPointDetails > song_;
public:
    explicit OsuPlayer(QObject *parent = 0);
    ~OsuPlayer();
    void SetHwnd(HWND osu_hwnd);
    void ProcessSong(QString song_location);
signals:

public slots:

};

#endif // OSUPLAYER_H
