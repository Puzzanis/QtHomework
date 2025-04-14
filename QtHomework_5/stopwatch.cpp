#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent): QObject(parent)
{
    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &Stopwatch::TimerSlot);
}

Stopwatch::~Stopwatch()
{
    delete timer;
}



void Stopwatch::ChangeStateButton(QString state)
{
    if (state == "Стоп")
    {
        timer->start(100);
    }
    else {
        timer->stop();
    }
}

QString Stopwatch::setText()
{
    lastTime = (numCircle == 0)?time:(time-lastTime);
    numCircle += 1;
    QString str = QString("Круг ") +
                  QString::number(numCircle) +
                  QString(", время: ") +
                  QString::number(lastTime/10) +
                  QString(" с ") +
                  QString::number((lastTime%10)*100) + QString(" мс");
    lastTime = time;
    return str;
}

void Stopwatch::clearText()
{
    time = 0;
    lastTime = 0;
    numCircle = 0;
}

void Stopwatch::TimerSlot()
{
    time += 1;
    int ms = (time*100)%1000;
    int s = ((time*100)/1000)%60;
    int m = (((time*100)/1000)/60)%60;

    QString t1 = "." + QString::number(ms);
    t1 = (ms == 0)?".000":t1;
    QString t2 = QString::number(s);
    t2 = (s == 0)?"00":(s < 10)?("0" + t2): t2;
    QString t3 = QString::number(m) + ":";
    t3 = (m == 0)?"00:":(m < 10)?("0" + t3): t3;

    emit sig_Time(t3, t2, t1);
}

