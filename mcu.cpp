#include "mcu.h"

MCU::MCU(QObject *parent, int id_in) : QObject(parent)
{
    id = id_in;
}

void MCU::setName(QString inName)
{
    name = inName;
}

QString MCU::getName()
{
    return name;
}
