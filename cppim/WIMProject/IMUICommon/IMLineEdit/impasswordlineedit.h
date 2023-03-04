#ifndef IMPASSWORDLINEEDIT_H
#define IMPASSWORDLINEEDIT_H

#include <QLineEdit>
#include <QScopedPointer>

/**
* @brief     用户名密码输入框
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-03
*/
class IMPassWordLineEditPrivate;

class IMPassWordLineEdit:public QLineEdit
{
    Q_DECLARE_PRIVATE(IMPassWordLineEdit)

public:
    enum LineEditType
    {
        LineEditType_User = 0,      //用户名输入框
        LineEditType_PassWord = 1   //密码输入框
    };
    IMPassWordLineEdit(QWidget *parent = nullptr);
    ~IMPassWordLineEdit();
    void setLineEditType(const LineEditType type);
    void setActionIcon(const QIcon & icon );
    void setActionIcon(const QString & icon);
    void setPassWordActionIcon(const QIcon & leftIcon ,const QIcon & rigthIcon);
    void setPassWordActionIcon(const QString & leftIcon,const QString & rigthIcon);

private:
    void initAction();

private slots:
    void on_displayPwdAction_triggered(bool checked);

private:
    LineEditType m_type;
    QScopedPointer<IMPassWordLineEditPrivate> d_ptr;
};

#endif // IMPASSWORDLINEEDIT_H
