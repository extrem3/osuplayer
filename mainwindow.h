#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <windows.h>
#include "mousemaster.h"

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
    MouseMaster *mouseMaster;
    QTimer *timer;
public slots:
        int GetDirectory();
        void MousePositioned();

private slots:
        void on_btn_go_clicked();
        void on_btn_getMousePos_clicked();
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
