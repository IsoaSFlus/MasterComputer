#include "fadeanimation.h"

FadeAnimation::FadeAnimation(QObject *parent, QLabel *label) : QObject(parent)
{
    effect = new QGraphicsOpacityEffect();
//    effect->setOpacity(opacity);
//    label->setGraphicsEffect(effect);
    opacity = 1.0;
    step = 0.02;
    alert_flag = 0;
    unalert_flag = 0;
    unalert_flag_2 = 0;
    onalert_flag = 0;
    this->label = label;
    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &FadeAnimation::fade);

}

void FadeAnimation::start()
{
    alert_flag = 1;
    timer->start(20);
}

void FadeAnimation::stop()
{
    if(onalert_flag == 1)
        unalert_flag = 1;
}

void FadeAnimation::fade()
{
    if(opacity <= 0.0)
    {
        step = step * (-1.0);
        if(alert_flag == 1)
        {
            label->setPixmap(QPixmap(":/img/red"));
            alert_flag = 0;
            onalert_flag = 1;
        }
        else if(unalert_flag == 1)
        {
            label->setPixmap(QPixmap(":/img/gray"));
            unalert_flag = 0;
            onalert_flag = 0;
            unalert_flag_2 = 1;
        }

    }
    else if(opacity >= 1.0)
    {
        step = step * (-1.0);
        if(unalert_flag_2 == 1)
        {
            unalert_flag_2 = 0;
            timer->stop();
        }
    }
    effect->setOpacity(opacity);
    label->setGraphicsEffect(effect);
    opacity += step;
}
