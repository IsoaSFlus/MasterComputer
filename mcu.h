#ifndef MCU_H
#define MCU_H

#include <QObject>

class MCU : public QObject
{
    Q_OBJECT

private:
    QString name;

public:
    int id;
    explicit MCU(QObject *parent = 0, int id_in = 0);
    void setName(QString inName);
    QString getName();
signals:



public slots:

};

class MCUs
{
private:
    MCUs()
    {
    }
public:
    static MCUs * mcus()
    {
        static MCUs *m_pInstance;
        if(m_pInstance == NULL) //判断是否第一次调用
            m_pInstance = new MCUs();
        return m_pInstance;
    }
    ~MCUs()
    {
//        delete mcu;
    }
    MCU *mcu[4];
};

#endif // MCU_H
