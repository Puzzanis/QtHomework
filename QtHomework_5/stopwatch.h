#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <QObject>
#include <QDebug>
#include <QTimer>

class Stopwatch: public QObject
{
    Q_OBJECT

public:
    explicit Stopwatch(QObject *parent=nullptr);
    ~Stopwatch();

    void ChangeStateButton(QString state);
    QString setText();
    void clearText();

signals:
    void sig_Time(QString m, QString s, QString ms);

private slots:
    void TimerSlot();

private:
    QTimer* timer;
    int time{0};
    int numCircle{0};
    int lastTime{0};
};

#endif // STOPWATCH_H
