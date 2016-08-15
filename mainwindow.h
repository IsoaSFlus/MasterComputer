#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QDialog>
#include <QDateTime>
#include <QtSerialPort/QSerialPortInfo>
#include <QCloseEvent>
#include "qtcomm.h"
#include "mcu.h"
#include "setnamedialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateLabel();
    void setName();
    void saveLog();
private slots:
    void on_pushButton_clicked();
    void showLog();
private:
    MCUs *mcus;
    QAction *setNameAction;
    Ui::MainWindow *ui;
    QTComm *qtcomm;
    QString buf;
};

#endif // MAINWINDOW_H
