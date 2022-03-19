#include "socket.h"

Socket::Socket(QObject *parent) :
    QObject(parent)
{

}
void Socket::sendImage(QPixmap &img) {
    QByteArray ba;
    QBuffer buffer(&ba);
    img.save(&buffer, "PNG");
    QBuffer buf;
    buf.open(QBuffer::ReadWrite);
    QDataStream stream(&buf);
    qint64 v = buffer.size();
    stream << v;
    QByteArray arr=buf.buffer();
    qDebug() << buffer.size();
    socket->write(arr);
    socket->write(ba);
    if(socket->waitForBytesWritten()) {
    }
}
bool Socket::connect() {
    this->socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 80);
    if(socket->waitForConnected()) {
        return true;
    }
    return false;
}
