#ifndef IMRECIVENODE_H
#define IMRECIVENODE_H

#include "imnode.h"

#include <QScopedPointer>
#include "immsgparame.h"

class IMReciveNodePrivate;

class IMReciveNode : public IMNode
{
    Q_DECLARE_PRIVATE(IMReciveNode)
public:
    IMReciveNode(const IMMsgParame &parame);
    ~IMReciveNode();

    void setParentRect(const QRect& rect)override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)override;

private:
    QScopedPointer<IMReciveNodePrivate> d_ptr;
};

#endif // IMRECIVENODE_H
