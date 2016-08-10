#include "qtcomm.h"

QTComm::QTComm(QObject *parent) : QObject(parent)
{
    mSerialPort = new QSerialPort();
}

QTComm::~QTComm()
{
    delete mSerialPort;
}

void QTComm::init()
{

    mSerialPort->setPortName(QString("/dev/ttyUSB0"));
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
    mSerialPort->write("AT+RXA=0xFF,0xFF,0xFF,0xFF,0xFF");

}

void QTComm::send()
{
    mSerialPort->write("HelloB!");
}
QByteArray QTComm::read()
{
    return mSerialPort->readAll();
}
