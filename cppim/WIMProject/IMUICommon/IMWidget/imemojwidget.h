#ifndef IMEMOJWIDGET_H
#define IMEMOJWIDGET_H

#include <QWidget>
#include <QScopedPointer>
#include <QListWidget>

/**
* @brief     表情管理窗口
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-25
*/
class IMEmojWidgetPrivate;

class IMEmojWidget : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMEmojWidget)

public:
    IMEmojWidget(QWidget* parent=Q_NULLPTR);
    ~IMEmojWidget();

private:
    QScopedPointer<IMEmojWidgetPrivate> d_ptr;
};

#endif // IMEMOJWIDGET_H
