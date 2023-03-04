#ifndef IMNODE_H
#define IMNODE_H

#include <QObject>
#include <QGraphicsItem>

class IMNode : public QGraphicsRectItem
{
public:
    IMNode();
    virtual ~IMNode();
    virtual void setParentRect(const QRect& rect)=0;
public:
    const int distance = 10;
    const int m_leftMargin = 15;
    const int m_fixHeight = 100;   //固定高
};

#endif // IMNODE_H
