#ifndef IMSENDNODE_H
#define IMSENDNODE_H

#include "imnode.h"
#include <QScopedPointer>

#include "immsgparame.h"
class IMSendNodePrivate;

class IMSendNode : public IMNode
{
    Q_DECLARE_PRIVATE(IMSendNode)
public:
    IMSendNode(const IMMsgParame &parame);
    ~IMSendNode();

    void setParentRect(const QRect& rect)override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)override;

private:
    QScopedPointer<IMSendNodePrivate> d_ptr;
};

#endif // IMSENDNODE_H
