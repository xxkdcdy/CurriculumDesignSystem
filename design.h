#ifndef DESIGN_H
#define DESIGN_H

#include <QString>


//课设题目类
class design{
private:
    QString id;//编号
    QString dname;//题目名称
    QString keyword;//关键字
    QString tec;//实现技术
    int number;//参与人员数
    QString teacher;//指导教师姓名

public:
    QString getId() const;
    void setId(const QString &value);

    QString getDname() const;
    void setDname(const QString &value);

    QString getKeyword() const;
    void setKeyword(const QString &value);

    QString getTec() const;
    void setTec(const QString &value);

    int getNumber() const;
    void setNumber(int value);

    QString getTeacher() const;
    void setTeacher(const QString &value);
    QString toString();
};


#endif // DESIGN_H
