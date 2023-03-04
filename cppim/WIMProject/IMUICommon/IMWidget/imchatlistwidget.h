#ifndef IMCHATLISTWIDGET_H
#define IMCHATLISTWIDGET_H

#include <QWidget>
#include <QScopedPointer>
#include "imchatlistwidgetitem.h"
/**
* @brief     用户列表窗口
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-06
*/
class QPaintEvent;
class IMChatListWidgetPrivate;

class IMChatListWidget : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMChatListWidget)

public:
    IMChatListWidget(QWidget *parent = nullptr);
    ~IMChatListWidget();
    void addChatListWidgetItem(const ChatListItem& info);
    void deleteChatListWidgetItem(const QString& name);

protected:
    void showEvent(QShowEvent* event)override;
    void resizeEvent(QResizeEvent* event)override;

private:
    void iniWidgetControls();

signals:
    void clicked(ChatListItem&);

private slots:
    void lineEdit_pressed();
    void itemClicked_slot(ChatListItem& item);

private:
    QScopedPointer<IMChatListWidgetPrivate> d_ptr;
};
#endif // IMCHATLISTWIDGET_H
