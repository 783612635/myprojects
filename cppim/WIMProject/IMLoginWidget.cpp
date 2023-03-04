#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "IMLoginWidget.h"
#include "ui_IMLoginWidget.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QPainter>
#include <QShowEvent>
#include <QMessageBox>
#include <QStyleOption>
#include <QResizeEvent>
#include <QDesktopWidget>

#include "IMUICommon/IMWidget/imchatwidget.h"
#include "IMUICommon/IMWidget/imregisterwidget.h"
#include "IMUICommon/IMTitleHeader/IMTitleHeader.h"
#include "IMUICommon/IMLineEdit/impasswordlineedit.h"

#include "IMUtils/IMDefine/imdefine.h"
#include "IMUtils/AppConfig/gui-util.h"
#include "IMUtils/IMSqlUtil/IMSqliteDbConnection.h"

//登录窗口宽高设置
const int WIDGET_WIDTH = 500;
const int WIDGET_HEIGHT = 400;

class IMLoginWidgetPrivate
{
    Q_DECLARE_PUBLIC(IMLoginWidget)
    IMLoginWidgetPrivate()
        :m_dbConnection(false)
        ,m_headerTitle(Q_NULLPTR)
        ,m_registerWidget(Q_NULLPTR)
        ,m_chatWidget(Q_NULLPTR)
    {
    }
    Ui::IMLoginWidget ui;
    IMLoginWidget* q_ptr;
    bool m_dbConnection;
    IMTitleHeader* m_headerTitle;
    IMRegisterWidget* m_registerWidget;
    IMChatWidget* m_chatWidget;
};

IMLoginWidget::IMLoginWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new IMLoginWidgetPrivate)
{
    Q_D(IMLoginWidget);

    d->ui.setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(WIDGET_WIDTH,WIDGET_HEIGHT);
    d->m_headerTitle = new IMTitleHeader( this );
    d->m_headerTitle->setAppName("IM登录窗口");
    initDatabase();
    initControlProperty();
}

IMLoginWidget::~IMLoginWidget()
{

}

void IMLoginWidget::initDatabase()
{
    Q_D(IMLoginWidget);
    d->m_dbConnection = IMSqliteDbConnection::Instance()->initDbConnection();
}

void IMLoginWidget::initControlProperty()
{
    Q_D(IMLoginWidget);
    this->setProperty("IMLoginWidget",true);
    d->ui.lineEdit_User->setLineEditType(IMPassWordLineEdit::LineEditType_User);
    d->ui.lineEdit_User->setProperty("blue",true);
    d->ui.lineEdit_PassWord->setLineEditType(IMPassWordLineEdit::LineEditType_PassWord);
    d->ui.lineEdit_PassWord->setProperty("blue",true);
    d->ui.label_UserName->setProperty("white",true);
    d->ui.label_PassWord->setProperty("white",true);
    d->ui.pbt_Login->setProperty("Login",true);
    d->ui.pbt_Register->setProperty("Login",true);
}

void IMLoginWidget::on_pbt_Login_clicked()
{
    Q_D(IMLoginWidget);
    if(d->ui.lineEdit_User->text().isEmpty()||d->ui.lineEdit_PassWord->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("输入账号密码内容不能为空！");
        msgBox.exec();
        return;
    }
    QString userName = d->ui.lineEdit_User->text();
    QString passward = d->ui.lineEdit_PassWord->text();
    LoginInfo info(userName,passward);
    bool isExist = IMSqliteDbConnection::Instance()->isUserExist(info);
    if(isExist)
    {
        if(!d_ptr->m_chatWidget)
        {
            d->m_chatWidget = new IMChatWidget();
            d->m_chatWidget->show();
            IMUtils::moveToScreenCenter(*d->m_chatWidget);
            this->close();
        }
        else
        {
            d_ptr->m_chatWidget->show();
            this->close();
        }
#ifdef Q_DEBUG
        qDebug()<<"sucess";
#endif
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("密码或账号输入错误!");
        msgBox.exec();
        return;
    }
}

void IMLoginWidget::on_pbt_Register_clicked()
{
    //注册窗口
    if(!d_ptr->m_registerWidget)
    {
        d_ptr->m_registerWidget = new IMRegisterWidget();
        if(d_ptr->m_registerWidget->isHidden())
        {
            d_ptr->m_registerWidget->show();
        }
    }
    else
    {
        if(d_ptr->m_registerWidget->isHidden())
        {
            d_ptr->m_registerWidget->show();
        }
    }
}

void IMLoginWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init( this );
    QPainter painter(this);
    style()->drawPrimitive( QStyle::PE_Widget, &opt, &painter, this);
}

void IMLoginWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    adjustSize();
}

void IMLoginWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    adjustSize();
}

void IMLoginWidget::adjustSize()
{
    Q_D(IMLoginWidget);
    d->m_headerTitle->setFixedWidth(this->width());
    QRect desktop = this->geometry();
    d->ui.loginWidget->move((desktop.width() - d->ui.loginWidget->width())/2,
                            (desktop.height() - d->ui.loginWidget->height())/2+(d->m_headerTitle->height()/2));
}
