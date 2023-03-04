#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "imchatwidget.h"
#include "ui_imchatwidget.h"

#include <QDir>
#include <QShortcut>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QToolButton>
#include <QButtonGroup>

#include "imemojwidget.h"
#include "imscreenwidget.h"
#include "IMUtils/AppConfig/gui-util.h"
#include "IMUICommon/IMChatWidget/immsgparame.h"
#include "IMUICommon/IMChatWidget/imchatcontrol.h"

#define IMDIR() (QDir::currentPath())

class IMChatWidgetPrivate
{
    Q_DECLARE_PUBLIC(IMChatWidget);
public:
    IMChatWidgetPrivate();
    ~IMChatWidgetPrivate();
    void initControls();
    void initChatList();
    void initToolMgrWidget();
    void initTitleButtonGroup();
public:
    Ui::IMChatWidget ui;
    IMChatWidget* q_ptr;
    IMChatControl* chatView;
    IMEmojWidget* emojWidget;
    QSize size;
    bool pressed;       //鼠标是否按下
    bool leftButton;    //限定鼠标左键
    QPoint initPoint;   //初始化屏幕窗口点
    QPoint lastPoint;   //最后按下的坐标
    QHBoxLayout* toolButtonLayout; //菜单管理布局
    QToolButton* expressionMgrBtn; //表情管理按钮
    QToolButton* screenShotBtn;    //屏幕截图按钮
    QToolButton* sendPictureBtn;   //发送图片按钮
    QToolButton* transferFileBtn;  //传送文件按钮

    ChatListItem currentItem;   //当前选中项
};

IMChatWidgetPrivate::IMChatWidgetPrivate()
    :chatView(Q_NULLPTR),pressed(false),leftButton(false)
{
}
IMChatWidgetPrivate::~IMChatWidgetPrivate()
{

}
void IMChatWidgetPrivate::initTitleButtonGroup()
{
    QHBoxLayout * titleLayout = new QHBoxLayout( ui.widget_titleBar );
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(5,5,5,5);
    titleLayout->addStretch();

    QToolButton * minButton = new QToolButton(ui.widget_titleBar);
    minButton->setProperty("minButton",true);
    minButton->setToolTip(u8"最小化");
    titleLayout->addWidget(minButton);

    QToolButton * maxButton = new QToolButton(ui.widget_titleBar);
    maxButton->setProperty("maxButton",true);
    maxButton->setToolTip(u8"放大");
    titleLayout->addWidget(maxButton);

    QToolButton * closeButton = new QToolButton(ui.widget_titleBar);
    closeButton->setProperty("closeButton",true);
    closeButton->setToolTip(u8"关闭");
    titleLayout->addWidget(closeButton);

    titleLayout->setSpacing(10);
    ui.widget_titleBar->setLayout(titleLayout);
    ui.widget_titleBar->setContentsMargins(0,0,0,0);

#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    QObject::connect(minButton,&QToolButton::clicked,q_ptr,&IMChatWidget::minButton_clicked);
    QObject::connect(maxButton,&QToolButton::clicked,q_ptr,&IMChatWidget::maxButton_clicked);
    QObject::connect(closeButton,&QToolButton::clicked,q_ptr,&IMChatWidget::closeButton_clicked);
#endif
}
void IMChatWidgetPrivate::initControls()
{
    // TODO(NiceBlueChai): 点其它（失去焦点）地方自动隐藏表情窗口，避免被主窗口或其他程序的窗口遮住
    emojWidget = new IMEmojWidget(q_ptr);
    QObject::connect(ui.widget_ChatListWidget,&IMChatListWidget::clicked,q_ptr,&IMChatWidget::currentItem_slots);
}
void IMChatWidgetPrivate::initToolMgrWidget()
{
    toolButtonLayout = new QHBoxLayout(ui.chatWidget_toolBar);
    toolButtonLayout->setContentsMargins(5,0,0,0);
    expressionMgrBtn = new QToolButton(q_ptr);
    expressionMgrBtn->setProperty("expression",true);
    screenShotBtn = new QToolButton(q_ptr);
    screenShotBtn->setProperty("screenShot",true);
    sendPictureBtn = new QToolButton(q_ptr);
    sendPictureBtn->setProperty("sendPicture",true);
    transferFileBtn = new QToolButton(q_ptr);
    transferFileBtn->setProperty("transferFile",true);

    toolButtonLayout->addWidget(expressionMgrBtn);
    toolButtonLayout->addWidget(screenShotBtn);
    toolButtonLayout->addWidget(sendPictureBtn);
    toolButtonLayout->addWidget(transferFileBtn);

    QSpacerItem* item = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding);
    toolButtonLayout->addSpacerItem(item);
    toolButtonLayout->setSpacing(20);
    ui.chatWidget_toolBar->setLayout(toolButtonLayout);
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    QObject::connect(expressionMgrBtn,&QPushButton::clicked,q_ptr,&IMChatWidget::emojButtonClicked);
    QObject::connect(screenShotBtn, &QPushButton::clicked, []() { IMScreenWidget::Instance()->showMaximized(); });

    expressionMgrBtn->setCheckable(true);
