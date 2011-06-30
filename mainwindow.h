#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
