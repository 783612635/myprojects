#ifndef IMAPPLET_H
#define IMAPPLET_H

#include <QObject>
#include <QScopedPointer>

class IMAppletPrivate;

class IMApplet final : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IMApplet)
public:
    static IMApplet *Instance();

public slots:
    /**
     * @brief init  init something, sa load config, load css ... etc.
     */
    void init();
    /**
     * \brief load qss from path and set style sheet to qApp
     * \param path the qss file path, :/qt.css(from qrc load) or qt.css
     **/
    bool loadQss(const QString &path);

    /**
     * @brief loadQss  load multi qss(css) file to target
     * @param target
     * @param args   qss or css file path. for example, {"Theme/qss/IMLoginWidget.qss", "qt-win.css"}  or {":/qt.css", ":/qt-linux.qss"}
     * @return
     */
    bool loadQss(QWidget *target, const std::initializer_list<const QString>& paths);

    /**
     * @brief refreshQss  reload all qss(css) to qApp
     */
    void refreshQss();

    void initLogHandle();

private:
    explicit IMApplet(QObject *parent = nullptr);
    ~IMApplet();

private:
    QScopedPointer<IMAppletPrivate> d_ptr;
};

#endif // IMAPPLET_H
