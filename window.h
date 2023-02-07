#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
class QPushButton;
class QProgressBar;
class QSlider;
class QMediaPlayer;
class QVideoWidget;
class QString;
class QCheckBox;
class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QString, QWidget *parent = nullptr);

private slots:
    void rewindVideo();
    void fastForwardVideo();
    void changePos(int val);
    void getDuration();
    void setValueqint64(qint64);
    void setValueProg(qint64);
    void playVideo();
    void returnBack();
    void repeatModeFunc();
private:
    QMediaPlayer* player;
    QVideoWidget* vw;
    QString videoName;
    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* rewindButton;
    QPushButton* fastForwardButton;
    QPushButton* seekButton;
    QSlider* slider;
    QProgressBar* progressBar;
    QPushButton* repeatModeButton;
    QPushButton* returnButton;
    QString path, myfile;
    int dur;
    bool repeatMode=false;
};

#endif // WINDOW_H
