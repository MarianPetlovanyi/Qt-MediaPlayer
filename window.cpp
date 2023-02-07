#include "window.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDebug>
#include <QDir>
#include <QPushButton>
#include <QSlider>
#include <QProgressBar>
#include <QSignalMapper>
#include <QCheckBox>
#include <QMediaMetaData>
Window::Window(QString file, QWidget *parent) :
    QWidget(parent)
{
    QString name = qgetenv("USER");
        if (name.isEmpty())
            name = qgetenv("USERNAME");


    setFixedSize(1600,1000);
    myfile = file;
    path= "/home/"+name+"/Downloads/%1";
    player = new QMediaPlayer;
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    vw->setParent(this);
    player->setMedia(QUrl::fromLocalFile(path.arg(myfile)));
    vw->setGeometry(0,0,1600,900);
    player->play();
    player->setPlaybackRate(1.0);

    playButton = new QPushButton("Play", this);
    playButton->setGeometry(750,900,100,50);
    connect(playButton, SIGNAL(clicked(bool)), this, SLOT(playVideo()));

    pauseButton = new QPushButton("Pause", this);
    pauseButton->setGeometry(750,950,100,50);
    connect(pauseButton, SIGNAL(clicked(bool)), player, SLOT(pause()));

    rewindButton = new QPushButton("<<", this);
    rewindButton->setGeometry(650,925,100,50);
    connect (rewindButton, SIGNAL(pressed()), this, SLOT(rewindVideo())) ;

    fastForwardButton = new QPushButton(">>", this);
    fastForwardButton->setGeometry(850,925,100,50);
    connect (fastForwardButton, SIGNAL(clicked(bool)), this, SLOT(fastForwardVideo())) ;

    progressBar = new QProgressBar(this);
    progressBar->setGeometry(10,915,600,30);


    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setGeometry(10,945,600,30);

    repeatModeButton = new QPushButton("Repeat - OFF", this);
    repeatModeButton->setGeometry(975, 925, 100, 50);
    connect(repeatModeButton,SIGNAL(clicked()), this, SLOT(repeatModeFunc()));

    returnButton = new QPushButton("Back", this);
    returnButton->setGeometry(1490, 925, 100, 50);
    connect(returnButton, SIGNAL(clicked(bool)),this, SLOT(returnBack()));


    //connect(slider, SIGNAL(valueChanged(int)), progressBar, SLOT (setValue(int)));
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(setValueqint64(qint64));


    connect(player, SIGNAL(positionChanged(qint64)),this, SLOT(setValueProg(qint64)));
    connect (player, SIGNAL(durationChanged(qint64)), this, SLOT(getDuration()));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT (changePos(int)));
}
void Window::rewindVideo(){
    //this->player->setPlaybackRate(-0.5);
    this->changePos(player->position()-5000);
}
void Window::setValueProg(qint64 val){
    this->progressBar->setValue((int)val);
    if(repeatMode==true && player->position()>dur-1200){
        this->changePos(100);
    }
}
void Window::getDuration(){
    this->dur=(int)player->duration();
    progressBar->setRange(0,dur);
    progressBar->setValue(0);
    slider->setRange(0,dur);
    slider->setValue(0);
}
void Window::setValueqint64(qint64 val){
    slider->setValue((int)val);
}
void Window::repeatModeFunc(){
    if(repeatMode==true){
        repeatMode=false;
        repeatModeButton->setText("Repeat - OFF");
        emit setValueProg(player->position());
    }
    else{
        repeatMode=true;
        repeatModeButton->setText("Repeat - ON ");
    }
}
void Window::changePos(int val){
    this->player->setPosition(val);
}
void Window::fastForwardVideo(){
    this->changePos(player->position()+5000);
    //this->player->setPlaybackRate(2.0);
}
void Window::playVideo(){
    this->player->play();
    this->player->setPlaybackRate(1.0);
}
void Window::returnBack(){
    delete(player);
    this->close();
}
