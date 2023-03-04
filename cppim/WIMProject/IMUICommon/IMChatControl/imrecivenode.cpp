#include "imrecivenode.h"

#include <QPainter>
#include <QDateTime>

class IMReciveNodePrivate
{
    Q_DECLARE_PUBLIC(IMReciveNode)
    QRect m_rect;
    QString m_time;
    IMReciveNode* q_ptr;
    IMMsgParame m_parame;
};

IMReciveNode::IMReciveNode(const IMMsgParame &parame)
    :d_ptr(new IMReciveNodePrivate)
{
    Q_D(IMReciveNode);
    d->q_ptr = this;
    d->m_parame = parame;
    d->m_time = QDateTime::currentDateTime().toString("hh:mm:ss");
}

IMReciveNode::~IMReciveNode()
{

}

void IMReciveNode::setParentRect(const QRect &rect)
{
    Q_D(IMReciveNode);
    d->m_rect = rect;
}

void IMReciveNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_D(IMReciveNode);
    int chatHeight = m_fixHeight/2;
    //信息窗口
    int messageY = (d->m_parame.m_count*m_fixHeight)+chatHeight;
    //绘制时间
    QRect timeRect(0+m_leftMargin,d->m_parame.m_count*chatHeight*2,d->m_rect.width(),chatHeight);
    painter->drawText(timeRect,Qt::AlignCenter,d->m_time);

    //绘制头像
    painter->drawPixmap(0+m_leftMargin,messageY,chatHeight,chatHeight,QPixmap(d->m_parame.m_iconPath));

    //绘制聊天框
    painter->save();
    int strCount = d->m_parame.m_content.size();
    QRect rect(0+(m_leftMargin*2)+chatHeight,messageY,strCount*15,chatHeight);
    painter->fillRect(rect,Qt::green);
    painter->restore();
    painter->save();

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawText(rect,Qt::AlignCenter,d->m_parame.m_content);
    painter->restore();
}
