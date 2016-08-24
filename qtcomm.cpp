#include "qtcomm.h"

QTComm::QTComm(QObject *parent) : QObject(parent)
{
    mSerialPort = new QSerialPort();
}

QTComm::~QTComm()
{
    delete mSerialPort;
}

void QTComm::openSerialPort(QString portName)
{

    mSerialPort->setPortName(portName);
    mSerialPort->setBaudRate(QSerialPort::Baud9600);    //波特率
    mSerialPort->setDataBits(QSerialPort::Data8);
    mSerialPort->setParity(QSerialPort::NoParity);
    mSerialPort->setStopBits(QSerialPort::OneStop);
    mSerialPort->setFlowControl(QSerialPort::NoFlowControl);
    mSerialPort->setReadBufferSize(1024);
    if(mSerialPort->open(QSerialPort::ReadWrite))
        qDebug() <<"ok";
    else
        qDebug() <<"false";
//    mSerialPort->write("AT+RXA=0xFF,0xFF,0xFF,0xFF,0xFF");
//    mSerialPort->write("AT+RATE=2");
//    mSerialPort->write("AT+FREQ=2.440G");
}

void QTComm::send()
{
    mSerialPort->write("HelloB!");
}
QByteArray QTComm::read()
{
    return mSerialPort->readAll();
}
//AT+RXA=0XE7,0XE7,0XE7,0XE7,0XE7
