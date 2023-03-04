#include "im-applet.h"

#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QWidget>
#include <QFileInfo>

#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>


class IMAppletPrivate
{
    Q_DECLARE_PUBLIC(IMApplet)

    void setMultiSinks();
    QString style_;
    IMApplet *q_ptr;
};

IMApplet::IMApplet(QObject *parent) : QObject{parent}, d_ptr(new IMAppletPrivate)
{
    d_ptr->q_ptr = this;
}

IMApplet::~IMApplet() {}

IMApplet *IMApplet::Instance()
{
    static IMApplet imapplet;
    return &imapplet;
}

void IMApplet::init()
{
    initLogHandle();
}

bool IMApplet::loadQss(const QString &path)
{
    Q_D(IMApplet);

    QFile file(path);
    if (!QFileInfo(file).exists()) {
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream input(&file);
    d->style_ += "\n";
    d->style_ += input.readAll();
    qApp->setStyleSheet(d->style_);

    return true;
}

bool IMApplet::loadQss(QWidget *target, const std::initializer_list<const QString>& paths)
{
    if (!target)
        return false;
    QString style;
    for (const auto &path : paths) {
        QFile file(path);
        if (!QFileInfo(file).exists()) {
            qWarning("failed when load %s, file not exists!\n ", path.toStdString().c_str());
            return false;
        }
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning("failed when load %s, %s\n ",
                     path.toStdString().c_str(),
                     file.errorString().toStdString().c_str());
            return false;
        }
        qDebug("qss load %s succeed ! \n ",path.toStdString().c_str());
        QTextStream input(&file);
        if (!style.isEmpty())
            style += "\n";
        style += input.readAll();
    }
    target->setStyleSheet(style);
    return true;
}

// reload all style sheet from qss(css) files
void IMApplet::refreshQss()
{
    Q_D(IMApplet);
    d->style_.clear(); // clear style sheet
    loadQss("Theme/qss/IMChatWidget.qss") || loadQss(":/Theme/qss/IMChatWidget.qss");
}

void IMApplet::initLogHandle()
{
    Q_D(IMApplet);
    d->setMultiSinks();
    qInstallMessageHandler(
        [](QtMsgType type, const QMessageLogContext &context, const QString &str) {
            static QMutex mutex;
            QMutexLocker lock(&mutex);
            switch (type) {
            case QtMsgType::QtInfoMsg:
                spdlog::info("{} +{} {} {}",
                             context.file,
                             context.line,
                             context.function,
                             str.toStdString());
                break;
            case QtMsgType::QtDebugMsg:
                spdlog::debug("{} +{} {} {}",
                              context.file,
                              context.line,
                              context.function,
                              str.toStdString());
                break;
            case QtMsgType::QtWarningMsg:
                spdlog::warn("{} +{} {} {}",
                             context.file,
                             context.line,
                             context.function,
                             str.toStdString());
                break;
            case QtMsgType::QtCriticalMsg:
                spdlog::critical("{} +{} {} {}",
                                 context.file,
                                 context.line,
                                 context.function,
                                 str.toStdString());
                break;
            case QtMsgType::QtFatalMsg:
                spdlog::error("{} +{} {} {}",
                              context.file,
                              context.line,
                              context.function,
                              str.toStdString());
                // Under VisualStudio, this must be called before main finishes to workaround a known VS issue
                spdlog::drop_all();
                break;
            default:
                spdlog::trace("{} +{} {} {}",
                              context.file,
                              context.line,
                              context.function,
                              str.toStdString());
                break;
            }
        });
}

void IMAppletPrivate::setMultiSinks()
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("%^[%H:%M:%S.%e %l] [thread %t] %v%$");

    // 替换 basic_file_sink_mt，文件大  // 小为 5MB，一共保留 3 个日志文件
    //    auto file_sink = make_shared<basic_file_sink_mt>("applet.log", true);
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("im-applet.log",
                                                                            1024 * 1204 * 5,
                                                                            3);
    file_sink->set_level(spdlog::level::trace);
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%f %l] [thread %t] %v");

    auto logger = std::shared_ptr<spdlog::logger>(
        new spdlog::logger("multi_sink", {file_sink, console_sink}));
    logger->set_level(spdlog::level::trace);
    spdlog::set_default_logger(logger);
}
