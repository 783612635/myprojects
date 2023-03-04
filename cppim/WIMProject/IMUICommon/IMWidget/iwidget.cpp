#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "iwidget.h"
#include <QDir>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QToolButton>
#include <QVBoxLayout>
#include <QStyleOption>
#if (QT_VERSION < QT_VERSION_CHECK(5,10,0))
#include <QApplication>
#include <QDesktopWidget>
#else
#include <QGuiApplication>
#include <QScreen>
#endif
#include <QTextStream>

class IWidgetPrivate
{
public:
    IWidgetPrivate():m_titleText(NULL),m_contentLayout(NULL)
    {
    };
    QLabel * m_titleText;
    QPoint m_dragPosition;//拖拽事件鼠标坐标
    QVBoxLayout * m_contentLayout;
};

IWidget::IWidget(QWidget* parent)
    :QWidget(parent)
{
    d_ptr.reset(new IWidgetPrivate);
    this->setProperty("FramHiteWidget",true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->initHeaderTitle();
    setThemeStyle(IWidget::ThemeStyle_Blue);
}

IWidget::~IWidget()
{
}

void IWidget::moveToDesktopInCenter()
{
    if( !isMinimized() )
    {
        repaint();
    }
#if (QT_VERSION < QT_VERSION_CHECK(5,10,0))
    int desktopWidth = QApplication::desktop()->screenGeometry().width();
    int desktopHeight = QApplication::desktop()->screenGeometry().height();
#else
    int desktopWidth = QGuiApplication::primaryScreen()->geometry().width();
    int desktopHeight = QGuiApplication::primaryScreen()->geometry().height();
#endif
    this->move( (desktopWidth/2)-(this->size().width()/2), (desktopHeight/2)- (this->size().height()/2));
}

void IWidget::initHeaderTitle()
{
    //垂直布局容器
    QVBoxLayout * mainBoxLayout = new QVBoxLayout(this);
    mainBoxLayout->setContentsMargins(5,5,5,5);
    mainBoxLayout->setSpacing(0);

    //添加Windows Title区域
    QWidget * titleBar = new QWidget(this);
    titleBar->setObjectName("title");
    titleBar->setProperty("TitleWidget",true);

    QHBoxLayout * titleLayout = new QHBoxLayout( titleBar );
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(5,5,5,5);

    d_ptr->m_titleText = new QLabel(titleBar);
    d_ptr->m_titleText->setProperty("TitleLabel",true);
    d_ptr->m_titleText->setToolTip(d_ptr->m_titleText->text());

    titleLayout->addWidget(d_ptr->m_titleText);
    titleLayout->addStretch();

    QToolButton * maxButton = new QToolButton(titleBar);
    maxButton->setProperty("maxButton",true);
    maxButton->setMinimumSize(21,21);
    maxButton->setMaximumSize(21,21);
    maxButton->setToolTip("放大");
    titleLayout->addWidget(maxButton);
    maxButton->setVisible(false);

    QToolButton * minButton = new QToolButton(titleBar);
    minButton->setProperty("minButton",true);
    minButton->setMinimumSize(21,21);
    minButton->setMaximumSize(21,21);
    minButton->setToolTip("最小化");
    titleLayout->addWidget(minButton);

    QToolButton * closeButton = new QToolButton(titleBar);
    closeButton->setProperty("closeButton",true);
    closeButton->setMinimumSize(21,21);
    closeButton->setMaximumSize(21,21);
    closeButton->setToolTip("关闭");
    titleLayout->addWidget(closeButton);

    titleLayout->setSpacing(10);
    titleBar->setLayout(titleLayout);

    QWidget* contentWidget = new QWidget(this);
    contentWidget->setProperty("contentWidget",true);
    d_ptr->m_contentLayout = new QVBoxLayout(contentWidget);
    contentWidget->setLayout(d_ptr->m_contentLayout);

    mainBoxLayout->addWidget(titleBar);
    mainBoxLayout->addWidget(contentWidget);

    setLayout(mainBoxLayout);

#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    connect(closeButton,&QToolButton::clicked,[=](){this->close();});
    connect(maxButton,&QToolButton::clicked,this,&IWidget::maxButton_clicked);
    connect(minButton,&QToolButton::clicked,this,&IWidget::minButton_clicked);

#else
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(maxButton,SIGNAL(clicked()),this,SLOT(maxButton_clicked()));
    connect(minButton,SIGNAL(clicked()),this,SLOT(minButton_clicked()));
#endif
}

void IWidget::maxButton_clicked()
{
    if(!this->isMaximized())
    {
       this->showMaximized();
    }
}

void IWidget::minButton_clicked()
{
    if(!this->isMinimized())
    {
       this->showMinimized();
    }
}

void IWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    moveToDesktopInCenter();
}

void IWidget::setContentWidget(QObject *Object)
{
    QWidget* widget = qobject_cast<QWidget*>(Object);
    QLayout* layout = qobject_cast<QLayout*>(Object);
    if( widget )
    {
        d_ptr->m_contentLayout->addWidget(widget);
    }
    else if( layout )
    {
        d_ptr->m_contentLayout->addLayout(layout);
    }
}

bool IWidget::eventFilter(QObject *obj, QEvent *event)
{
    if( obj == this)
    {
        if( event->type() == QEvent::MouseButtonPress )
        {
            QMouseEvent * mouseEvent = static_cast< QMouseEvent*>(event);
            d_ptr->m_dragPosition = mouseEvent->globalPos() - frameGeometry().topLeft();
        }
        else if( event->type() == QEvent::MouseButtonDblClick)
        {
            showMaximized();
        }
    }
    return QWidget::eventFilter( obj, event );
}

void IWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if( event->button() == Qt::LeftButton )
    {
        d_ptr->m_dragPosition = event->globalPos() - frameGeometry().topLeft();
    }
}

void IWidget::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    move( event->globalPos() - d_ptr->m_dragPosition );
}

void IWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init( this );
    QPainter painter(this);
    style()->drawPrimitive( QStyle::PE_Widget, &opt, &painter, this);
}

void IWidget::setThemeStyle(const IWidget::ThemeStyle &Theme)
{
    if( Theme == ThemeStyle::ThemeStyle_Blue )
    {
       this->setAttribute(Qt::WA_TranslucentBackground);
       style()->unpolish(this);
       this->setStyleSheet(getThemeStyle("/Theme/qss/IWidget.qss"));
       style()->polish(this);
    }
    else if( Theme == ThemeStyle::ThemeStyle_Black )
    {
       this->setAttribute(Qt::WA_TranslucentBackground);
       style()->unpolish(this);
       this->setStyleSheet(getThemeStyle(""));
       style()->polish(this);
    }
    else if( Theme == ThemeStyle::ThemeStyle_Transparent )
    {
        style()->unpolish(this);
        this->setStyleSheet(getThemeStyle(""));
        style()->polish(this);
    }
}

QString IWidget::getThemeStyle(const QString filePath)const
{
    QString style="";
    QFile file( QDir::currentPath() + filePath );
    if( file.open(QFile::ReadOnly) )
    {
        QTextStream input(&file);
        style+="\n";
        style+=input.readAll();
        file.close();
    }
    return style;
}

void IWidget::setWindowTitle(const QString &TextName)
{
    d_ptr->m_titleText->setText(TextName);
}
