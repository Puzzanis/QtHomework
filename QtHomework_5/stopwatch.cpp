#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent): QObject(parent)
{
    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &Stopwatch::TimerSlot);
}

Stopwatch::~Stopwatch()
{
    qDebug() << "closed";
}

void Stopwatch::ChangeStateButton(QString state)
{
    if (state == "Старт")
    {
        timer->start(100);
    }
    else {
        timer->stop();
    }
    emit sig_ChangeStateButton((state == "Старт")?"Стоп":"Старт");
}

void Stopwatch::setText()
{
    lastTime = (numCircle == 0)?time:(time-lastTime);
    numCircle += 1;
    QString str = QString("Круг ") +
                  QString::number(numCircle) +
                  QString(", время: ") +
                  QString::number(lastTime/10) +
                  QString(" с ") +
                  QString::number((lastTime%10)*100) + QString(" мс");
    emit sig_setText(str);
    lastTime = time;
}

void Stopwatch::clearText()
{
    time = 0;
    lastTime = 0;
    numCircle = 0;
    emit sig_clearText(time);
}

void Stopwatch::TimerSlot()
{
    time += 1;
    emit sig_Time(time);
}

