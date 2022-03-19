#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QPixmap>
#include <QBuffer>
class Socket: public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = 0);
    void sendImage(QPixmap &img);
    bool connect();
private:
    QTcpSocket *socket;
};

#endif // SOCKET_H
