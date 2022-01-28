#include "design.h"
#include <QObject>


QString design::getId() const
{
    return id;
}

void design::setId(const QString &value)
{
    id = value;
}

QString design::getDname() const
{
    return dname;
}

void design::setDname(const QString &value)
{
    dname = value;
}

QString design::getKeyword() const
{
return keyword;
}

void design::setKeyword(const QString &value)
{
keyword = value;
}

QString design::getTec() const
{
return tec;
}

void design::setTec(const QString &value)
{
tec = value;
}

int design::getNumber() const
{
return number;
}

void design::setNumber(int value)
{
number = value;
}

QString design::getTeacher() const
{
return teacher;
}

void design::setTeacher(const QString &value)
{
teacher = value;
}

QString design::toString(){
    QString ans = QObject::tr("%1,%2,%3,%4,%5,%6\n")
            .arg(id,dname,keyword,tec,QString::number(number),teacher);
    return ans;
}

