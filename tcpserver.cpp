#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent,int numConnections) :
    QTcpServer(parent)
{
     sockets = new QMap<int,TcpSocket *>;
     threads = new QMap<int,Thread *>;
     socketList = new QList<TableItem*>;
     threadList = new QList<TableItem*>;
     setMaxPendingConnections(numConnections);
}

TcpServer::~TcpServer()
{
    emit this->sentDisConnect(-1);
    delete sockets;
    delete threads;
}

void TcpServer::setMaxPendingConnections(int numConnections)
{
    this->QTcpServer::setMaxPendingConnections(numConnections);//调用Qtcpsocket函数，设置最大连接数，主要是使maxPendingConnections()依然有效
    this->maxConnections = numConnections;
}

void TcpServer::incomingConnection(qintptr socketDescriptor) //多线程必须在此函数里捕获新连接
{
    if (sockets->size() > maxPendingConnections())//继承重写此函数后，QTcpServer默认的判断最大连接数失效，自己实现
    {
        QTcpSocket tcp;
        tcp.setSocketDescriptor(socketDescriptor);
        tcp.disconnectFromHost();
        return;
    }

    auto socket = new TcpSocket(socketDescriptor);
    Thread *thread = new Thread(socketDescriptor);

    QString ip =  socket->peerAddress().toString();
    qint16 port = socket->peerPort();

    connect(this,&TcpServer::sentDisConnect,socket,&TcpSocket::disConTcp);//断开信号 主动

    connect(socket,&TcpSocket::messageFromSocket,this, &TcpServer::messageReceived);
    connect(thread,&Thread::messageFromThread,this, &TcpServer::messageReceived);
    connect(socket,&TcpSocket::socketDisconnected,this,&TcpServer::handleSocketDisconnected);//socket断开 通知server
    connect(socket,&TcpSocket::destroyed,this,&TcpServer::handleSocketDestroyed);//socket销毁 通知server
    connect(socket,&TcpSocket::destroyed,thread,&Thread::handleSocketDestroyed);//socket销毁 通知thread
    connect(thread,&Thread::threadQuitted, this,&TcpServer::handleThreadQuitted);//thread销毁 通知server
    connect(thread,&Thread::destroyed, this,&TcpServer::handleThreadDestroyed);//thread销毁 通知server

    socket->moveToThread(thread);//把socket移动到新的线程
    thread->start();


    sockets->insert(socketDescriptor,socket);//插入到连接信息中
    threads->insert(socketDescriptor,thread);

    TableItem *socketItem = new TableItem("socket",&socketDescriptor);
    socketList->append(socketItem);
    emit addSocket(socketItem);
    TableItem *threadItem = new TableItem("thread",&socketDescriptor);
    threadList->append(threadItem);
    emit addThread(threadItem);

    emit connectClient(socketDescriptor,ip,port);
    //emit addSocket(socketDescriptor);
}

void TcpServer::messageReceived(QString message)
{
    qDebug() << message;
}

void TcpServer::handleSocketDisconnected(int handle,const QString & ip, quint16 port,QThread * th)
{
    for(int i = 0; i < socketList->size(); i++)
    {
        if(socketList->at(i)->getUid() == handle)
        {
            socketList->at(i)->setState("disconnected");
            emit updateSocket(i);
        }
    }
    sockets->remove(handle);
    //tcpClient->remove(handle);//连接管理中移除断开连接的socket 不能删server主动断开
    //qDebug() << "disconnected" << ip << port;
    //emit sockDisConnect(handle,ip,port);//??
}

void TcpServer::handleSocketDestroyed()
{
    for(int i = 0; i < socketList->size(); i++)
    {
        if(socketList->at(i)->getState() == "disconnected")
        {
            TableItem *temp = socketList->takeAt(i);
            delete temp;
            emit deleteSocket(i);
        }
    }
    //tcpClient->remove(handle);//连接管理中移除断开连接的socket server主动断开
    qDebug() << "one socket is destroyed";
}

void TcpServer::handleThreadQuitted(int handle)
{
    qDebug() << threadList->at(0);
    qDebug() << threadList->size();

    for(int i = 0; i < threadList->size(); i++)
    {
        if(threadList->at(i)->getUid() == handle)
        {
            threadList->at(i)->setState("finished");
            emit updateThread(i);
        }
    }
    threads->remove(handle);
}

void TcpServer::handleThreadDestroyed()
{
    for(int i = 0; i < threadList->size(); i++)
    {
        if(threadList->at(i)->getState() == "finished")
        {
            TableItem *temp = threadList->takeAt(i);
            delete temp;
            emit deleteThread(i);
        }
    }
    qDebug() << "one thread is destoryed";
}


void TcpServer::sendData()
{
    TcpSocket *temp = sockets->first();
    temp->sendData("akb444444444444444444444444444444444444444444444444444444444448");
}

void TcpServer::clear()
{
    emit this->sentDisConnect(-1);
    sockets->clear();
}

/**/
void TcpServer::uiToServer(int tid)
{
    //TcpSocket *temp = sockets->value(tid);
    TcpSocket *temp = sockets->first();
    qDebug() << "find tcp";
    temp->sendData("nutrition facts");
}
