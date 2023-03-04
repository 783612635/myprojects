#ifndef IMNODE_H
#define IMNODE_H

#include <QWidget>

class IMNode : public QWidget
{
public:
    IMNode(QWidget* parent =Q_NULLPTR);
    virtual ~IMNode();
public:
    const int m_leftMargin = 30;
    const int m_fixHeight = 100;   //固定高
};

#endif // IMNODE_H
