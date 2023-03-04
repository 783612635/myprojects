#ifndef IMCHATWIDGET_H
#define IMCHATWIDGET_H

#include <QWidget>
#include <QScopedPointer>

/**
* @brief     聊天窗口主页
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-14
*/
namespace Ui {
class IMChatWidget;
}
struct ChatListItem;
class IMChatWidgetPrivate;

class IMChatWidget : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMChatWidget)

public:
    explicit IMChatWidget(QWidget *parent = nullptr);
    ~IMChatWidget();

protected:
    void resizeEvent(QResizeEvent* event)override;
    bool eventFilter(QObject *obj, QEvent *event)override;

private slots:
    void currentItem_slots(ChatListItem& item);
    void emojButtonClicked(bool checked);

private slots:
    void minButton_clicked();             //最小化按钮
    void maxButton_clicked();             //最大化按钮
    void closeButton_clicked();           //关闭按钮
    void on_toolButton_send_clicked();    //发送按钮

private:
    QScopedPointer<IMChatWidgetPrivate> d_ptr;
};

#endif // IMCHATWIDGET_H
