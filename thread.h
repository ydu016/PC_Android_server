#include <QThread>
#include <QDebug>

#pragma once
class Thread : public QThread
{
    Q_OBJECT
public:
    Thread(qintptr tid);
signals:
    void messageFromThread(QString message);
    void threadQuitted(qintptr tid);
public slots:
    void handleSocketDestroyed();
    void handleFinished();
private:
    qintptr tid;
};
