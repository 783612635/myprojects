#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "imchatcontrol.h"
#include <QScrollBar>
#include <QShowEvent>
#include <QResizeEvent>
#include <QGraphicsScene>

#include "imnode.h"
#include "imsendnode.h"
#include "imrecivenode.h"

class IMChatControlPrivate
{
    Q_DECLARE_PUBLIC(IMChatControl)
public:
    IMChatControlPrivate();
    ~IMChatControlPrivate();
    void initScene();
    void sceneUpdate();
    void addLeftNode(IMNode* left);
    void addRightNode(IMNode* right);

    int m_count;
    IMChatControl* q_ptr;
    QGraphicsScene* controlScene;
    std::list<IMNode*> m_leftNodes;   //左聊天信息
    std::list<IMNode*> m_rightNodes;  //右聊天信息
};

IMChatControlPrivate::IMChatControlPrivate()
    :m_count(0),q_ptr(Q_NULLPTR),controlScene(Q_NULLPTR)
{
    m_leftNodes.clear();
    m_rightNodes.clear();
}
IMChatControlPrivate::~IMChatControlPrivate()
{

}
void IMChatControlPrivate::initScene()
{
    controlScene = new QGraphicsScene();
    controlScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    q_ptr->setScene(controlScene);
    q_ptr->setStyleSheet("border:0px");
    q_ptr->setRenderHint(QPainter::Antialiasing);
    q_ptr->setAutoFillBackground(true);
    q_ptr->setCacheMode(QGraphicsView::CacheBackground);
    q_ptr->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    q_ptr->setWindowFlags(Qt::FramelessWindowHint);
    q_ptr->setAttribute(Qt::WA_TranslucentBackground);
    controlScene->setSceneRect(0,0,q_ptr->width(),870);
    q_ptr->setDragMode(QGraphicsView::ScrollHandDrag);
//    q_ptr->verticalScrollBar()->hide();
//    q_ptr->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    q_ptr->verticalScrollBar()->resize(0,0);
    q_ptr->horizontalScrollBar()->hide();
    q_ptr->horizontalScrollBar()->resize(0,0);
    q_ptr->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
void IMChatControlPrivate::addLeftNode(IMNode* left)
{
    m_leftNodes.push_back(left);
    m_count++;
}

void IMChatControlPrivate::addRightNode(IMNode* right)
{
    m_rightNodes.push_back(right);
    m_count++;
}
void IMChatControlPrivate::sceneUpdate()
{
    if(!q_ptr)
        return;
    std::list<IMNode*>::iterator leftItor = m_leftNodes.begin();
    while(leftItor!=m_leftNodes.end())
    {
        (*leftItor)->setParentRect(q_ptr->rect());
        (*leftItor)->update();
        ++leftItor;
    }

    std::list<IMNode*>::iterator rightItor = m_rightNodes.begin();
    while(rightItor!=m_rightNodes.end())
    {
        (*rightItor)->setParentRect(q_ptr->rect());
        (*rightItor)->update();
        ++leftItor;
    }
}

IMChatControl::IMChatControl(QWidget* parent)
    :QGraphicsView(parent),d_ptr(new IMChatControlPrivate())
{
    Q_D(IMChatControl);
    d->q_ptr = this;
    d->initScene();
}

IMChatControl::~IMChatControl()
{
}

void IMChatControl::addSendMsg(IMMsgParame &parame)
{
    Q_D(IMChatControl);
    parame.m_count = d->m_count;
    IMSendNode *leftNode = new IMSendNode(parame);
    leftNode->setParentRect(this->rect());

    d->controlScene->addItem(leftNode);
    d->addLeftNode(leftNode);
}

void IMChatControl::addReciveMsg(IMMsgParame &parame)
{
    Q_D(IMChatControl);
    parame.m_count = d->m_count;
    IMReciveNode *rightNode = new IMReciveNode(parame);
    rightNode->setParentRect(this->rect());

    d->controlScene->addItem(rightNode);
    d->addRightNode(rightNode);
}

std::list<IMNode*> IMChatControl::getLeftNodes()const
{
    return d_ptr->m_leftNodes;
}

std::list<IMNode*> IMChatControl::getRightNodes()const
{
    return d_ptr->m_rightNodes;
}

void IMChatControl::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    this->setFixedSize(event->size());
}

void IMChatControl::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
}
