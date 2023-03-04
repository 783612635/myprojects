#ifndef IMScrollArea_H
#define IMScrollArea_H

#include <QMouseEvent>
#include <QScrollArea>
#include <QScopedPointer>

/**
* @brief     自定义滚动区域控件
* 1.可根据滚轮滑动滚动区域
* 2.可扩展区域绘图事件
* 3.可根据鼠标拖拽实现区域移动（仅限于左）
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-11-11
*/
class IMScrollAreaPrivate;
class IMScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    IMScrollArea( QWidget * parent );
    ~IMScrollArea();

private:
    QScopedPointer<IMScrollAreaPrivate> d_ptr;
};

#endif // IMScrollArea_H
