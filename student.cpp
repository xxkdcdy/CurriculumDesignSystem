#include "student.h"
#include <QObject>

QString Student::getSno() const
{
    return sno;
}

void Student::setSno(const QString &value)
{
    sno = value;
}

QString Student::getName() const
{
    return name;
}

void Student::setName(const QString &value)
{
    name = value;
}

QString Student::getSex() const
{
return sex;
}

void Student::setSex(const QString &value)
{
sex = value;
}

int Student::getAge() const
{
return age;
}

void Student::setAge(int value)
{
age = value;
}

QString Student::getMyclass() const
{
return myclass;
}

void Student::setMyclass(const QString &value)
{
myclass = value;
}

QString Student::getMajor() const
{
return major;
}

void Student::setMajor(const QString &value)
{
major = value;
}

QString Student::getTopic() const
{
return topic;
}

void Student::setTopic(const QString &value)
{
topic = value;
}

int Student::getScore() const
{
return score;
}

void Student::setScore(int value)
{
score = value;
}

QString Student::toString(){
    QString ans = QObject::tr("%1\t,%2,%3,%4,%5,%6,%7,%8\n")
            .arg(sno,name,sex,QString::number(age),myclass,major,topic,QString::number(score));
    return ans;
}


