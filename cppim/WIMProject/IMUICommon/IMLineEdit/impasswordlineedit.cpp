#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "impasswordlineedit.h"

#include <QAction>
#include <QMouseEvent>
#include <QRegExpValidator>

class IMPassWordLineEditPrivate
{
    Q_DECLARE_PUBLIC(IMPassWordLineEdit)
public:
    IMPassWordLineEditPrivate()
        :m_userAction(NULL),m_pwdAction(NULL)
        ,m_displayPwdAction(NULL)
    {

    }
    IMPassWordLineEdit* q_ptr;
    QAction* m_userAction;      //用户图标
    QAction* m_pwdAction;       //密码图标
    QAction* m_displayPwdAction;//显示密码图标
};

IMPassWordLineEdit::IMPassWordLineEdit(QWidget *parent)
    :QLineEdit(parent),d_ptr(new IMPassWordLineEditPrivate)
{
    Q_D(IMPassWordLineEdit);
    d->q_ptr = this;
    QRegExp rx("^[A-Za-z0-9`~!@#$%^&*()_-+=<>,.\\\\/]+$");
    QRegExpValidator *latitude = new QRegExpValidator(rx, this);
    setValidator(latitude);
}

IMPassWordLineEdit::~IMPassWordLineEdit()
{
}

void IMPassWordLineEdit::setLineEditType(const IMPassWordLineEdit::LineEditType type)
{
    m_type = type;
    initAction();
}

void IMPassWordLineEdit::setActionIcon(const QIcon &icon)
{
    Q_D(IMPassWordLineEdit);
    if(m_type == LineEditType_User)
    {
        if(!d->m_userAction)
            return;
        d->m_userAction->setIcon(icon);
    }
    else if(m_type == LineEditType_PassWord)
    {
        if(!d->m_pwdAction)
            return;
        d->m_pwdAction->setIcon(icon);
    }
}

void IMPassWordLineEdit::setActionIcon(const QString &icon)
{
    Q_D(IMPassWordLineEdit);
    if(m_type == LineEditType_User)
    {
        if(!d->m_userAction)
            return;
        d->m_userAction->setIcon(QIcon(icon));
    }
    else if(m_type == LineEditType_PassWord)
    {
        if(!d->m_pwdAction)
            return;
        d->m_pwdAction->setIcon(QIcon(icon));
    }
}

void IMPassWordLineEdit::setPassWordActionIcon(const QIcon &leftIcon, const QIcon &rigthIcon)
{
    Q_D(IMPassWordLineEdit);
    if(m_type == LineEditType_PassWord)
    {
        if(!d->m_pwdAction||!d->m_displayPwdAction)
            return;
        d->m_pwdAction->setIcon(leftIcon);
        d->m_displayPwdAction->setIcon(rigthIcon);
    }
}

void IMPassWordLineEdit::setPassWordActionIcon(const QString &leftIcon, const QString &rigthIcon)
{
    Q_D(IMPassWordLineEdit);
    if(m_type == LineEditType_PassWord)
    {
        if(!d->m_pwdAction||!d->m_displayPwdAction)
            return;
        d->m_pwdAction->setIcon(QIcon(leftIcon));
        d->m_displayPwdAction->setIcon(QIcon(rigthIcon));
    }
}

void IMPassWordLineEdit::initAction()
{
    Q_D(IMPassWordLineEdit);
    if(m_type == LineEditType_User)
    {
        d->m_userAction = new QAction(this);
        d->m_userAction->setIcon(QIcon(":/Theme/Images/IMPassWordLineEdit/user.png"));
        addAction(d->m_userAction,QLineEdit::LeadingPosition);
    }
    else if(m_type == LineEditType_PassWord)
    {
        d->m_pwdAction = new QAction(this);
        d->m_pwdAction->setIcon(QIcon(":/Theme/Images/IMPassWordLineEdit/password.png"));
        addAction(d->m_pwdAction,QLineEdit::LeadingPosition);
        d->m_displayPwdAction = new QAction(this);
        d->m_displayPwdAction->setIcon(QIcon(":/Theme/Images/IMPassWordLineEdit/search-pressed.png"));
        addAction(d->m_displayPwdAction,QLineEdit::TrailingPosition);
        d->m_displayPwdAction->setCheckable(true);
        d->m_displayPwdAction->setChecked(true);
        setEchoMode(QLineEdit::Password);
#if (QT_VERSION>QT_VERSION_CHECK(5,0,0))
        connect(d->m_displayPwdAction,&QAction::triggered,this,&IMPassWordLineEdit::on_displayPwdAction_triggered);
#endif
    }
}

void IMPassWordLineEdit::on_displayPwdAction_triggered(bool checked)
{
    Q_D(IMPassWordLineEdit);
    if(checked)
    {
        d->m_displayPwdAction->setIcon(QIcon(":/Theme/Images/IMPassWordLineEdit/search-pressed.png"));
        setEchoMode(QLineEdit::Password);
    }
    else
    {
        d->m_displayPwdAction->setIcon(QIcon(":/Theme/Images/IMPassWordLineEdit/search.png"));
        setEchoMode(QLineEdit::Normal);
    }
}
