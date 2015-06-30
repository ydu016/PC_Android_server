#include <QTcpSocket>
#include <QQueue>
#include <QFutureWatcher>
#include <QByteArray>

#include <QTime>


class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(qintptr socketDescriptor, QObject *parent = 0);
    ~TcpSocket();

    QByteArray handleData(QByteArray data,const QString & ip, qint16 port);//用来处理数据的函数
    void doSendData(QByteArray data);
    void doCheckAlive(int second);
    void doDisconnect();

signals:
    void checkAlive(int second);
    void sendDisconnect();
    void readyWrite(const QByteArray &, const int);
    void socketDisconnected(const int ,const QString &,const quint16, QThread *);//NOTE:断开连接的用户信息，此信号必须发出！线程管理类根据信号计数的
    void messageFromSocket(QString message);

protected slots:
    void handleCheckAlive(int second);
    void handlereadyRead();//接收数据
    void handlereadyWrite(const QByteArray &, const int);
    void handleDisconnect();
    void handleDisconnected();

protected:
    QQueue<QByteArray> datas;
private:
    qintptr socketID;

};
