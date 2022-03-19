#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    ui->label->setBackgroundRole(QPalette::Base);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonHandler() {

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
    newImage = newImage.scaled(this->size().width() - 20, this->size().height() - 20, Qt::KeepAspectRatio);
    QPixmap map = QPixmap::fromImage(newImage);
    this->ui->label->setPixmap(map);
    this->ui->label->resize(map.size());
    this->sock.connect();
    this->sock.sendImage(map);
}

