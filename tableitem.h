#include <QDebug>

#pragma once
class TableItem
{
public:
    TableItem(QString type, qintptr *uid);
    QString getType();
    int getUid();
    QString getState();
    void setState(QString state);
private:
    QString type;
    qintptr uid;
    QString state;
};

