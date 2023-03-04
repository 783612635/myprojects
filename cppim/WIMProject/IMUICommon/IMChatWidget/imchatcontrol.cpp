#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "imchatcontrol.h"
#include <QShowEvent>
#include <QScrollBar>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "imnode.h"
#include "imsendnode.h"
#include "imrecivenode.h"
#include "IMUICommon/IMScrollArea/imscrollarea.h"

class IMChatControlPrivate
{
    Q_DECLARE_PUBLIC(IMChatControl)
public:
    IMChatControlPrivate();
    ~IMChatControlPrivate();
    void initWidget();
    void update();
    void addItem(IMNode* item);
    void addLeftNode(IMNode* left);
    void addRightNode(IMNode* right);

    int nodeCount;
    IMChatControl* q_ptr;
    QVBoxLayout* layout;
    IMScrollArea* scrollArea;
    std::list<IMNode*> leftNodes;   //左聊天信息
    std::list<IMNode*> rightNodes;  //右聊天信息
};

IMChatControlPrivate::IMChatControlPrivate()
    :nodeCount(0),q_ptr(Q_NULLPTR),layout(Q_NULLPTR)
{
    leftNodes.clear();
    rightNodes.clear();
}
IMChatControlPrivate::~IMChatControlPrivate()
{

}
void IMChatControlPrivate::initWidget()
{
    QHBoxLayout* widgetLayout = new QHBoxLayout();
    scrollArea = new IMScrollArea(q_ptr);

    QWidget* widget = new QWidget();
    QVBoxLayout* areaLayout = new QVBoxLayout(scrollArea);
    layout = new QVBoxLayout();
    layout->setSpacing(0);
    QSpacerItem* spacerItem = new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding);
    areaLayout->addLayout(layout);
    areaLayout->addSpacerItem(spacerItem);
    widget->setLayout(areaLayout);
    scrollArea->setWidget(widget);

    widgetLayout->addWidget(scrollArea);
    layout->setContentsMargins(0,0,0,0);
    areaLayout->setContentsMargins(0,0,0,0);
    widgetLayout->setContentsMargins(0,0,0,0);
    q_ptr->setLayout(widgetLayout);
    QObject::connect(scrollArea->verticalScrollBar(),&QScrollBar::rangeChanged,q_ptr,&IMChatControl::rangeChanged);
}

void IMChatControlPrivate::addItem(IMNode* item)
{
    if(!item)
        return;
    layout->addWidget(item);
}

void IMChatControlPrivate::addLeftNode(IMNode* left)
{
    if(!left)
        return;
    addItem(left);
    leftNodes.push_back(left);
    nodeCount++;
}

void IMChatControlPrivate::addRightNode(IMNode* right)
{
    if(!right)
        return;
    addItem(right);
    rightNodes.push_back(right);
    nodeCount++;
}
void IMChatControlPrivate::update()
{
    if(!q_ptr)
        return;
    std::list<IMNode*>::iterator leftItor = leftNodes.begin();
    while(leftItor!=leftNodes.end())
    {
        (*leftItor)->update();
        ++leftItor;
    }

    std::list<IMNode*>::iterator rightItor = rightNodes.begin();
    while(rightItor!=rightNodes.end())
    {
        (*rightItor)->update();
        ++leftItor;
    }
}

IMChatControl::IMChatControl(QWidget* parent)
    :QWidget(parent),d_ptr(new IMChatControlPrivate())
{
    Q_D(IMChatControl);
    d->q_ptr = this;
    d->initWidget();
}

IMChatControl::~IMChatControl()
{
}

void IMChatControl::addSendMsg(IMMsgParame &parame)
{
    Q_D(IMChatControl);
    parame.m_count = d->nodeCount;
    IMSendNode *rightNode = new IMSendNode(parame);
    d->addLeftNode(rightNode);
}

void IMChatControl::addReciveMsg(IMMsgParame &parame)
{
    Q_D(IMChatControl);
    parame.m_count = d->nodeCount;
    IMReciveNode *leftNode = new IMReciveNode(parame);
    d->addRightNode(leftNode);
}

std::list<IMNode*> IMChatControl::getLeftNodes()const
{
    return d_ptr->leftNodes;
}

std::list<IMNode*> IMChatControl::getRightNodes()const
{
    return d_ptr->rightNodes;
}

void IMChatControl::resizeEvent(QResizeEvent* event)
{
    Q_D(IMChatControl);
    Q_UNUSED(event);
    d->scrollArea->setFixedSize(event->size());
}

void IMChatControl::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
}

void IMChatControl::rangeChanged(int min, int max)
{
    Q_UNUSED(min);
    Q_D(IMChatControl);
    d->scrollArea->verticalScrollBar()->setValue(max);
}
