#ifndef IMTITLEHEADER_H
#define IMTITLEHEADER_H

#include <QWidget>
#include <QScopedPointer>

namespace Ui {
class IMTitleHeader;
}

/**************************************
    * @author    Wanglipeng
    * @date      2021-12-03
    * @说明      自定义标题头
    ***************************************/
class IMTitleHeaderPrivate;

class IMTitleHeader : public QWidget
{
    Q_OBJECT

public:
    explicit IMTitleHeader(QWidget *parent = nullptr);
    ~IMTitleHeader();

    void setAppName(const QString &name);

protected:
    bool eventFilter(QObject* obj, QEvent * event) override;
    void mousePressEvent(QMouseEvent * event)override;
    void mouseMoveEvent(QMouseEvent * event)override;
    void paintEvent(QPaintEvent * event)override;
    void resizeEvent(QResizeEvent* event)override;

private slots:
    void on_pbt_close_clicked();
    void on_pbt_min_clicked();

private:
    QScopedPointer<IMTitleHeaderPrivate> d_ptr;
    Ui::IMTitleHeader *ui;
};

#endif // IMTITLEHEADER_H
