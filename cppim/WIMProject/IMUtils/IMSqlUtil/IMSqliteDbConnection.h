#ifndef IMSQLITEDBCONNECTION_H
#define IMSQLITEDBCONNECTION_H

#include <QScopedPointer>
#include "IMIDbConnection.h"
#include "IMUtils/IMDefine/imdefine.h"

/**
* @brief     Sqlite数据库管理类(用于管理登录信息数据库)
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-04
*/
class IMSqliteDbConnectionPrivate;

class IMSqliteDbConnection : public IMIDbConnection
{
public:
    static IMSqliteDbConnection *Instance();
    ~IMSqliteDbConnection();
    //初始化数据库
    bool initDbConnection();
    QSqlQuery getQuery();
    //数据库插入账号密码
    bool insertLoginInfo(const LoginInfo& info);
    //判断用户账号密码是否存在
    bool isUserExist(const LoginInfo& info);
private:
    //判断表是否存在
    bool isTableExist(QString table);
    QString getUuid()const;
private:
    explicit IMSqliteDbConnection();
    static QScopedPointer<IMSqliteDbConnection> m_stance;
    QScopedPointer<IMSqliteDbConnectionPrivate> d_ptr;
};

#endif // IMSQLITEDBCONNECTION_H
