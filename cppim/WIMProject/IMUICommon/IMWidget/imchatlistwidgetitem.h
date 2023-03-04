#ifndef IMCHATLISTWIDGETITEM_H
#define IMCHATLISTWIDGETITEM_H

#include <QWidget>
#include <QEvent>
#include <QObject>
#include <QScopedPointer>
#include "IMUtils/IMDefine/imdefine.h"

/**
* @brief     用户列表窗口项
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-07
*/

class IMChatListWidgetItemPrivate;
class IMChatListWidgetItem : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMChatListWidgetItem)

public:
    IMChatListWidgetItem(const ChatListItem &info,QWidget* parent = Q_NULLPTR);
    ~IMChatListWidgetItem();
    void setChatListItemInfo(const ChatListItem& item);
    void addNewMessage(const QString& message);

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event)override;
    void mousePressEvent(QMouseEvent* event)override;
    void paintEvent(QPaintEvent *event)override;
    void showEvent(QShowEvent* event)override;
    void resizeEvent(QResizeEvent* event)override;

signals:
    void clicked(ChatListItem&);

private:
    QScopedPointer<IMChatListWidgetItemPrivate> d_ptr;
};

#endif // IMCHATLISTWIDGETITEM_H
