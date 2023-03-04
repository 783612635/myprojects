#include "imsendnode.h"

#include <QDateTime>
#include <QPainter>
#include <QResizeEvent>

class IMSendNodePrivate
{
    Q_DECLARE_PUBLIC(IMSendNode);
    QString m_time;
    IMSendNode* q_ptr;
    IMMsgParame m_parame;
};

IMSendNode::IMSendNode(const IMMsgParame &parame,QWidget* parent)
    :IMNode(parent),d_ptr(new IMSendNodePrivate)
{
    Q_D(IMSendNode);
    setFixedHeight(m_fixHeight);
    d->q_ptr = this;
    d->m_parame = parame;
    d->m_time = QDateTime::currentDateTime().toString("hh:mm:ss");
}

IMSendNode::~IMSendNode()
{

}

void IMSendNode::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    Q_D(IMSendNode);
    QPainter painter(this);
    int chatHeight = this->height()/2;

    //绘制时间
    QRect timeRect(0+m_leftMargin,0,this->rect().width(),chatHeight);
    painter.drawText(timeRect,Qt::AlignCenter,d->m_time);

    //绘制头像
    painter.drawPixmap(this->rect().width()-m_leftMargin-chatHeight,chatHeight-(chatHeight/6),chatHeight,chatHeight,QPixmap(d->m_parame.m_iconPath));
    //绘制聊天框
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(15,255,75)));
    int fontWidth = d->m_parame.m_content.size()*17;
    QRect fontRect(this->rect().width()-(m_leftMargin*1.3)-chatHeight-fontWidth
               ,chatHeight,fontWidth,chatHeight);
    painter.drawRoundedRect(fontRect,6,6);

    //绘制三角形
    int distance = fontRect.height()/7;
    QPointF points[3] = {
                QPointF(fontRect.topRight().x(), fontRect.topRight().y()+distance),
                QPointF(fontRect.topRight().x()+distance, fontRect.topRight().y()+(2*distance)),
                QPointF(fontRect.topRight().x(), fontRect.topRight().y()+(3*distance))};

    painter.drawPolygon(points,3);
    painter.restore();

    painter.save();
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawText(fontRect,Qt::AlignCenter,d->m_parame.m_content);
    painter.restore();
}
