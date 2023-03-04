#ifndef IMLOGINWIDGET_H
#define IMLOGINWIDGET_H

#include <QWidget>
#include <QScopedPointer>


namespace Ui {
class IMLoginWidget;
}
/**
* @brief     登录窗口
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-02
*/
class QShowEvent;
class QResizeEvent;
class IMLoginWidgetPrivate;

class IMLoginWidget final: public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMLoginWidget)
public:
    explicit IMLoginWidget(QWidget *parent = nullptr);
    ~IMLoginWidget();

protected:
    void resizeEvent(QResizeEvent *event)override;
    void paintEvent(QPaintEvent * event)override;
    void showEvent(QShowEvent* event)override;

private:
    void adjustSize();
    void initDatabase();
    void initControlProperty();

private slots:
    void on_pbt_Login_clicked();
    void on_pbt_Register_clicked();

private:
    QScopedPointer<IMLoginWidgetPrivate> d_ptr;
};

#endif // IMLOGINWIDGET_H
