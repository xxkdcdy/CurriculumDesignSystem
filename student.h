#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

//学生类
class Student
{
private:
    QString sno;//学号
    QString name;//姓名
    QString sex;//性别
    int age;//年龄
    QString myclass;//班级
    QString major;//专业
    QString topic;//所选题目
    int score;//得分

public:
    bool selectStudentBySno(QString sno);   //查询学生信息是否存在

    QString getSno() const;
    void setSno(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getSex() const;
    void setSex(const QString &value);

    int getAge() const;
    void setAge(int value);

    QString getMyclass() const;
    void setMyclass(const QString &value);

    QString getMajor() const;
    void setMajor(const QString &value);

    QString getTopic() const;
    void setTopic(const QString &value);

    int getScore() const;
    void setScore(int value);

    QString toString();
};

#endif // STUDENT_H
