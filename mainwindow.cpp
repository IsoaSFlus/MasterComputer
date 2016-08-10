#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qtcomm = new QTComm(this);
    qtcomm->init();
    connect(qtcomm->mSerialPort, &QSerialPort::readyRead, this, &MainWindow::showLog);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete qtcomm;
}

void MainWindow::on_pushButton_clicked()
{
    qtcomm->send();
}

void MainWindow::showLog()
{
    if(qtcomm->read() == QString("WARNING"))
    {
        QString log;
        log = QString("地点A发出警报\n");
        QDateTime  time = QDateTime::currentDateTime();
        QString current_date = time.toString("yyyy-MM-dd hh:mm  ");
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + current_date + buf +log);
    }
}
