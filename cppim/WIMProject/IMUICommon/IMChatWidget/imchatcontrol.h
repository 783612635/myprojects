#ifndef IMCHATCONTROL_H
#define IMCHATCONTROL_H

#include <list>
#include <QWidget>
#include <QScopedPointer>

/**
* @brief     聊天主窗口
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-15
*/
class IMNode;
struct IMMsgParame;
class IMChatControlPrivate;

class IMChatControl : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMChatControl)
public:
    IMChatControl(QWidget* parent = Q_NULLPTR);
    ~IMChatControl();
    //添加发送信息
    void addSendMsg(IMMsgParame& parame);
    //添加接收信息
    void addReciveMsg(IMMsgParame& parame);

    std::list<IMNode*> getLeftNodes()const;
    std::list<IMNode*> getRightNodes()const;

protected:
    void resizeEvent(QResizeEvent* event)override;
    void showEvent(QShowEvent *event) override;

private slots:
    void rangeChanged(int min, int max);

private:
    QScopedPointer<IMChatControlPrivate> d_ptr;
};

#endif // IMCHATCONTROL_H
