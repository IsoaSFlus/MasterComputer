#include "mcu.h"

MCU::MCU(QObject *parent) : QObject(parent)
{

}

void MCU::setName(QString inName)
{
    name = inName;
}
