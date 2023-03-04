#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "imchatlistwidgetitem.h"
#include <QStyle>
#include <QPainter>
#include <QDateTime>

class IMChatListWidgetItemPrivate
{
    Q_DECLARE_PUBLIC(IMChatListWidgetItem);
public:
    IMChatListWidgetItemPrivate()
        :m_leave(false)
        ,m_enter(false)
        ,m_pressed(false)
        ,m_newMessage(false)
    {
    }
    bool m_leave;       //鼠标进入
    bool m_enter;       //鼠标离开
    bool m_pressed;     //鼠标按下
    bool m_newMessage;  //新消息
    ChatListItem m_item;
    IMChatListWidgetItem* q_ptr;
};

IMChatListWidgetItem::IMChatListWidgetItem(const ChatListItem &info,QWidget* parent )
    :QWidget(parent),d_ptr(new IMChatListWidgetItemPrivate)
{
    Q_D(IMChatListWidgetItem);
    setContentsMargins(0,5,0,5);
    d->q_ptr=this;
    d->m_item = info;
    d->m_item.m_dataTime = QDateTime::currentDateTime().toString("MM-dd");
    setFixedHeight(70);
}

IMChatListWidgetItem::~IMChatListWidgetItem()
{

}

void IMChatListWidgetItem::setChatListItemInfo(const ChatListItem& item)
{
    Q_D(IMChatListWidgetItem);
    d->m_item = item;
    this->update();
}

void IMChatListWidgetItem::addNewMessage(const QString& message)
{
    Q_D(IMChatListWidgetItem);
    d->m_item.m_message = message;
    this->update();
}

void IMChatListWidgetItem::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    Q_D(IMChatListWidgetItem);
    d->m_enter = true;
    d->m_leave = false;
    d->m_pressed = false;
    this->update();
}

void IMChatListWidgetItem::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    Q_D(IMChatListWidgetItem);
    d->m_enter = false;
    d->m_leave = true;
    d->m_pressed = false;
    this->update();
}

void IMChatListWidgetItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    Q_D(IMChatListWidgetItem);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //鼠标事件效果
    if(d->m_enter)
    {
        painter.save();
        painter.fillRect(this->rect(),QColor(195,195,195,130));
        painter.restore();
    }
    else if(d->m_leave)
    {
        painter.save();
        painter.fillRect(this->rect(),QColor(195,195,195,30));
        painter.restore();
    }
    else if(d->m_pressed)
    {
        painter.save();
        painter.fillRect(this->rect(),QColor(195,195,195,200));
        painter.restore();
    }
    else
    {
        painter.save();
        painter.fillRect(this->rect(),QColor(195,195,195,30));
        painter.restore();
    }
    //绘制图片
    QPixmap pixmap(d_ptr->m_item.m_iconPath);
    QRect pixmapRect(8,8,this->height()-13,this->height()-13);
    painter.drawPixmap(pixmapRect,pixmap);
    //绘制名称
    QRect textRect((this->width()/5)+13,7,250,this->height()/2);
    painter.drawText(textRect,d_ptr->m_item.m_name);
    //绘制信息
    painter.save();
    QRect messageRect((this->width()/5)+13,50,250,this->height()/2);
    QPen pen;
    pen.setColor(QColor(128,128,128));
    painter.setPen(pen);
    painter.drawText(messageRect,d_ptr->m_item.m_message);
    //绘制时间

    QRect m_dataTimeRect(this->width()-50,7,250,this->height()/2);
    painter.drawText(m_dataTimeRect,d_ptr->m_item.m_dataTime);
    painter.restore();
    //绘制新消息红点
    if(!d->m_newMessage)
    {
        painter.save();
        painter.setBrush(QBrush(Qt::red));
        QRectF rectang(6,6, 10.0, 10.0);
        painter.drawEllipse(rectang);
        painter.restore();
    }
}

void IMChatListWidgetItem::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    Q_D(IMChatListWidgetItem);
    d->m_newMessage = true;
    if(d->m_newMessage)
    {
         this->update();
    }
    d->m_pressed = true;
    d->m_enter = false;
    d->m_leave = false;
    this->update();
    emit clicked(d_ptr->m_item);
}

void IMChatListWidgetItem::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    this->update();
}

void IMChatListWidgetItem::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    this->update();
}
