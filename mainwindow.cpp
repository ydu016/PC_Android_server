#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHBoxLayout layout;

    graph = new LineGraphWidget(0,200);
    graph->resize(ui->widget->size().width(),ui->widget->size().height());
    graph->startUpdataTimer(1000);
    layout.addWidget(graph);
    ui->widget->setLayout(&layout);

    ui->socketTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->threadTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->clientTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->clientTableWidget->horizontalHeader()->setStretchLastSection(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSocket(TableItem *item)
{
    QTime time = QTime::currentTime();
    ui->eventListEdit->append(time.toString("h:m:s")+" Socket "+ QString::number(item->getUid())+" is created");
    ui->socketTableWidget->insertRow(ui->socketTableWidget->rowCount());
    ui->socketTableWidget->setItem(ui->socketTableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(item->getUid())));
    ui->socketTableWidget->setItem(ui->socketTableWidget->rowCount()-1,1,new QTableWidgetItem(item->getState()));



    ui->clientTableWidget->insertRow(ui->clientTableWidget->rowCount());
    ui->clientTableWidget->setItem(ui->clientTableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(item->getUid())));
    ui->clientTableWidget->setItem(ui->clientTableWidget->rowCount()-1,1,new QTableWidgetItem(item->getState()));


}

void MainWindow::updateSocket(int i)
{
    QTime time = QTime::currentTime();
    ui->eventListEdit->append(time.toString("h:m:s")+" Socket "+ui->socketTableWidget->item(i,0)->text()+" is disconnected");
    ui->socketTableWidget->item(i,1)->setText("disconnected");
}


void MainWindow::deleteSocket(int i)
{
    QTime time = QTime::currentTime();
    ui->eventListEdit->append(time.toString("h:m:s")+" Socket "+ui->socketTableWidget->item(i,0)->text()+" is deleted");
    ui->socketTableWidget->removeRow(i);
}

void MainWindow::addThread(TableItem *item)
{
    ui->threadTableWidget->insertRow(ui->threadTableWidget->rowCount());
    ui->threadTableWidget->setItem(ui->threadTableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(item->getUid())));
    ui->threadTableWidget->setItem(ui->threadTableWidget->rowCount()-1,1,new QTableWidgetItem(item->getState()));
}

void MainWindow::updateThread(int i)
{
    ui->threadTableWidget->item(i,1)->setText("finished");
}

void MainWindow::deleteThread(int i)
{
    ui->threadTableWidget->removeRow(i);
}

/**/
void MainWindow::on_userTableWidget_clicked(const QModelIndex &index)
{

}

void MainWindow::test()
{
    qDebug() << "test";
}

void MainWindow::on_sendButton_clicked()
{
    qDebug() << "send";
    QSet<int> set;
    QList<QTableWidgetItem *> list = ui->clientTableWidget->selectedItems();
    for(int i = 0; i< list.length(); i++)
    {
        set.insert(ui->clientTableWidget->item(list.at(i)->row(),0)->text().toInt());
    }

    for (QSet<int>::iterator i = set.begin(); i != set.end(); i++)
    {
        emit (uiToServer(*i));
    }
}
