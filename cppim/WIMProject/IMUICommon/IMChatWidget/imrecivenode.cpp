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

IMReciveNode::IMReciveNode(const IMMsgParame &parame,QWidget* parent)
    :IMNode(parent),d_ptr(new IMReciveNodePrivate)
{
    Q_D(IMReciveNode);
    setFixedHeight(m_fixHeight);
    d->q_ptr = this;
    d->m_parame = parame;
    d->m_time = QDateTime::currentDateTime().toString("hh:mm:ss");
}

IMReciveNode::~IMReciveNode()
{

}

void IMReciveNode::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    Q_D(IMReciveNode);
    QPainter painter(this);
    int chatHeight = m_fixHeight/2;
    //绘制时间
    QRect timeRect(0+m_leftMargin,0,this->rect().width(),chatHeight);
    painter.drawText(timeRect,Qt::AlignCenter,d->m_time);

    //绘制头像
    painter.drawPixmap(0+m_leftMargin,chatHeight-(chatHeight/6),chatHeight,chatHeight,QPixmap(d->m_parame.m_iconPath));

    //绘制聊天框
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(255,255,255)));
    int fontWidth = d->m_parame.m_content.size()*17;
    QRect fontRect(0+(m_leftMargin*1.3)+chatHeight,chatHeight,fontWidth,chatHeight);
    painter.drawRoundedRect(fontRect,6,6);

    //绘制三角形
    int distance = fontRect.height()/7;
    QPointF points[3] = {
                QPointF(fontRect.topLeft().x(), fontRect.topLeft().y()+distance),
                QPointF(fontRect.topLeft().x()-distance, fontRect.topLeft().y()+(2*distance)),
                QPointF(fontRect.topLeft().x(), fontRect.topLeft().y()+(3*distance))};

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

