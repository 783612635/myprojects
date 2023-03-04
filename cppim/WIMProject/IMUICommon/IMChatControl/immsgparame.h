#ifndef IMMSGPARAME_H
#define IMMSGPARAME_H

#include <QString>
#include <QObject>

enum MsgType
{
    MsgType_Text,   //文本格式
    MsgType_Picture,//图片格式
    MsgType_Voice   //语音类型
};

struct IMMsgParame
{
public:
    int m_count;
    QString m_iconPath;
    QString m_name;
    QString m_content;
    MsgType m_type;
};
Q_DECLARE_METATYPE(IMMsgParame);
#endif // IMMSGPARAME_H
