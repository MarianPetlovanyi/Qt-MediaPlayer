#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "window.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include <thread>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QMediaPlaylist>
#define PATH "/home/marian/Downloads"
static struct VidAud{
    QStringList videos;
    QStringList audios;
//    VidAud();
//    VidAud(QStringList aVideos, QStringList aAudios){
//        videos=aVideos;
//        audios=aAudios;
//    }

} vidAud;
void indexSuppFiles(QString startDir){
    QDir directory(startDir);
    QStringList videos = directory.entryList(QStringList() << "*.mp4",QDir::Files);
    QStringList audios = directory.entryList(QStringList() << "*.mp3",QDir::Files);
    ::vidAud.videos=videos;
    ::vidAud.audios=audios;

}
 MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1000,700);


    QString dir = PATH;
    std::thread thread1(indexSuppFiles,dir);
    thread1.join();



    arr_button_videos = new QPushButton*[::vidAud.videos.size()];
    arr_button_audios = new QPushButton*[::vidAud.audios.size()];


    //createPlayListButton = new QPushButton("Create playlist", this);
    //connect(createPlayListButton, SIGNAL(clicked(bool)), )

    int i=0;
    foreach(QString filename, ::vidAud.videos) {
       QSignalMapper* signalMapper = new QSignalMapper (this) ;
       arr_button_videos[i] = new QPushButton(filename, this);
       arr_button_videos[i]->setGeometry(10,10+i*30,300,30);
       arr_button_videos[i]->setStyleSheet("text-align:left;");
       connect (arr_button_videos[i], SIGNAL(clicked(bool)), signalMapper, SLOT(map())) ;
       signalMapper -> setMapping (arr_button_videos[i], arr_button_videos[i]->text()) ;
       connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(newVideoWindow(QString))) ;
       i++;
      }
    i=0;
    foreach(QString filename, ::vidAud.audios) {
       QSignalMapper* signalMapper = new QSignalMapper (this) ;
       arr_button_audios[i] = new QPushButton(filename, this);
       arr_button_audios[i]->setGeometry(310,10+i*30,300,30);
       arr_button_audios[i]->setStyleSheet("text-align:left;");
       connect (arr_button_audios[i], SIGNAL(clicked(bool)), signalMapper, SLOT(map())) ;
       signalMapper -> setMapping (arr_button_audios[i], arr_button_audios[i]->text()) ;
       connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(newVideoWindow(QString))) ;
       i++;
      }

}
void MainWindow::newVideoWindow(QString file){
    Window *v = new Window(file);
    v -> show();
};
MainWindow::~MainWindow()
{
    delete ui;
}

