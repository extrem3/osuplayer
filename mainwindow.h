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
    WindowDimensions osu_window_;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QStandardItemModel model;
    OsuFileParser *fileParser;
    OsuPlayer *osuPlayer;
    QTimer *timer;
    QString ExtractSongName(QString full_path);
    QString ExtractSongDifficulty(QString full_name);
public slots:
    int GetDirectory();
    QString GetFullDirectoryPath();
private slots:
    void on_btn_go_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
