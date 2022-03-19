#include "socket.h"

Socket::Socket(QObject *parent) :
    QObject(parent) {}
void Socket::sendImage(QPixmap &img) {
    // Преобразование изображения в ByteArray
    QByteArray ba;
    QBuffer imageBuffer(&ba);
    img.save(&imageBuffer, "PNG");
    // Вычисление размера полученного ByteArray
    QBuffer lengthBuffer;
    lengthBuffer.open(QBuffer::ReadWrite);
    QDataStream stream(&lengthBuffer);
    qint64 v = imageBuffer.size();
    stream << v;
    QByteArray arr=lengthBuffer.buffer();
    qDebug() << imageBuffer.size();
    // Отправка размера и самого массива байт
    socket->write(arr);
    socket->write(ba);
}
bool Socket::connectToServer(QString adress, int port) {
    socket = new QTcpSocket(this);
    socket->connectToHost(adress, port);
    if(socket->waitForConnected()) {
        return true;
    }
    return false;
}
