#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QImageReader>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <socket.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void loadHandler();
    void sendHandler();

private:
    QPixmap currentImage;
    Ui::MainWindow *ui;
    Socket sock;
};
#endif // MAINWINDOW_H
