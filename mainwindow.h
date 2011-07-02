#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QColumnView>
#include <QString>
#include <QTimer>
#include <QDir>
#include <QDebug>
#include <windows.h>
#include "osufileparser.h"
#include "osuplayer.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QStandardItemModel model;
    OsuFileParser *fileParser;
    OsuPlayer *osuPlayer;
    QTimer *timer;
public slots:
        int GetDirectory();
        void SongFocused();

private slots:
        void on_btn_go_clicked();
        void on_btn_getOsuDimensions_clicked();


private:
    Ui::MainWindow *ui;
    struct window_dimensions
    {
        int x;
        int y;
        int width;
        int height;
    } osu_window_;
};

#endif // MAINWINDOW_H
