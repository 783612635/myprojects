#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif

#include "gui-util.h"

#include <QApplication>
#include <QScreen>
#include <QWidget>

void IMUtils::moveToScreenCenter(QWidget &w)
{
    auto rect = w.rect();
    w.move(QApplication::primaryScreen()->availableGeometry().center() - QPoint(rect.width()/2, rect.height()/2));
}


