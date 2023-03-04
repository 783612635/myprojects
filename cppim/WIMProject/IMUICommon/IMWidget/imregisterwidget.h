#ifndef IMREGISTERWIDGET_H
#define IMREGISTERWIDGET_H

#include "IMUICommon/IMWidget/iwidget.h"

/**
* @brief     注册窗口界面，用于注册数据并录入数据库
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-05
*/

class IMRegisterWidgetPrivate;

class IMRegisterWidget : public IWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMRegisterWidget)

public:
    IMRegisterWidget(QWidget* parent = Q_NULLPTR);
    ~IMRegisterWidget();

private slots:
    void on_pbt_Ok_clicked();
    void on_pbt_Cancle_clicked();

private:
    QScopedPointer<IMRegisterWidgetPrivate> d_ptr;
};

#endif // IMREGISTERWIDGET_H
