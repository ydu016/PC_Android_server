#include "thread.h"

Thread::Thread(qintptr tid)
{
    this->tid = tid;
    connect(this,&Thread::finished,this,&Thread::handleFinished);//thread结束 内部处理
}

void Thread::handleSocketDestroyed()
{
    emit messageFromThread("Socket is destroyed. Prepare to quit thread");
    this->quit();
}

void Thread::handleFinished()
{
    emit messageFromThread("Thread is finisehd. Preparet to delete thread");
    emit threadQuitted(this->tid);
    this->deleteLater();
}


