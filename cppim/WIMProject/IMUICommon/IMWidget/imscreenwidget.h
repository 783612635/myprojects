#ifndef IMSCREENWIDGET_H
#define IMSCREENWIDGET_H

#include <QWidget>
#include <QObject>
#include <QScopedPointer>

/**
* @brief     截图窗口(单例模式)
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-26
*/

class IMScreenWidgetPrivate;

class IMScreenWidget : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMScreenWidget)

public:
    static IMScreenWidget *Instance();
    IMScreenWidget(QWidget* parent = Q_NULLPTR);
    ~IMScreenWidget();

protected:
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);

private slots:
    void saveScreen();
    void saveFullScreen();
    void saveScreenOther();
    void saveFullOther();

private:
    static QScopedPointer<IMScreenWidget> self;
    QScopedPointer<IMScreenWidgetPrivate> d_ptr;
};

#endif // IMSCREENWIDGET_H
