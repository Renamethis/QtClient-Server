#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Инициализация интерфейса
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(loadHandler()));
    connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(sendHandler()));
    ui->label->setBackgroundRole(QPalette::Base);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadHandler() {
    // Загрузка изображения
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog-> setWindowTitle (tr ("Открыть изображение"));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    fileDialog->setViewMode(QFileDialog::Detail);
    QString fileName = fileDialog->getOpenFileName();
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    QImage newImage = reader.read();
    if (newImage.isNull()) {
        return;
    }
    currentImage = QPixmap::fromImage(newImage);
    if(currentImage.isNull()) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Can't read image!");
        messageBox.setFixedSize(500,200);
        messageBox.show();
        return;
    }
    // Форматирование и отображение изображения
    QPixmap previewImage = currentImage.scaled(300, 170, Qt::KeepAspectRatio);
    ui->label->setPixmap(previewImage);
    ui->label->resize(previewImage.size());
    ui->pushButton_3->setEnabled(true);
}
void MainWindow::sendHandler() {
    // Подключение к серверу и отправка
    if(sock.connectToServer(ui->lineEdit->text(), ui->lineEdit_2->text().toInt())) {
        sock.sendImage(currentImage);
    } else {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Can't connect to server!");
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }
}
