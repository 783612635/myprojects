#ifndef IMLEFTMENUWIDGET_H
#define IMLEFTMENUWIDGET_H

#include <QWidget>
#include <QScopedPointer>
/**
* @brief     上下菜单栏自定义窗口
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-09
*/
class QPushButton;
class QResizeEvent;
class IMLeftMenuWidgetPrivate;

class IMLeftMenuWidget : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMLeftMenuWidget)
public:
    explicit IMLeftMenuWidget(QWidget *parent = nullptr);
    ~IMLeftMenuWidget();
    //上方添加
    void addTopItem(QPushButton* btn);
    //下方添加
    void addBottomItem(QPushButton* btn);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    QScopedPointer<IMLeftMenuWidgetPrivate> d_ptr;
};

#endif // IMLEFTMENUWIDGET_H
