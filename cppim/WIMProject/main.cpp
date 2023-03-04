#include "IMLoginWidget.h"
#include "gui-util.h"
#include "im-applet.h"
#include <QApplication>
#include <set>

int main(int argc, char *argv[])
{
    auto imapp = IMApplet::Instance();
    imapp->init();

    QApplication app(argc, argv);
    imapp->refreshQss(); // load all qss, must be call after app initialized

    IMLoginWidget w;
    w.setWindowTitle("IMCpp");
    imapp->loadQss(&w, {"Theme/qss/IMLoginWidget.qss", "Theme/qss/TitleHeader.qss"})
        || imapp->loadQss(&w, {":/Theme/qss/IMLoginWidget.qss", ":/Theme/qss/TitleHeader.qss"});
    w.show();
    IMUtils::moveToScreenCenter(w);

    return app.exec();
}
