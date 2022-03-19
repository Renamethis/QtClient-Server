#include "server.h"

Server::Server(QObject *parent) :
    QObject(parent)
{
    this->server = new QTcpServer(this);
    connect(this->server, SIGNAL(newConnection()), this, SLOT(connection()));
    if(!server->listen(QHostAddress::Any, 80)) {
        return;
    }
}
void Server::connection() {
    QTcpSocket *socket = server->nextPendingConnection();
    if(socket->waitForReadyRead()) {
        QByteArray bytearray = socket->read(8);
        QDataStream ds(bytearray);
        qint64 length;
        ds >> length;
        qDebug() << bytearray;
        QByteArray imageArray;
        while(socket->bytesAvailable() < length) {
            if(socket->waitForReadyRead()) {
                QByteArray buf = socket->read(length);
                imageArray.append(buf);
                length -= buf.size();
            }
        }
        qDebug() << imageArray.size();
        map.loadFromData(imageArray, "PNG");
        emit(onReceived());
    }
    socket->close();
}
