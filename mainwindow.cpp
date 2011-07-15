#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    osuPlayer = new OsuPlayer(this);
    GetDirectory();
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
        if (song != "." && song != "..")
        {
            QStandardItem *songName = new QStandardItem();
            songName->setData(song, Qt::AccessibleDescriptionRole);
            songName->setData(ExtractSongName(song), Qt::DisplayRole);
            QDir dir_songs(ui->lne_dir->text() + "/songs/" + song);
            foreach (QString difficulty, dir_songs.entryList())
            {
                if (difficulty.endsWith(".osu"))
                {
                    QStandardItem *difficultyName = new QStandardItem();
                    difficultyName->setData(difficulty, Qt::AccessibleDescriptionRole);
                    difficultyName->setData(ExtractSongDifficulty(difficulty), Qt::DisplayRole);
                    songName->appendRow(difficultyName);
                }
            }
            model.appendRow(songName);
        }
    }
    model.sort(0);
    ui->clw_dir->setModel(&model);
    return 1;
}

void MainWindow::on_btn_go_clicked()
{
    HWND osu_hwnd = FindWindow(TEXT("WindowsForms10.Window.8.app.0.3ce0bb8"), NULL);
    RECT osu_window_dimensions;

    GetWindowRect(osu_hwnd, &osu_window_dimensions);
    osu_window_.x = osu_window_dimensions.left + 3 + 240;
    osu_window_.width = osu_window_dimensions.right - osu_window_dimensions.left - 6 - 480;
    osu_window_.y = osu_window_dimensions.top + 25 + 100;
    osu_window_.height = osu_window_dimensions.bottom - osu_window_dimensions.top - 28 - 200;

    osuPlayer->SetHwnd(osu_hwnd);
    osuPlayer->SetWindowSize(osu_window_);
    osuPlayer->SetDelay(QString(ui->lne_delay->text()).toInt());

    osuPlayer->ProcessSong(GetFullDirectoryPath());

    osuPlayer->Play();
}

QString MainWindow::GetFullDirectoryPath()
{
    QModelIndex item = ui->clw_dir->currentIndex();
    return ui->lne_dir->text() + "/Songs/" +
           item.parent().data(Qt::AccessibleDescriptionRole).toString() +
           "/" + item.data(Qt::AccessibleDescriptionRole).toString();
}

QString MainWindow::ExtractSongName(QString full_path)
{
    full_path.remove(0, full_path.indexOf(" "));
    return full_path;
}

QString MainWindow::ExtractSongDifficulty(QString full_name)
{
    full_name.remove(0, full_name.lastIndexOf("[") + 1);
    full_name.remove(full_name.lastIndexOf("]"), full_name.length());
    return full_name;
}
