#ifndef IMDEFINE_H
#define IMDEFINE_H

#include <QObject>
#include <QString>


using INT = int;
using DOUBLE = double;
using FLOAT = float;
using BOOL = bool;

//数据库管理
#define GetSQLiteDbManager()  IMSqliteDbConnection::Instance();

#define NEW_OBJ(OBJ,TYPE){    \
    if(NULL==OBJ){OBJ=NEWTYPE}\
}

//登录账号密码信息
struct LoginInfo
{
    LoginInfo(){};
    LoginInfo(const QString& userName,const QString& passWard)
    {
        this->m_userName = userName;
        this->m_passWard = passWard;
    }
    QString m_userName;
    QString m_passWard;
};
//成员信息
struct ChatListItem
{
    ChatListItem()
        :m_iconPath(""),m_name("")
        ,m_message(""),m_dataTime("")
    {};
    ChatListItem(const QString& iconPath,const QString& name
                 ,const QString& message,const QString& dataTime)
        :m_iconPath(iconPath),m_name(name)
        ,m_message(message),m_dataTime(dataTime)
    {};
    ChatListItem& operator == (ChatListItem& other)
    {
        this->m_name = other.m_name;
        return *this;
    }
    QString m_iconPath;
    QString m_name;
    QString m_message;
    QString m_dataTime;
};
#endif // IMDEFINE_H
