#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    mouseMaster = new MouseMaster(this, 100);
    fileParser = new OsuFileParser(QString("asdf"));
    fileParser->AddHitPoint(QString("128,192,7735,1,0"));
    fileParser->AddHitPoint(QString("128,102,7735,1,0"));
    fileParser->AddSlider(QString("184,248,10177,6,2,B|184:248|117:163|184:88,1,150|8"));
    fileParser->AddSlider(QString("320,304,47010,2,0,B|232:304,2,80"));
    fileParser->AddSlider(QString("304,224,58186,2,0,B|344:248|384:224,4,80,0|2|0|2|0"));
    fileParser->AddSpinner(QString("128,2,7735,1,0,44333"));
    fileParser->TraceVector();
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
    //ui->lbl_mouse->setText(str);
}

void MainWindow::on_btn_getOsuDimensions_clicked()
{
    HWND osu_hwnd = FindWindow(TEXT("WindowsForms10.Window.8.app.0.3ce0bb8"), NULL);
    RECT osu_window_dimensions;

    WCHAR str;

    qDebug() << GetWindowText(osu_hwnd, &str, 10);

    GetWindowRect(osu_hwnd, &osu_window_dimensions);
    osu_window_.x = osu_window_dimensions.left + 3;
    osu_window_.width = osu_window_dimensions.right - osu_window_dimensions.left - 6;
    osu_window_.y = osu_window_dimensions.top + 25;
    osu_window_.height = osu_window_dimensions.bottom - osu_window_dimensions.top - 28;

    ui->lbl_x->setText(QString::number(osu_window_.x));
    ui->lbl_width->setText(QString::number(osu_window_.width));
    ui->lbl_y->setText(QString::number(osu_window_.y));
    ui->lbl_height->setText(QString::number(osu_window_.height));

    BringWindowToTop(osu_hwnd);
}

void MainWindow::SongFocused()
{

}
