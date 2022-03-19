#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QPixmap>
class Server: public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    bool listen();
    QPixmap map;
private slots:
    void connection();
signals:
    void onReceived();
private:
    QTcpServer *server;
};

#endif // SERVER_H
