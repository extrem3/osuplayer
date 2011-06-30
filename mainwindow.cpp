#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColumnView>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <time.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));

    //mouseMaster = new MouseMaster(this, 100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::GetDirectory()
{
    QStandardItem *name = new QStandardItem("Name");
    QStandardItem *firstName = new QStandardItem("First Name");
    QStandardItem *lastName = new QStandardItem("Last Name");

    name->appendRow(firstName);
    name->appendRow(lastName);
    model.appendRow(name);
    ui->clw_dir->setModel(&model);
    return 1;
}

void MainWindow::on_btn_go_clicked()
{
    mouseMaster->SetPosition(int(rand() % 1680), int(rand() % 1080));
    mouseMaster->MoveTo(840, 525, 200);
    QTimer::singleShot(250, mouseMaster, SLOT(Click()));
    //mouseMaster->SetMousePosition(mouseMaster->GetPositionX(), mouseMaster->GetPositionY() - 30);
    //mouseMaster->Click();
}

void MainWindow::MousePositioned()
{
    mouseMaster->SetPosition(15,15);
    QString str;
    str.append(QString("Window at %1x%2").arg(mouseMaster->GetPositionX()).arg(mouseMaster->GetPositionY()));
    ui->lbl_mouse->setText(str);
}

void MainWindow::on_btn_getMousePos_clicked()
{
    ui->lbl_mouse->setText("you have 3 seconds..");
    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(MousePositioned));
    //timer->start(3000);

    //QTimer::singleShot(3000, this, SLOT(MousePositioned()));
}

void MainWindow::on_btn_getOsuDimensions_clicked()
{
    HWND osu_hwnd = FindWindow(TEXT("WindowsForms10.Window.8.app.0.3ce0bb8"), NULL);
    RECT osu_window_dimensions;

    GetWindowRect(osu_hwnd, &osu_window_dimensions);
    osu_window_.x = osu_window_dimensions.left;
    osu_window_.width = osu_window_dimensions.right - osu_window_dimensions.left;
    osu_window_.y = osu_window_dimensions.top;
    osu_window_.height = osu_window_dimensions.bottom - osu_window_dimensions.top;
    ui->lne_x->setText(QString::number(osu_window_.x));
    ui->lne_width->setText(QString::number(osu_window_.width));
    ui->lne_y->setText(QString::number(osu_window_.y));
    ui->lne_height->setText(QString::number(osu_window_.height));
}
