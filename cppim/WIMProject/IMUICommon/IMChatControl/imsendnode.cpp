#include "imsendnode.h"

#include <QDateTime>
#include <QPainter>
class IMSendNodePrivate
{
    Q_DECLARE_PUBLIC(IMSendNode)
    QRect m_rect;
    QString m_time;
    IMSendNode* q_ptr;
    IMMsgParame m_parame;
};

IMSendNode::IMSendNode(const IMMsgParame &parame)
    :d_ptr(new IMSendNodePrivate)
{
    Q_D(IMSendNode);
    d->m_parame = parame;
    d->m_time = QDateTime::currentDateTime().toString("hh:mm:ss");
}

IMSendNode::~IMSendNode()
{

}

void IMSendNode::setParentRect(const QRect &rect)
{
    Q_D(IMSendNode);
    d->m_rect = rect;
}

void IMSendNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_D(IMSendNode);
    int chatHeight = m_fixHeight/2;
    //信息窗口
    int messageY = (d->m_parame.m_count*m_fixHeight)+chatHeight;

    //绘制时间
    QRect timeRect(0+m_leftMargin,d->m_parame.m_count*chatHeight*2,d->m_rect.width(),chatHeight);
    painter->drawText(timeRect,Qt::AlignCenter,d->m_time);

    //绘制头像
    painter->drawPixmap(d->m_rect.width()-m_leftMargin-chatHeight,messageY,chatHeight,chatHeight,QPixmap(d->m_parame.m_iconPath));
    //绘制聊天框
    painter->save();
    int strCount = d->m_parame.m_content.size();
    QRect rect(d->m_rect.width()-(m_leftMargin*2)-chatHeight-(strCount*15),messageY,strCount*15,chatHeight);
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
