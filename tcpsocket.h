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
    void sendData(QByteArray data);

signals:
    //void readData(const int,const QString &,const quint16,const QByteArray &);
    void readyWrite(const QByteArray &, const int);
    void socketDisconnected(const int ,const QString &,const quint16, QThread *);//NOTE:断开连接的用户信息，此信号必须发出！线程管理类根据信号计数的
    void messageFromSocket(QString message);

public slots:
    //void sentData(const QByteArray & ,const int);//发送信号的槽
    void disConTcp(int i);
    void handleDisconnected();

protected slots:
    void handlereadyRead();//接收数据
    void handlereadyWrite(const QByteArray &, const int);

protected:
    QQueue<QByteArray> datas;
private:
    qintptr socketID;

};
