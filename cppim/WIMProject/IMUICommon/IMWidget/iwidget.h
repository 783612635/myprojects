#ifndef IWIDGET_H
#define IWIDGET_H

#include <QObject>
#include <QWidget>
#include <QScopedPointer>
QT_BEGIN_NAMESPACE
#include <QEvent>
#include <QPaintEvent>
#include <QMouseEvent>
QT_END_NAMESPACE

//删除对象
#define DELETE(OBJ){\
    if(OBJ)         \
    {               \
        delete OBJ; \
        OBJ = NULL; \
    };              \
}

/**
* @brief     抽象窗口基类
* 1.自定义窗口基类
* 2.透明窗口
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-11-24
*/

class IWidgetPrivate;
class IWidget:public QWidget
{
public:
    IWidget(QWidget* parent = Q_NULLPTR);
    virtual ~IWidget()override;

protected:
    bool eventFilter(QObject* obj, QEvent * event)override;
    void showEvent(QShowEvent * event)override;
    void mousePressEvent(QMouseEvent * event)override;
    void mouseMoveEvent(QMouseEvent * event)override;
    void paintEvent(QPaintEvent *event)override;

public:
    enum ThemeStyle
    {
        ThemeStyle_Blue,    //蓝色风格
        ThemeStyle_Black,   //黑色风格(目前无)
        ThemeStyle_Transparent  //透明风格(目前无)
    };
    void setThemeStyle( const ThemeStyle & Theme );
    void setWindowTitle(const QString& TextName);
    void setContentWidget(QObject * Object);
private:
    void initHeaderTitle();
    void moveToDesktopInCenter();
    QString getThemeStyle(const QString filePath)const;

private slots:
    void maxButton_clicked();
    void minButton_clicked();

private:
    QScopedPointer<IWidgetPrivate> d_ptr;
};

#endif // IWIDGET_H
