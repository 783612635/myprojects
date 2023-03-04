#ifndef IMSENDNODE_H
#define IMSENDNODE_H

#include "imnode.h"
#include <QScopedPointer>

#include "immsgparame.h"
class QResizeEvent;
class IMSendNodePrivate;

class IMSendNode : public IMNode
{
    Q_DECLARE_PRIVATE(IMSendNode)
public:
    IMSendNode(const IMMsgParame &parame,QWidget* parent =Q_NULLPTR);
    ~IMSendNode();

private:
    void paintEvent(QPaintEvent* event);

private:
    QScopedPointer<IMSendNodePrivate> d_ptr;
};

#endif // IMSENDNODE_H
