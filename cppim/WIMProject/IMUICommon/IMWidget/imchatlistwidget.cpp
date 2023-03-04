#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "imchatlistwidget.h"
#include <map>
#include <QAction>
#include <QVariant>
#include <QPainter>
#include <QDateTime>
#include <QLineEdit>
#include <QSpacerItem>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QDesktopWidget>

#include "IMUICommon/IMScrollArea/imscrollarea.h"

Q_DECLARE_METATYPE(ChatListItem);
class IMChatListWidgetPrivate
{
    Q_DECLARE_PUBLIC(IMChatListWidget)
public:
    IMChatListWidgetPrivate();
    ~IMChatListWidgetPrivate();
    void addWidget(QWidget* widget);
    void moveToDesktopInCenter(QWidget* widget);
public:
    IMChatListWidget* q_ptr;
    QVBoxLayout* m_userLayout;
    std::map<QString,IMChatListWidgetItem*> m_chatListItemMap;
};

IMChatListWidgetPrivate::IMChatListWidgetPrivate()
    :m_userLayout(Q_NULLPTR)
{
    m_chatListItemMap.clear();
}
IMChatListWidgetPrivate::~IMChatListWidgetPrivate()
{

}
void IMChatListWidgetPrivate::moveToDesktopInCenter(QWidget* widget)
{
    int DesktopWidth = QApplication::desktop()->width();
    int DesktopHeight = QApplication::desktop()->height();
    widget->move( (DesktopWidth/2)-(widget->size().width()/2)
                 , (DesktopHeight/2)- (widget->size().height()/2));
}
void IMChatListWidgetPrivate::addWidget(QWidget* widget)
{
    if(m_userLayout)
    {
        m_userLayout->addWidget(widget);
    }
}

IMChatListWidget::IMChatListWidget(QWidget *parent)
    :QWidget(parent),d_ptr(new IMChatListWidgetPrivate)
{
    setWindowFlags(Qt::FramelessWindowHint);
    iniWidgetControls();
    this->setFixedWidth(300);
    this->setContentsMargins(0,30,0,0);
}

IMChatListWidget::~IMChatListWidget()
{
}

void IMChatListWidget::iniWidgetControls()
{
    Q_D(IMChatListWidget);
    QVBoxLayout* layout = new QVBoxLayout();

    //搜索菜单栏
    QHBoxLayout* searchLayout = new QHBoxLayout();
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText("搜索");
    lineEdit->setStyleSheet("QLineEdit{border:1px solid #9E9E9E;"\
                            "border-radius:8px;min-height:35px;max-height:35px;}"
                            "QAction{height:35px;width:35px;}");
    lineEdit->addAction(new QAction(QIcon(":/Theme/Images/IMChatListWidget/search.png"),"",lineEdit),QLineEdit::LeadingPosition);
    searchLayout->addWidget(lineEdit);
    searchLayout->setContentsMargins(15,5,10,0);

    IMScrollArea* scrollArea = new IMScrollArea(this);
    QWidget* widget = new QWidget();
    QVBoxLayout* areaLayout = new QVBoxLayout(scrollArea);
    d->m_userLayout = new QVBoxLayout();
    d->m_userLayout->setContentsMargins(0,0,0,0);
    d->m_userLayout->setSpacing(0);
    QSpacerItem* spacerItem = new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding);
    areaLayout->addLayout(d->m_userLayout);
    areaLayout->addSpacerItem(spacerItem);
    areaLayout->setContentsMargins(0,0,0,0);
    widget->setLayout(areaLayout);
    scrollArea->setWidget(widget);

    layout->setContentsMargins(0,0,0,0);
    layout->addLayout(searchLayout);
    layout->addWidget(scrollArea);
    layout->setSpacing(10);
    this->setLayout(layout);
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    connect(lineEdit,&QLineEdit::returnPressed,this,&IMChatListWidget::lineEdit_pressed);
#endif
}

void IMChatListWidget::lineEdit_pressed()
{

}

void IMChatListWidget::itemClicked_slot(ChatListItem& item)
{
    emit clicked(item);
}

void IMChatListWidget::addChatListWidgetItem(const ChatListItem &info)
{
    Q_D(IMChatListWidget);
    IMChatListWidgetItem* item = new IMChatListWidgetItem(info,this);
    item->setProperty("data",QVariant::fromValue(info));
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    connect(item,&IMChatListWidgetItem::clicked,this,&IMChatListWidget::itemClicked_slot);
#endif
    d_ptr->m_chatListItemMap.insert(std::pair<QString,IMChatListWidgetItem*>(info.m_name,item));
    d->addWidget(item);
}

void IMChatListWidget::deleteChatListWidgetItem(const QString &name)
{
    Q_D(IMChatListWidget);
    std::map<QString,IMChatListWidgetItem*>::iterator itor = d->m_chatListItemMap.begin();
    while(itor!=d->m_chatListItemMap.end())
    {
        if(itor->first == name)
        {
            delete itor->second;
            itor->second = Q_NULLPTR;
            itor = d->m_chatListItemMap.erase(itor);
            break;
        }
    }
}

void IMChatListWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QWidget* parentWidget = qobject_cast<QWidget*>(parent());
    if(parentWidget)
    {
        this->setFixedHeight(parentWidget->height());
    }
}

void IMChatListWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    QWidget* parentWidget = qobject_cast<QWidget*>(parent());
    if(parentWidget)
    {
        this->setFixedHeight(parentWidget->height());
    }
}
