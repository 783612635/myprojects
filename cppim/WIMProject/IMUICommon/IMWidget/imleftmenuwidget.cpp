#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "imleftmenuwidget.h"

#include <QAction>
#include <QVariant>
#include <QSpacerItem>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QResizeEvent>


class IMLeftMenuWidgetPrivate
{
    Q_DECLARE_PUBLIC(IMLeftMenuWidget)
public:
    IMLeftMenuWidgetPrivate();
    ~IMLeftMenuWidgetPrivate();
    void initControls();
    void initItem();
    IMLeftMenuWidget* q_ptr;
    QVBoxLayout* m_topLayout;
    QVBoxLayout* m_bottomLayout;
};

IMLeftMenuWidgetPrivate::IMLeftMenuWidgetPrivate()
    :m_topLayout(Q_NULLPTR),m_bottomLayout(Q_NULLPTR)
{

}
IMLeftMenuWidgetPrivate::~IMLeftMenuWidgetPrivate()
{

}
void IMLeftMenuWidgetPrivate::initControls()
{
    QVBoxLayout* widgetLayout = new QVBoxLayout(q_ptr);
    widgetLayout->setContentsMargins(0,0,0,0);
    QPushButton* userPhoto = new QPushButton("",q_ptr);
    userPhoto->setProperty("userPhoto",true);
    m_topLayout = new QVBoxLayout();
    m_topLayout->setSpacing(20);
    QSpacerItem* spacerItem = new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_bottomLayout = new QVBoxLayout();
    m_bottomLayout->setSpacing(20);
    widgetLayout->addWidget(userPhoto);
    QSpacerItem* spacerItemOne = new QSpacerItem(20,20,QSizePolicy::Fixed,QSizePolicy::Fixed);
    widgetLayout->addSpacerItem(spacerItemOne);
    widgetLayout->addLayout(m_topLayout);
    widgetLayout->addSpacerItem(spacerItem);
    widgetLayout->addLayout(m_bottomLayout);
    QSpacerItem* spacerBottom = new QSpacerItem(30,30,QSizePolicy::Fixed,QSizePolicy::Fixed);
    widgetLayout->addSpacerItem(spacerBottom);
    q_ptr->setLayout(widgetLayout);
}
void IMLeftMenuWidgetPrivate::initItem()
{
    QPushButton* btnMessage = new QPushButton(q_ptr);
    btnMessage->setProperty("message",true);
    q_ptr->addTopItem(btnMessage);
    QPushButton* btnAddress = new QPushButton(q_ptr);
    btnAddress->setProperty("address",true);
    q_ptr->addTopItem(btnAddress);
    QPushButton* btnLook = new QPushButton(q_ptr);
    btnLook->setProperty("look",true);
    q_ptr->addTopItem(btnLook);

    QPushButton* btnSetting = new QPushButton(q_ptr);
    btnSetting->setProperty("setting",true);
    q_ptr->addBottomItem(btnSetting);
}

IMLeftMenuWidget::IMLeftMenuWidget(QWidget *parent)
    : QWidget(parent),d_ptr(new IMLeftMenuWidgetPrivate)
{
    Q_D(IMLeftMenuWidget);
    this->setContentsMargins(0,20,0,5);
    d->q_ptr = this;
    d->initControls();
    d->initItem();
}

IMLeftMenuWidget::~IMLeftMenuWidget()
{

}

void IMLeftMenuWidget::addTopItem(QPushButton* btn)
{
    btn->setIconSize(QSize(40,40));
    d_ptr->m_topLayout->addWidget(btn);
}

void IMLeftMenuWidget::addBottomItem(QPushButton* btn)
{
    btn->setIconSize(QSize(40,40));
    d_ptr->m_bottomLayout->addWidget(btn);
}

void IMLeftMenuWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    this->setFixedSize(event->size());
}
