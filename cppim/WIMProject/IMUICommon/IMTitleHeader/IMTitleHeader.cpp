#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "IMTitleHeader.h"

#include "ui_IMTitleHeader.h"
#include <QDir>
#include <QFile>
#include <QPainter>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QStyleOption>
#include <QResizeEvent>
#include <QApplication>

class IMTitleHeaderPrivate
{
public:
    IMTitleHeaderPrivate()
    {}
    QWidget * m_parent;
    QPoint m_dragPosition;//拖拽事件鼠标坐标
};

IMTitleHeader::IMTitleHeader(QWidget *parent) :
    QWidget(parent),d_ptr(new IMTitleHeaderPrivate),
    ui(new Ui::IMTitleHeader)
{
    ui->setupUi(this);
    installEventFilter(this);
    d_ptr->m_parent = parent;
    this->setProperty("IMTitleHeader",true);
}

IMTitleHeader::~IMTitleHeader()
{
    delete ui;
}

void IMTitleHeader::setAppName(const QString & name)
{
    ui->label_TitleName->setText( name );
}

void IMTitleHeader::on_pbt_close_clicked()
{
    qApp->closeAllWindows();
    qApp->exit(0);
}

void IMTitleHeader::on_pbt_min_clicked()
{
    d_ptr->m_parent->showMinimized();
}

bool IMTitleHeader::eventFilter(QObject *obj, QEvent *event)
{
    if( obj == this)
    {
      if( event->type() == QEvent::MouseButtonPress )
      {
          QMouseEvent * mouseEvent = static_cast< QMouseEvent*>(event);
           d_ptr->m_dragPosition = mouseEvent->globalPos()- d_ptr->m_parent->geometry().topLeft();
      }
    }
    return QWidget::eventFilter( obj, event );
}

void IMTitleHeader::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if( event->button() == Qt::LeftButton )
    {
        d_ptr->m_dragPosition = event->globalPos() - d_ptr->m_parent->geometry().topLeft();
    }
}

void IMTitleHeader::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if( d_ptr->m_parent )
    {
        d_ptr->m_parent->move( event->globalPos() - d_ptr->m_dragPosition );
    }
}

void IMTitleHeader::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init( this );
    QPainter painter(this);
    style()->drawPrimitive( QStyle::PE_Widget, &opt, &painter, this);
}

void IMTitleHeader::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(d_ptr->m_parent)
    {
        this->setFixedSize(d_ptr->m_parent->width(),d_ptr->m_parent->height()/10);
    }
}


