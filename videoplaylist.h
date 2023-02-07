#ifndef VIDEOPLAYLIST_H
#define VIDEOPLAYLIST_H
#include <QMediaPlaylist>
class QString;
class QMediaPlaylist;

class VideoPlayList
{
public:
    VideoPlayList();
private:
    QString name;
    QMediaPlaylist playlist;
};

#endif // VIDEOPLAYLIST_H
