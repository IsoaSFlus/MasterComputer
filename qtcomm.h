#ifndef QTCOMM_H
#define QTCOMM_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QDebug>

class QTComm : public QObject
{
    Q_OBJECT
private:
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
public:
    QSerialPort *mSerialPort;
    explicit QTComm(QObject *parent = 0);
    ~QTComm();
    void init();
    QByteArray read();
signals:

public slots:
    void send();
};

#endif // QTCOMM_H
