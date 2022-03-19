#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <server.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setBackgroundRole(QPalette::Base);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);
    connect(serv, SIGNAL(onReceived()), this, SLOT(onImageReceived()));
}
void MainWindow::onImageReceived() {
    QPixmap newMap = serv->map.scaled(this->size().width() - 20, this->size().height() - 20, Qt::KeepAspectRatio);
    ui->label->setPixmap(newMap);
    ui->label->resize(newMap.size());
}
MainWindow::~MainWindow()
{
    delete ui;
}

