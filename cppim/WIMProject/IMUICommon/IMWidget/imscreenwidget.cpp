#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif

#include "imscreenwidget.h"

#include <QtGlobal>
#include <QSize>
#include <QMenu>
#include <QMutex>
#include <QEvent>
#include <QPoint>
#include <QMutex>
#include <QPixmap>
#include <QPainter>
#include <QDateTime>
#include <QFileDialog>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QContextMenuEvent>
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QScreen>
#endif

#ifdef Q_OS_WIN
#include "windows.h"
#include "WinUser.h"
#endif

#define STRDATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))
/**
* @brief     处理截图数据类
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-27
*/
class Screen
{
public:
    Screen();
    ~Screen();
public:
    enum STATUS{SELECT,MOV,SET_W_H};
    Screen(QSize size);
    void setStart(QPoint pos);
    void setEnd(QPoint pos);
    QPoint getStart();
    QPoint getEnd();

    QPoint getLeftUp();
    QPoint getRightDown();

    STATUS getStatus();
    void setStatus(STATUS status);

    int width();
    int height();
    bool isInArea(QPoint pos);//检测pos是否在截图范围内
    void move(QPoint p); //按p,移动截图区域

private:
    QPoint leftUpPos,rightDownPos;//记录，截图区域，左上角、右下角
    QPoint startPos,endPos; //记录 鼠标开始位置、结束位置
    int maxWidth,maxHeight; //记录屏幕大小
    STATUS status; //三个状态：选择区域，移动区域，设置宽高

    void cmpPoint(QPoint &s,QPoint &e); //比较两位置，判断左上角，右下角
};

Screen::Screen()
{

}

Screen::~Screen()
{

}

Screen::Screen(QSize size)
{
    maxWidth = size.width();
    maxHeight = size.height();

    startPos = QPoint(-1,-1);
    endPos = startPos;
    leftUpPos = startPos;
    rightDownPos = startPos;
    status = SELECT;
}

int Screen::width()
{
    return maxWidth;
}

int Screen::height()
{
    return maxHeight;
}

Screen::STATUS Screen::getStatus()
{
    return status;
}

void Screen::setStatus(STATUS status)
{
    this->status = status;
}

void Screen::setEnd(QPoint pos)
{
    endPos = pos;
    leftUpPos = startPos;
    rightDownPos = endPos;
    cmpPoint(leftUpPos, rightDownPos);
}

void Screen::setStart(QPoint pos)
{
    startPos = pos;
}

QPoint Screen::getEnd()
{
    return endPos;
}

QPoint Screen::getStart()
{
    return startPos;
}

QPoint Screen::getLeftUp()
{
    return leftUpPos;
}

QPoint Screen::getRightDown()
{
    return rightDownPos;
}

bool Screen::isInArea(QPoint pos)
{
    if (pos.x() > leftUpPos.x() && pos.x() < rightDownPos.x()
            && pos.y() > leftUpPos.y() && pos.y() < rightDownPos.y()) {
        return true;
    }

    return false;
}

void Screen::move(QPoint p)
{
    int lx = leftUpPos.x() + p.x();
    int ly = leftUpPos.y() + p.y();
    int rx = rightDownPos.x() + p.x();
    int ry = rightDownPos.y() + p.y();

    if (lx < 0) {
        lx = 0;
        rx -= p.x();
    }

    if (ly < 0) {
        ly = 0;
        ry -= p.y();
    }

    if (rx > maxWidth)  {
        rx = maxWidth;
        lx -= p.x();
    }

    if (ry > maxHeight) {
        ry = maxHeight;
        ly -= p.y();
    }

    leftUpPos = QPoint(lx, ly);
    rightDownPos = QPoint(rx, ry);
    startPos = leftUpPos;
    endPos = rightDownPos;
}

void Screen::cmpPoint(QPoint &leftTop, QPoint &rightDown)
{
    QPoint l = leftTop;
    QPoint r = rightDown;

    if (l.x() <= r.x()) {
        if (l.y() <= r.y()) {
            ;
        } else {
            leftTop.setY(r.y());
            rightDown.setY(l.y());
        }
    } else {
        if (l.y() < r.y()) {
            leftTop.setX(r.x());
            rightDown.setX(l.x());
        } else {
            QPoint tmp;
            tmp = leftTop;
            leftTop = rightDown;
            rightDown = tmp;
        }
    }
}

class IMScreenWidgetPrivate
{
    Q_DECLARE_PUBLIC(IMScreenWidget)
public:
    IMScreenWidgetPrivate(){};
    IMScreenWidget* q_ptr;
    QMenu * rightMenu;            //右键菜单对象
    Screen *screen;               //截屏对象
    QPixmap *fullScreen;          //保存全屏图像
    QPixmap *bgScreen;            //模糊背景图
    QPoint movPos;                //坐标
};

QScopedPointer<IMScreenWidget> IMScreenWidget::self;
IMScreenWidget *IMScreenWidget::Instance()
{
    if (self.isNull()) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull()) {
            self.reset(new IMScreenWidget);
        }
    }
    return self.data();
}

IMScreenWidget::IMScreenWidget(QWidget* parent)
        :QWidget(parent),d_ptr(new IMScreenWidgetPrivate)
{
    setWindowFlags(Qt::FramelessWindowHint);
    Q_D(IMScreenWidget);
    d->q_ptr = this;
    d->rightMenu = new QMenu(this);
    d->rightMenu->addAction("保存当前截图", this, &IMScreenWidget::saveScreen);
    d->rightMenu->addAction("保存全屏截图", this, &IMScreenWidget::saveFullScreen);
    d->rightMenu->addAction("截图另存为", this, &IMScreenWidget::saveScreenOther);
    d->rightMenu->addAction("全屏另存为", this, &IMScreenWidget::saveFullOther);
    d->rightMenu->addAction("退出截图", this, &IMScreenWidget::hide);
    //取得屏幕大小
    d->screen = new Screen(QApplication::desktop()->size());
    //保存全屏图像
    d->fullScreen = new QPixmap();
}

