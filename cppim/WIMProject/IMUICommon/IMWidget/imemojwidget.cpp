#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "imemojwidget.h"

#include <QHBoxLayout>
#include <QTextBrowser>


class  IMEmojWidgetPrivate
{
    Q_DECLARE_PUBLIC(IMEmojWidget)
    void createWidget();
    IMEmojWidget* q_ptr;
    QTextBrowser* textBrowser;
};

void IMEmojWidgetPrivate::createWidget()
{
    if(!q_ptr)
        return;
    q_ptr->setContentsMargins(0,0,0,0);
    QHBoxLayout* layout = new QHBoxLayout();
    textBrowser = new QTextBrowser();
    layout->addWidget(textBrowser);
    layout->setContentsMargins(0,0,0,0);
    q_ptr->setLayout(layout);
    //加上0x00是为了防止表情后面跟随乱码
    char32_t  emoj[] = {0x1F601,0x0};
    for(char32_t i = 0x1F601 ; i <=  0x1F64F ; ++i)
    {
        emoj[0] = i ;
        textBrowser->insertPlainText(QString::fromUcs4(emoj));
    }
}

IMEmojWidget::IMEmojWidget(QWidget* parent)
    :QWidget(parent),d_ptr(new IMEmojWidgetPrivate)
{
    Q_D(IMEmojWidget);
    d->q_ptr = this;
    d->q_ptr->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    d->createWidget();
}

IMEmojWidget::~IMEmojWidget()
{
}
