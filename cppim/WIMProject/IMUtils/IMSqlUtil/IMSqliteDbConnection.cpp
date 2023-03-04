#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "IMSqliteDbConnection.h"
#include <QVariant>
#include <QUuid>
#include <QMutex>
#include <QMutexLocker>
#include <QSqlDatabase>
class IMSqliteDbConnectionPrivate
{
public:
    IMSqliteDbConnectionPrivate()
    {

    }
    QSqlQuery m_query;
    QSqlDatabase m_database;
};

QScopedPointer<IMSqliteDbConnection> IMSqliteDbConnection::m_stance;
IMSqliteDbConnection *IMSqliteDbConnection::Instance()
{
    if(m_stance.isNull())
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if(m_stance.isNull())
        {
            m_stance.reset(new IMSqliteDbConnection);
        }
    }
    return m_stance.data();
}

IMSqliteDbConnection::IMSqliteDbConnection()
    :d_ptr(new IMSqliteDbConnectionPrivate)
{
}

IMSqliteDbConnection::~IMSqliteDbConnection()
{

}

bool IMSqliteDbConnection::initDbConnection()
{
    bool dbConnection = false;
    d_ptr->m_database = QSqlDatabase::addDatabase("QSQLITE");
    d_ptr->m_database.setDatabaseName("IMProject.db");
    if(d_ptr->m_database.open())
    {
        dbConnection = true;
    }
    if(dbConnection)
    {
        QSqlQuery query(d_ptr->m_database);
        d_ptr->m_query = query;
        if(isTableExist("loginInfo"))
        {
            return dbConnection;
        }
        else
        {
            QString createTable = "create table loginInfo("
                                  "user VARCHAR(255),"
                                  "passward VARCHAR(255)"
                                  ")";
            d_ptr->m_query.exec(createTable);
            LoginInfo info;
            info.m_userName="root";
            info.m_passWard="123456";
            insertLoginInfo(info);
        }
    }
    return dbConnection;
}

bool IMSqliteDbConnection::isTableExist(QString table)
{
    int count = 0;
    QString sql = QString("SELECT count(*) FROM %1").arg(table);
    if(d_ptr->m_query.exec(sql))
    {
        d_ptr->m_query.next();
        count = d_ptr->m_query.value(0).toInt();
    }
    if( count > 0 )
    {
         return true;
    }
    else
    {
        return false;
    }
}

QString IMSqliteDbConnection::getUuid() const
{
    return QUuid::createUuid().toString();
}

QSqlQuery IMSqliteDbConnection::getQuery()
{
    return  d_ptr->m_query;
}

bool IMSqliteDbConnection::insertLoginInfo(const LoginInfo &info)
{
    bool isInsert = false;
    if(isUserExist(info))
    {
        isInsert = true;
        return isInsert;
    }
    QString insertSql = QString("insert into loginInfo (user,passward)"
                                " values(\"%1\",\"%2\");")
            .arg(info.m_userName).arg(info.m_passWard);
    if(d_ptr->m_query.exec(insertSql))
    {
        isInsert = true;
    }
    return isInsert;
}

bool IMSqliteDbConnection::isUserExist(const LoginInfo &info)
{
    bool isExist = false;
    QString selectSql = QString("select * from loginInfo where user = \"%1\""
                                "and passward = \"%2\"").arg(info.m_userName).arg(info.m_passWard);
    if(d_ptr->m_query.exec(selectSql))
    {
        while(d_ptr->m_query.next())
        {
            QString userName = d_ptr->m_query.value(0).toString();
            QString passward = d_ptr->m_query.value(1).toString();
            if(userName==info.m_userName||passward==info.m_passWard)
            {
                isExist = true;
            }
        }
    }
    return isExist;
}

