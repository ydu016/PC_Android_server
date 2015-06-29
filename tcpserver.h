#include <QTcpServer>
#include <QHash>
#include "tcpsocket.h"
#include "thread.h"
#include "tableitem.h"

//继承QTCPSERVER以实现多线程TCPscoket的服务器。
//如果socket的信息处理直接处理的话，很多新建的信号和槽是用不到的
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0,int numConnections = 10000);
    ~TcpServer();

    void setMaxPendingConnections(int numConnections);//重写设置最大连接数函数
    void sendData();
    //void sentData(const QByteArray &,const int);//向scoket发送消息

signals:
    void addSocket(TableItem *item);
    void updateSocket(int i);
    void deleteSocket(int i);
    void addThread(TableItem *thread);
    void updateThread(int i);
    void deleteThread(int i);

    void connectClient(const int , const QString & ,const quint16 );//发送新用户连接信息
    void sentDisConnect(int i); //断开特定连接，并释放资源，-1为断开所有。 //向socket发
    void sockDisConnect(int ,QString ,quint16);//断开连接的用户信息 //向ui发

public:
    void clear(); //断开所有连接，线程计数器请0


    /**/
    void uiToServer(int tid);


protected slots:
    void handleSocketDisconnected(int handle,const QString & ip, quint16 prot, QThread *th);//断开连接的用户信息
    void handleSocketDestroyed();
    void handleThreadQuitted(int handle);
    void handleThreadDestroyed();
    void messageReceived(QString message);



protected:
    void incomingConnection(qintptr socketDescriptor);//覆盖已获取多线程
private:
    QMap<int, TcpSocket*> * sockets;//管理连接的map
    QMap<int, Thread* > * threads;
    QList<TableItem*> *socketList;
    QList<TableItem*> *threadList;
    int maxConnections;

};
