#include "mainwindow.h"
#include "tcpserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.test();
    w.show();

#ifndef Q_OS_WIN
    QCoreApplication::setEventDispatcher(new EventDispatcherLibEv());
#endif
    qDebug() << "???" ;
    TcpServer server;
    server.listen(QHostAddress::Any,6666);

    //QObject::connect(&w, &MainWindow::sendData, &ser, &TcpServer::sendData);
    QObject::connect(&server, &TcpServer::addSocket, &w, &MainWindow::addSocket);
    QObject::connect(&server, &TcpServer::updateSocket, &w, &MainWindow::updateSocket);
    QObject::connect(&server, &TcpServer::deleteSocket, &w, &MainWindow::deleteSocket);
    QObject::connect(&server, &TcpServer::addThread, &w, &MainWindow::addThread);
    QObject::connect(&server, &TcpServer::updateThread, &w, &MainWindow::updateThread);
    QObject::connect(&server, &TcpServer::deleteThread, &w, &MainWindow::deleteThread);

    /**/
    QObject::connect(&w, &MainWindow::uiToServer, &server, &TcpServer::uiToServer);
    return a.exec();
}
