#include "tableitem.h"

TableItem::TableItem(QString type, qintptr *uid)
{
    this->type = type;
    this->uid = *uid;
    if(type == "socket")
    {
        this->state = "connected";
    }else
    {
        this->state = "running";
    }
}

QString TableItem::getType()
{
    return this->type;
}

qintptr TableItem::getUid()
{
    return this->uid;
}

QString TableItem::getState()
{
    return this->state;
}

void TableItem::setState(QString state)
{
    this->state = state;
}
