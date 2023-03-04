#-------------------------------------------------
#
# Project created by QtCreator 2021-12-02T19:11:32
#
#-------------------------------------------------

QT       += core gui sql
#添加exe图标
RC_ICONS = myappico.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WIMProject
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

include($$PWD/ThirdPart/ThirdPart.prf)
include($$PWD/IMUtils/IMUtils.prf)
include($$PWD/IMUICommon/IMUICommon.prf)

SOURCES += \
    im-applet.cpp \
    main.cpp \
    IMLoginWidget.cpp


HEADERS += \
    IMLoginWidget.h \
    im-applet.h


FORMS += \
    IMLoginWidget.ui


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