IMScreenWidget::~IMScreenWidget()
{
}

void IMScreenWidget::paintEvent(QPaintEvent *)
{
    Q_D(IMScreenWidget);
    int x = d->screen->getLeftUp().x();
    int y = d->screen->getLeftUp().y();
    int w = d->screen->getRightDown().x() - x;
    int h = d->screen->getRightDown().y() - y;

    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawPixmap(0, 0, *d->bgScreen);

    if (w != 0 && h != 0) {
        painter.drawPixmap(x, y, d->fullScreen->copy(x, y, w, h));
    }

    painter.drawRect(x, y, w, h);

    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawText(x + 2, y - 8, tr("截图范围：( %1 x %2 ) - ( %3 x %4 )  图片大小：( %5 x %6 )")
                     .arg(x).arg(y).arg(x + w).arg(y + h).arg(w).arg(h));
}

void IMScreenWidget::showEvent(QShowEvent *)
{
    Q_D(IMScreenWidget);
    QPoint point(-1, -1);
    d->screen->setStart(point);
    d->screen->setEnd(point);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    *d->fullScreen = fullScreen->grabWindow(QApplication::desktop()->winId(), 0, 0, d->screen->width(), d->screen->height());
#else
    QScreen *pscreen = QApplication::primaryScreen();
    *d->fullScreen = pscreen->grabWindow(QApplication::desktop()->winId(), 0, 0, d->screen->width(), d->screen->height());
#endif

    this->activateWindow();
    this->setWindowState((this->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);

    //设置透明度实现模糊背景
    QPixmap pix(d->screen->width(), d->screen->height());
    pix.fill((QColor(160, 160, 160, 200)));
    d->bgScreen = new QPixmap(*d->fullScreen);
    QPainter painter(d->bgScreen);
    painter.drawPixmap(0, 0, pix);
}

void IMScreenWidget::saveScreen()
{
    Q_D(IMScreenWidget);
    int x = d->screen->getLeftUp().x();
    int y = d->screen->getLeftUp().y();
    int w = d->screen->getRightDown().x() - x;
    int h = d->screen->getRightDown().y() - y;

    QString fileName = QString("%1/screen_%2.png").arg(qApp->applicationDirPath()).arg(STRDATETIME);
    d->fullScreen->copy(x, y, w, h).save(fileName, "png");
    close();
}

void IMScreenWidget::saveFullScreen()
{
    Q_D(IMScreenWidget);
    QString fileName = QString("%1/full_%2.png").arg(qApp->applicationDirPath()).arg(STRDATETIME);
    d->fullScreen->save(fileName, "png");
    close();
}

void IMScreenWidget::saveScreenOther()
{
    Q_D(IMScreenWidget);
    QString name = QString(u8"%1.png").arg(STRDATETIME);
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", name, "png Files (*.png)");
    if (!fileName.endsWith(".png")) {
        fileName += ".png";
    }

    if (fileName.length() > 0) {
        int x = d->screen->getLeftUp().x();
        int y = d->screen->getLeftUp().y();
        int w = d->screen->getRightDown().x() - x;
        int h = d->screen->getRightDown().y() - y;
        d->fullScreen->copy(x, y, w, h).save(fileName, "png");
        close();
    }
}

void IMScreenWidget::saveFullOther()
{
    Q_D(IMScreenWidget);
    QString name = QString("%1.png").arg(STRDATETIME);
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", name, "png Files (*.png)");
    if (!fileName.endsWith(".png")) {
        fileName += ".png";
    }

    if (fileName.length() > 0) {
        d->fullScreen->save(fileName, "png");
        close();
    }
}

void IMScreenWidget::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(IMScreenWidget);
    if (d->screen->getStatus() == Screen::SELECT) {
        d->screen->setEnd(e->pos());
    } else if (d->screen->getStatus() == Screen::MOV) {
        QPoint p(e->x() - d->movPos.x(), e->y() - d->movPos.y());
        d->screen->move(p);
        d->movPos = e->pos();
    }
    this->update();
}

void IMScreenWidget::mousePressEvent(QMouseEvent *e)
{
    Q_D(IMScreenWidget);
    int status = d->screen->getStatus();

    if (status == Screen::SELECT) {
        d->screen->setStart(e->pos());
    } else if (status == Screen::MOV) {
        if (d->screen->isInArea(e->pos()) == false) {
            d->screen->setStart(e->pos());
            d->screen->setStatus(Screen::SELECT);
        } else {
            d->movPos = e->pos();
            this->setCursor(Qt::SizeAllCursor);
        }
    }
    this->update();
}

void IMScreenWidget::mouseReleaseEvent(QMouseEvent *)
{
    Q_D(IMScreenWidget);
    if (d->screen->getStatus() == Screen::SELECT) {
        d->screen->setStatus(Screen::MOV);
    } else if (d->screen->getStatus() == Screen::MOV) {
        this->setCursor(Qt::ArrowCursor);
    }
}

void IMScreenWidget::contextMenuEvent(QContextMenuEvent *)
{
    Q_D(IMScreenWidget);
    this->setCursor(Qt::ArrowCursor);
    d->rightMenu->exec(cursor().pos());
}
