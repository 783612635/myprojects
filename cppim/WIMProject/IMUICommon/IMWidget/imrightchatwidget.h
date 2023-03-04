#ifndef IMRIGHTCHATWIDGET_H
#define IMRIGHTCHATWIDGET_H

#include <QObject>
#include <QWidget>
#include <QScopedPointer>
/**
* @brief     右侧聊天窗口界面
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-10
*/
class IMRightChatWidgetPrivate;

class IMRightChatWidget : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMRightChatWidget)

public:
    IMRightChatWidget(QWidget* parent = Q_NULLPTR);
    ~IMRightChatWidget();

private:
    QScopedPointer<IMRightChatWidgetPrivate> d_ptr;
};

#endif // IMRIGHTCHATWIDGET_H
