#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Инициализация интерфейса
    ui->setupUi(this);
    ui->label->setBackgroundRole(QPalette::Base);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(startHandler()));
}
void MainWindow::onImageReceived() {
    // Отображение изображения
    QPixmap newMap = serv->map.scaled(this->size().width() - 5, this->size().height() - 10, Qt::KeepAspectRatio);
    ui->label->setPixmap(newMap);
    ui->label->resize(newMap.size());
}
void MainWindow::startHandler() {
    // Инициализация сервера и подключение
    serv = new Server();
    if(serv->listen()) {
        connect(serv, SIGNAL(onReceived()), this, SLOT(onImageReceived()));
        ui->pushButton->setEnabled(false);
    } else {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Can't start server!");
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

