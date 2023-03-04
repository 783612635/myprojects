#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "imregisterwidget.h"

#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QMessageBox>
#include "IMUtils/IMDefine/imdefine.h"
#include "IMUICommon/IMLineEdit/impasswordlineedit.h"

#include "IMUtils/IMSqlUtil/IMSqliteDbConnection.h"

class IMRegisterWidgetPrivate
{
    Q_DECLARE_PUBLIC(IMRegisterWidget)
public:
    IMRegisterWidgetPrivate()
        :  m_userLabel (Q_NULLPTR),m_passwardLabel(Q_NULLPTR)
          ,m_userLineEdit(Q_NULLPTR),m_passwardLineEdit(Q_NULLPTR)
    {
    };
    //初始化窗口
    void initWidget();
    //初始化样式表
    void initStyleSheet();

    QLabel* m_userLabel;
    QLabel* m_passwardLabel;
    IMPassWordLineEdit* m_userLineEdit;
    IMPassWordLineEdit* m_passwardLineEdit;
    IMRegisterWidget* q_ptr;
};

void IMRegisterWidgetPrivate::initWidget()
{
    QVBoxLayout* vboxLayout = new QVBoxLayout(q_ptr);
    //初始化账号密码
    QHBoxLayout* userLayout = new QHBoxLayout(q_ptr);
    m_userLabel = new QLabel("账号",q_ptr);
    m_userLabel->setProperty("white",true);
    m_userLineEdit = new IMPassWordLineEdit(q_ptr);
    m_userLineEdit->setProperty("blue",true);
    userLayout->addWidget(m_userLabel);
    userLayout->addWidget(m_userLineEdit);

    QHBoxLayout* pwdLayout = new QHBoxLayout(q_ptr);
    m_passwardLabel = new QLabel("密码",q_ptr);
    m_passwardLabel->setProperty("white",true);
    m_passwardLineEdit = new IMPassWordLineEdit(q_ptr);
    m_passwardLineEdit->setProperty("blue",true);
    pwdLayout->addWidget(m_passwardLabel);
    pwdLayout->addWidget(m_passwardLineEdit);

    //按钮初始化
    QPushButton* pbt_OK = new QPushButton("确定",q_ptr);
    pbt_OK->setProperty("Login",true);
    QPushButton* pbt_Cancle = new QPushButton("取消",q_ptr);
    pbt_Cancle->setProperty("Login",true);
    QSpacerItem* spacerItem = new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding);
    QHBoxLayout* ptLayout = new QHBoxLayout(q_ptr);
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    QObject::connect(pbt_OK,&QPushButton::clicked,q_ptr,&IMRegisterWidget::on_pbt_Ok_clicked);
    QObject::connect(pbt_Cancle,&QPushButton::clicked,q_ptr,&IMRegisterWidget::on_pbt_Cancle_clicked);

#else
    connect(pbt_OK,SIGNAL(clicked()),this,SLOT(on_pbt_Ok_clicked()));
    connect(pbt_Cancle,SIGNAL(clicked()),this,SLOT(on_pbt_Cancle_clicked()));
#endif

    ptLayout->addWidget(pbt_OK);
    ptLayout->addSpacerItem(spacerItem);
    ptLayout->addWidget(pbt_Cancle);

    vboxLayout->addLayout(userLayout);
    vboxLayout->addLayout(pwdLayout);
    vboxLayout->addLayout(ptLayout);
    q_ptr->setLayout(vboxLayout);
    q_ptr->setContentWidget(vboxLayout);
}

void IMRegisterWidgetPrivate::initStyleSheet()
{

}

IMRegisterWidget::IMRegisterWidget(QWidget* parent)
    :IWidget(parent),d_ptr(new IMRegisterWidgetPrivate)
{
    Q_D(IMRegisterWidget);
    d_ptr->q_ptr = this;
    setWindowFlags(Qt::FramelessWindowHint);
    d->initWidget();
    d->initStyleSheet();
    setWindowTitle("注册界面");
}

IMRegisterWidget::~IMRegisterWidget()
{
}

void IMRegisterWidget::on_pbt_Ok_clicked()
{
    LoginInfo info(d_ptr->m_userLineEdit->text(),d_ptr->m_passwardLineEdit->text());
    if(IMSqliteDbConnection::Instance()->insertLoginInfo(info))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("注册成功！");
        msgBox.exec();
        this->close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("注册失败！");
        msgBox.exec();
    }
}

void IMRegisterWidget::on_pbt_Cancle_clicked()
{
    close();
    d_ptr->m_userLineEdit->clear();
    d_ptr->m_passwardLineEdit->clear();
}