#endif
}
void IMChatWidgetPrivate::initChatList()
{
    QHBoxLayout* layout = new QHBoxLayout();
    chatView = new IMChatControl(ui.chatWidget);
    layout->addWidget(chatView);
    layout->setContentsMargins(0,0,0,0);
    ui.chatWidget->setStyleSheet("border:none;");
    ui.chatWidget->setLayout(layout);
    for(int i=1;i<6;i++)
    {
        ChatListItem info1;
        info1.m_iconPath = QString(":/Theme/Images/IMChatListWidget/icon%1.jpg").arg(i);
        info1.m_name = QString("小明-%1").arg(i);
        info1.m_message = "你好";
        ui.widget_ChatListWidget->addChatListWidgetItem(info1);
    }
}

IMChatWidget::IMChatWidget(QWidget *parent)
    :QWidget(parent),
      d_ptr(new IMChatWidgetPrivate)
{
    Q_D(IMChatWidget);
    d->ui.setupUi(this);
    installEventFilter(this);
    setWindowFlags(Qt::FramelessWindowHint);
    d->q_ptr = this;
    d->ui.widget_ToolBar->setProperty("widget_ToolBar",true);
    d->initChatList();
    d->initTitleButtonGroup();
    d->initToolMgrWidget();
    d->initControls();
}

IMChatWidget::~IMChatWidget()
{
}

void IMChatWidget::resizeEvent(QResizeEvent *event)
{
    Q_D(IMChatWidget);
    Q_UNUSED(event);
    d->ui.widget->setFixedHeight(this->height());
    d->ui.widget_ToolBar->setFixedHeight(this->height());
    d->ui.widget_ChatListWidget->setFixedHeight(this->height());
}

bool IMChatWidget::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(IMChatWidget);
    if (obj == this)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        if (mouseEvent->type() == QEvent::MouseButtonPress)
        {
            if ( mouseEvent->button() != Qt::LeftButton)
            {
                return false;
            }
            if (this->rect().contains(mouseEvent->pos()))
            {
                d->lastPoint = mouseEvent->pos();
                d->pressed = true;
            }
        }
        else if (mouseEvent->type() == QEvent::MouseMove && d->pressed)
        {
            int offsetX = mouseEvent->pos().x() - d->lastPoint.x();
            int offsetY = mouseEvent->pos().y() - d->lastPoint.y();
            int x = this->x() + offsetX;
            int y = this->y() + offsetY;
            this->move(x, y);
        }
        else if (mouseEvent->type() == QEvent::MouseButtonRelease && d->pressed)
        {
            d->pressed = false;
        }
    }

    return QObject::eventFilter(obj, event);
}

void IMChatWidget::currentItem_slots(ChatListItem& item)
{
    Q_D(IMChatWidget);
    d->currentItem = item;
    d->ui.pbt_userName->setText(d->currentItem.m_name);
}

void IMChatWidget::emojButtonClicked(bool checked)
{
    Q_D(IMChatWidget);
    if(checked)
    {
        d->emojWidget->show();
        d->emojWidget->activateWindow();
        d->emojWidget->move(this->cursor().pos().x(),this->cursor().pos().y()-(d->emojWidget->height()));
    }
    else
    {
        if(d->emojWidget)
        {
            d->emojWidget->showNormal();
            d->emojWidget->hide();
        }
    }
}

void IMChatWidget::minButton_clicked()
{
    this->showMinimized();
}

void IMChatWidget::maxButton_clicked()
{
    Q_D(IMChatWidget);
    QToolButton* sendObj = dynamic_cast<QToolButton*>(sender());
    if(this->isFullScreen())
    {
        this->showNormal();
        if(sendObj)
        {
            this->move(d->initPoint);
            sendObj->setStyleSheet("border-image:url(\":/Theme/Images/IMChatWidget/titleBar/max.png\");");
        }
        return;
    }
    if(sendObj)
    {
        d->initPoint = this->pos();
        sendObj->setStyleSheet("border-image:url(\":/Theme/Images/IMChatWidget/titleBar/max-min.png\");");
        this->showFullScreen();
    }
}

void IMChatWidget::closeButton_clicked()
{
    this->close();
}

void IMChatWidget::on_toolButton_send_clicked()
{
    Q_D(IMChatWidget);
    if(d->currentItem.m_name.isEmpty())
        return;
    IMMsgParame parame;
    parame.m_iconPath = d->currentItem.m_iconPath;
    parame.m_name = d->currentItem.m_name;
    parame.m_content = d->ui.textEdit_send->toPlainText();
    if (parame.m_content.isEmpty()) { // 发送内容为空直接返回
        return;
    }
    parame.m_type = MsgType::MsgType_Text;
    d->chatView->addReciveMsg(parame);

    IMMsgParame parame1;
    parame1.m_iconPath = d->currentItem.m_iconPath;
    parame1.m_name = d->currentItem.m_name;
    parame1.m_content = d->ui.textEdit_send->toPlainText();
    parame1.m_type = MsgType::MsgType_Text;
    d->chatView->addSendMsg(parame1);
    d->ui.textEdit_send->clear();
}
