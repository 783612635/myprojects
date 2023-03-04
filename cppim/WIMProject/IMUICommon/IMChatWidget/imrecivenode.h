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
    IMReciveNode(const IMMsgParame &parame,QWidget* parent =Q_NULLPTR);
    ~IMReciveNode();

private:
    void paintEvent(QPaintEvent* event);

private:
    QScopedPointer<IMReciveNodePrivate> d_ptr;
};

#endif // IMRECIVENODE_H
