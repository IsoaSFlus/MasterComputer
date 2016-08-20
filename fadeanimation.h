#ifndef FADEANIMATION_H
#define FADEANIMATION_H

#include <QObject>
#include <QGraphicsEffect>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QPixmap>
#include <QLabel>

class FadeAnimation : public QObject
{
    Q_OBJECT
private:
    QTimer *timer;
    QGraphicsOpacityEffect *effect;
    QLabel *label;
    float opacity;
    float step;
    int alert_flag;
    int unalert_flag;
    int unalert_flag_2;
    int onalert_flag;

public:
    explicit FadeAnimation(QObject *parent = 0, QLabel *label = 0);
    void start();
    void stop();
signals:

public slots:
    void fade();
};

#endif // FADEANIMATION_H
