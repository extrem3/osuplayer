#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    osuPlayer = new OsuPlayer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::GetDirectory()
{
    QDir dir(ui->lne_dir->text() + "/songs/");
    if (!dir.isReadable())
        return 0;

    foreach (QString song, dir.entryList())
    {
        QStandardItem *songName = new QStandardItem(song);
        QDir dir_songs(ui->lne_dir->text() + "/songs/" + song);
        foreach (QString difficulty, dir_songs.entryList())
        {
            if (difficulty.endsWith(".osu"))
            {
                QStandardItem *difficultyName = new QStandardItem(difficulty);
                songName->appendRow(difficultyName);
            }
        }
        model.appendRow(songName);
    }

    ui->clw_dir->setModel(&model);
    return 1;
}

void MainWindow::on_btn_go_clicked()
{
    osuPlayer->ProcessSong(QString("D:/games/osu/Songs/6358 Toyosaki Aki - Cagayake! GIRLS (TV Size)/Toyosaki Aki - Cagayake! GIRLS (TV Size) (DJPop) [Insane].osu"));
    osuPlayer->Play();
}

void MainWindow::on_btn_getOsuDimensions_clicked()
{
    HWND osu_hwnd = FindWindow(TEXT("WindowsForms10.Window.8.app.0.3ce0bb8"), NULL);
    RECT osu_window_dimensions;

    WCHAR str;

    qDebug() << GetWindowText(osu_hwnd, &str, 10);

    GetWindowRect(osu_hwnd, &osu_window_dimensions);
    osu_window_.x = osu_window_dimensions.left + 3 + 240;
    osu_window_.width = osu_window_dimensions.right - osu_window_dimensions.left - 6 - 480;
    osu_window_.y = osu_window_dimensions.top + 25 + 100;
    osu_window_.height = osu_window_dimensions.bottom - osu_window_dimensions.top - 28 - 200;

    /*ui->lbl_x->setText(QString::number(osu_window_.x - 240));
    ui->lbl_width->setText(QString::number(osu_window_.width + 480));
    ui->lbl_y->setText(QString::number(osu_window_.y - 100));
    ui->lbl_height->setText(QString::number(osu_window_.height + 200));*/

    ui->lbl_x->setText(QString::number(osu_window_.x));
    ui->lbl_width->setText(QString::number(osu_window_.width));
    ui->lbl_y->setText(QString::number(osu_window_.y));
    ui->lbl_height->setText(QString::number(osu_window_.height));

    osuPlayer->SetHwnd(osu_hwnd);
    osuPlayer->SetWindowSize(osu_window_);
}

void MainWindow::SongFocused()
{

}
