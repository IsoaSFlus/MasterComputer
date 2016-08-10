#ifndef MCU_H
#define MCU_H

#include <QObject>

class MCU : public QObject
{
    Q_OBJECT
private:
    QString name;
public:
    explicit MCU(QObject *parent = 0);
    void setName(QString inName);

signals:

public slots:
};

#endif // MCU_H
