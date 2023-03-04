#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "imrightchatwidget.h"

class IMRightChatWidgetPrivate
{
    Q_DECLARE_PUBLIC(IMRightChatWidget)
public:
    IMRightChatWidget* q_ptr;
};

IMRightChatWidget::IMRightChatWidget(QWidget* parent)
    :QWidget(parent),d_ptr(new IMRightChatWidgetPrivate)
{
    Q_D(IMRightChatWidget);
    d->q_ptr = this;
}

IMRightChatWidget::~IMRightChatWidget()
{

}
