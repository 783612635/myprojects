#ifndef IMIDBCONNECTION_H
#define IMIDBCONNECTION_H

#include <QString>
#include <QSqlQuery>

/**
* @brief     数据库连接基类，数据库继承基类进行扩展
* @author    Wanglipeng
* @email     1594932770@qq.com
* @date      2021-12-03
*/
class IMIDbConnection
{
public:
    IMIDbConnection(){};
    virtual ~IMIDbConnection(){};
    virtual bool initDbConnection()=0;
    virtual QSqlQuery getQuery()=0;
};

#endif // IMIDBCONNECTION_H
