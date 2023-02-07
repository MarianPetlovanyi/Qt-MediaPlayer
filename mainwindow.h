#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QPushButton;
class QString;
class QGroupBox;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void newVideoWindow(QString file);
private:
    Ui::MainWindow *ui;
    QString dir;
    QGroupBox *videoBox;
    QGroupBox *audioBox;
    QPushButton** arr_button_videos;
    QPushButton** arr_button_audios;
    QPushButton* createPlayListButton;
};
#endif // MAINWINDOW_H
