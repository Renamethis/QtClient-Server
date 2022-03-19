#include "server.h"

Server::Server(QObject *parent) :
    QObject(parent)
{
    // Инициализация сервера
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(connection()));
}
bool Server::listen() {
    if(!server->listen(QHostAddress::Any, 80)) {
        return false;
    }
    return true;
}
void Server::connection() {
    QTcpSocket *socket = server->nextPendingConnection();
    if(socket->waitForReadyRead()) {
        // Чтение размера массива байт
        QByteArray bytearray = socket->read(8);
        QDataStream ds(bytearray);
        qint64 length;
        ds >> length;
        // Чтение массива байт
        QByteArray imageArray;
        while(socket->bytesAvailable() < length) {
            if(socket->waitForReadyRead()) {
                QByteArray buf = socket->read(length);
                imageArray.append(buf);
                length -= buf.size();
            }
        }
        // Преобразование QByteArray к QPixmap для отображения
        map.loadFromData(imageArray, "PNG");
        emit(onReceived());
    }
    socket->close();
}
